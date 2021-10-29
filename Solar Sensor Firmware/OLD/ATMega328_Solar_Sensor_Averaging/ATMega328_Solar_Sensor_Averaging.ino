/*
   Solar Sensor Averaging firmware for ATMega328
   by:    Matt Little
   date:  22/8/2021
   w:     www.curiouselectric.co.uk
   e:     hello@curiouselectric.co.uk

   This code is for an ATMega328 unit solar sensor unit.
   This uses an ATMega328 running at 8MHz with 3.3v or 5V supply.

   To program it then MiniCore is used:
   // For optiboot using 3.3V and 8MHz and with WDT we need to sort out new code:
   Easiest method is:
   Install MiniCore from here: https://github.com/MCUdude/MiniCore
   Add to preferences and then board manager.

  Optiboot is used as the bootlloader:
  Need to download optiboot5a from here:
  https://code.google.com/archive/p/optiboot/downloads
  Install optiboot_atmega328.hex into a folder called "optiboot5a" in the hardware section
  Use this optiboot hex file for upload to the ATmega328
  Fuses are: Low = 0xFF, High = 0xDE, Extended = 0xFE

   More construction details are here:
   https://github.com/curiouselectric/SolarSensor
   and
   *** link to web page for design documentation ***

   This code works with an ADC and the serial port
   It reads the ADC and temperature sensor at regular time intervals
   It returns the average values when requested on serial port
   At all other times then the unit is asleep.

   My implementation:
   Recieve data:
   “aaI*R01A4#”
   Where “aa” is just a start code
   "I" gives the ID of the sensor controller unit.
   "*" is the ID of the sensor controller & means multiple sensors units can be attached to one upload controller.
   “R” means read data
   “01” is a sensor number – one of these for each sensor attached. Up to 24.
   Sensor 00 is for the battery voltage, sensors 01-24 are for the external attached sensors.
   “A” means averaging period
   “4” is the averaging period in seconds.
   This can be (0) 1s, (1) 10s, (2) 60s, (3) 600s, (4) 3600s, for 1 second, 10 second, 1 min, 10 min and 1 hour averaging. No other values allowed.
   “#” is just an end character.

   If data is not that length or does not have 'aa' and '#' at start/end then return with send "aaFAIL**#" error code

  /* Failure codes:
    "aaFAIL1#" = String too long
    "aaFAIL2#" = Unit ID not correct/not a number
    "aaFAIL3#" = Channel ID is not correct/not a number
    "aaFAIL4#" = Average not correct/not a number
    "aaFAIL5#" = Start/End chars not correct
    "aaFAILID#" = Channel ID not correct not correct
    "aaFAILID#" = Ave Value not correct not correct
*/

/*
  The returned data will be:
  “aaD01A12345MN12345MX12345#”

  This returns “aaD01” which is a repeat of the sensor number requested.
  Then “A”  which is the average value for the sample period requested which can be a value from 00000 to 99999 (16 bit value in decimal format).
  Then “MN” which is the minimum value for the sample period requested which can be a value from 00000 to 99999 (16 bit value in decimal format).
  Then “MX” which is the maximum value for the sample period requested which can be a value from 00000 to 99999 (16 bit value in decimal format).
  “#” is just an end character.

  If a serial command “aaI*RESET#” is sent then (if the ID matches) the Max and Min are reset
  This is to ensure data transfer before reset.

  Based on:
  http://www.arduino.cc/en/Tutorial/SerialEvent

  // TO DO:

  Sort out ADC channel 1 read - why is it max value all the time? - +/-2.094V is the ADC max need to keep within this...
  Sort out reading ADC channel 2
  DONE - Sort out change baud rate - will need device restart? Need to store in EEPROM. - Done. Only a few different rates. Will reset after changing it.


*/

#include <stdio.h>
#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>       // for saving mode to EEPROM
#include <avr/wdt.h>      // for the watch dog timer

// For the LM75 I2C temperature sensor:
#include <Temperature_LM75_Derived.h>

//For the MCP3426 ADC I2C sensor:
// https://github.com/stevemarple/MCP342x
#include <MCP342x.h>

#include "Button2.h"      // Need to include this to the library
#include "config.h"
#include "serial_parse.h"
#include "average_data.h"
#include "utilitiesDL.h"

// 0x68 is the default address for all MCP342x devices
uint8_t address = 0x68;
MCP342x adc = MCP342x(address);
// Configuration settings
MCP342x::Config config1(MCP342x::channel1, MCP342x::oneShot, MCP342x::resolution16, MCP342x::gain1);
// Configuration/status read back from the ADC
MCP342x::Config status1;
MCP342x::Config config2(MCP342x::channel2, MCP342x::oneShot, MCP342x::resolution16, MCP342x::gain1);
// Configuration/status read back from the ADC
MCP342x::Config status2;

// The Generic_LM75 class will provide 9-bit (±0.5°C) temperature for any
// LM75-derived sensor. More specific classes may provide better resolution.
Generic_LM75 temperature(0x48);

// ****** This is for the buttons button2 library used and needs to be installed ********
// https://github.com/LennartHennigs/Button2
Button2 buttonA = Button2(SWA_PIN);

int SERIAL_BAUD;
long int baud_rates[MAX_BAUD_RATES] = {1200, 4800, 9600, 57600, 115200}; // This holds the available baud rates

// ******** This is for Scheduling Tasks **************************
// Must include this library from Arduino IDE Library Manager
// https://github.com/arkhipenko/TaskScheduler
#include <TaskScheduler.h>

// #define _TASK_TIMECRITICAL      // Enable monitoring scheduling overruns
#define _TASK_SLEEP_ON_IDLE_RUN    // Enable 1 ms SLEEP_IDLE powerdowns between tasks if no callback methods were invoked during the pass
// #define _TASK_STATUS_REQUEST    // Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only
// #define _TASK_WDT_IDS           // Compile with support for wdt control points and task ids
// #define _TASK_LTS_POINTER       // Compile with support for local task storage pointer
// #define _TASK_PRIORITY          // Support for layered scheduling priority
// #define _TASK_MICRO_RES         // Support for microsecond resolution
// #define _TASK_STD_FUNCTION      // Support for std::function (ESP8266 and ESP32 ONLY)
// #define _TASK_DEBUG             // Make all methods and variables public for debug purposes
// #define _TASK_INLINE            // Make all methods "inline" - needed to support some multi-tab, multi-file implementations
// #define _TASK_TIMEOUT           // Support for overall task timeout
// #define _TASK_OO_CALLBACKS      // Support for dynamic callback method binding
// #define _TASK_DEFINE_MILLIS     // Force forward declaration of millis() and micros() "C" style
// #define _TASK_EXPOSE_CHAIN      // Methods to access tasks in the task chain

// Callback methods prototypes
void t1Callback();
void t1SCallback();
void t10SCallback();
void t60SCallback();
void t600SCallback();
void t3600SCallback();

// Tasks
// time (mS) between tasks, number of tasks to do, call back function
/*
  Scheduling defines:
  TASK_MILLISECOND
  TASK_SECOND
  TASK_MINUTE
  TASK_HOUR
  TASK_IMMEDIATE
  TASK_FOREVER
  TASK_ONCE
  TASK_NOTIMEOUT
*/

Task t1     (100 * TASK_MILLISECOND, TASK_FOREVER,  &t1Callback);   // Sample as base rate of 10Hz
Task t1S    (TASK_SECOND, TASK_FOREVER, &t1SCallback);
Task t10S   (10 * TASK_SECOND, TASK_FOREVER, &t10SCallback);
Task t60S   (TASK_MINUTE, TASK_FOREVER, &t60SCallback);
Task t600S  (10 * TASK_MINUTE, TASK_FOREVER, &t600SCallback);
Task t3600S (TASK_HOUR, TASK_FOREVER, &t3600SCallback);

Scheduler runner;

// *********** This is for the serial data parsing ******************
// Create a class for the serial data to be parsed
check_data   checkData;

// *********** This is for the data holders *************************
// Want to create a data class for each channel, up to max of NUM_CHANNELS
data_channel channels[NUM_CHANNELS];    // This creates our data channels

// *********** These are global variables ***************************
String        inputString = "";           // a String to hold incoming data
String        errorString = "";           // a String to hold incoming data
String        returnString = "";          // A string to hold the returned data
bool          stringComplete = false;     // Checks if the string is complete
byte          UNIT_ID = B00000000;        // This is the unit_id of the board itself. This will be default value. Values from 0-255 can potentially be used. 4 bit binary number? = 16 channels.
bool          display_1s_data = false;    // This flag is for displaying the data on serial. USeful for debug?
int           flow_control = 0;           // This defines if flow meters are attached. 0= None, 1 =  1 flow 2 = 2 flow. Stored in EEPROM.
uint32_t      led_flash_timer = millis();
bool          led_update_flag = true;
long int      data_random;
volatile int  data_counter_1s = 0;
volatile int  data_counter_10s = 0;
volatile int  data_counter_60s = 0;
volatile int  data_counter_600s = 0;
volatile int  data_counter_3600s = 0;

void t1Callback() {
  // This loop runs every 100mS
  // This will record the value and store it
  // It will then be averaged for 1s, 10s, 60s 10min and 1 hour averages

  int32_t dataValue = 0;
  MCP342x::Config status;
  // Initiate a conversion; convertAndRead() will wait until it can be read
  uint8_t err = adc.convertAndRead(MCP342x::channel1, MCP342x::oneShot,
                                   MCP342x::resolution16, MCP342x::gain1,
                                   1000000, dataValue, status);
//  if (err) {
//    Serial.print("Convert error: ");
//    Serial.println(err);
//  }
//  else {
//    Serial.print("Value: ");
//    Serial.println(dataValue);
//  }

  //  uint8_t err1;
  //  err1 = adc.convert(config1);
  //  err1 = adc.read(dataValue, status1);
  //  if (!err1 && status1.isReady())
  //  {

  channels[0].data_1s_holder += dataValue;
  // Here we set the max and min for the data
  if (dataValue < channels[0].data_min)
  {
    channels[0].data_min = dataValue;
  }
  if (dataValue > channels[0].data_max)
  {
    channels[0].data_max = dataValue;
  }

  data_counter_1s++;   // This counts the correct number of samples we take within the 1S sample period. Used for averaging.
}

void t1SCallback() {
  if (!t1S.isFirstIteration())
  {
    // We only read the temperature every second
    float dataTemperature = (temperature.readTemperatureC()) * 10.0 ; // The value is a float - need to convert to an int in 100's C
    channels[1].data_1s_holder = (int32_t)dataTemperature * data_counter_1s;  // We bring in the averaging here, so the values all work out.
    // Here we set the max and min for the data
    if (dataTemperature < channels[1].data_min)
    {
      channels[1].data_min = dataTemperature;
    }
    if (dataTemperature > channels[1].data_max)
    {
      channels[1].data_max = dataTemperature;
    }
    // End of reading temperature - now deal with the averaging...

    for (int j = 0; j < NUM_CHANNELS; j++)
    {
      // 1 second averages put into the correct channels
      channels[j].data_1s = channels[j].data_1s_holder / data_counter_1s;
      // reset all the data holders
      channels[j].data_1s_holder  = 0;    // Reset the value
      // Add on values for next average
      channels[j].data_10s_holder += channels[j].data_1s;   // This is for the 10s averages
    }

    if (DEBUG_DATA_1S == true || display_1s_data == true)
    {
      Serial.print(F("1s: "));
      for (int y = 0; y < NUM_CHANNELS; y++)
      {
        Serial.print((String)channels[y].data_1s); // Print the 1 second data
        Serial.print(F("\t :"));
      }
      Serial.print(F(" N: "));
      Serial.println(data_counter_1s);
    }

    // Every second we recheck the bits of the UNIT_ID
    bitWrite(UNIT_ID, 0, !digitalRead(GPIO_ID0));
    bitWrite(UNIT_ID, 1, !digitalRead(GPIO_ID1));
    bitWrite(UNIT_ID, 2, !digitalRead(GPIO_ID2));

    data_counter_10s ++;
    data_counter_1s = 0;   // Reset the counter
  }
}

void t10SCallback() {
  if (!t10S.isFirstIteration())
  {
    // 10 second averages
    for (int j = 0; j < NUM_CHANNELS; j++)
    {
      channels[j].data_10s = (float)channels[j].data_10s_holder / (float)data_counter_10s;
      // reset all the data holders
      channels[j].data_10s_holder  = 0;    // Reset the value
      // Add on values for next average
      channels[j].data_60s_holder += channels[j].data_10s;    // This is for the 60S averages
    }
    if (DEBUG_DATA_10S == true)
    {
      Serial.print(F("10s: "));
      for (int y = 0; y < NUM_CHANNELS; y++)
      {
        Serial.print((String)channels[y].data_10s); // Print the 1 second data
        Serial.print(F("\t : \t"));
      }
      Serial.print(F(" N: "));
      Serial.println(data_counter_10s);
    }
    data_counter_60s++;
    data_counter_10s = 0;
  }
}

void t60SCallback() {
  if (!t60S.isFirstIteration())
  {
    // 1 minute averages
    for (int j = 0; j < NUM_CHANNELS; j++)
    {
      channels[j].data_60s = (float)channels[j].data_60s_holder / (float)data_counter_60s;
      // reset all the data holders
      channels[j].data_60s_holder  = 0;
      // This is for the 600S averages
      channels[j].data_600s_holder += channels[j].data_60s;
    }
    if (DEBUG_DATA_60S == true)
    {
      Serial.print(F("60s: "));
      for (int y = 0; y < NUM_CHANNELS; y++)
      {
        Serial.print((String)channels[y].data_60s); // Print the 1 second data
        Serial.print(F("\t : \t"));
      }
      Serial.print(F(" N: "));
      Serial.println(data_counter_60s);
    }
    data_counter_600s++;
    data_counter_60s = 0;
  }
}

void t600SCallback() {
  // 10 minute averages
  if (!t600S.isFirstIteration())
  {
    for (int j = 0; j < NUM_CHANNELS; j++)
    {
      channels[j].data_600s = (float)channels[j].data_600s_holder / (float)data_counter_600s;
      // reset all the data holders
      channels[j].data_600s_holder  = 0;    // Reset the value
      // This is for the 3600S averages
      channels[j].data_3600s_holder += channels[j].data_600s;
    }

    if (DEBUG_DATA_600S == true)
    {
      Serial.print(F("600s: "));
      for (int y = 0; y < NUM_CHANNELS; y++)
      {
        Serial.print((String)channels[y].data_600s); // Print the 1 second data
        Serial.print(F("\t : \t"));
      }
      Serial.print(F(" N: "));
      Serial.println(data_counter_600s);
    }
  }
  data_counter_3600s++;
  data_counter_600s = 0;
}

void t3600SCallback() {
  // 1 hour averages
  // 10 minute averages
  if (!t3600S.isFirstIteration())
  {
    for (int j = 0; j < NUM_CHANNELS; j++)
    {
      // 1 hour averages
      channels[j].data_3600s = (float)channels[j].data_3600s_holder / (float)data_counter_3600s;
      // reset all the data holders
      channels[j].data_3600s_holder  = 0;    // Reset the value
    }

    if (DEBUG_DATA_3600S == true)
    {
      Serial.print(F("3600s: "));
      for (int y = 0; y < NUM_CHANNELS; y++)
      {
        Serial.print((String)channels[y].data_3600s); // Print the 1 second data
        Serial.print(F("\t : \t"));
      }
      Serial.print(F(" N: "));
      Serial.println(data_counter_3600s);
    }
  }
  data_counter_3600s = 0;
}

void tap(Button2 & btn)
{
  // In this routine we figure out which button has been pressed and deal with that:
  if (btn == buttonA)
  {
    // If SWA pressed then toggle the 'display 1s data' flag
    display_1s_data = !display_1s_data;
    // Set LED0 to whatever the display data flag is:
    digitalWrite(LED0_PIN, display_1s_data);
    if (DEBUG_FLAG == true && display_1s_data == true)
    {
      Serial.println(F("Displaying 1s data"));
    }
    else if (DEBUG_FLAG == true && display_1s_data == false)
    {
      Serial.println(F("Not displaying data"));
    }
  }
}

void flashLED()
{
  if (millis() > (led_flash_timer + LED_FLASH_TIME + LED_ON_TIME))
  {
    digitalWrite(LED0_PIN, display_1s_data);
    led_flash_timer = millis();
    led_update_flag = true;
  }
  if (millis() > (led_flash_timer + LED_FLASH_TIME) && led_update_flag == true)
  {
    digitalWrite(LED0_PIN, !display_1s_data);
    led_update_flag = false;
  }
}

// Start up
void setup() {

  // Read the serial baud rate set in EEPROM
  SERIAL_BAUD = EEPROM.read(10);
  if (SERIAL_BAUD >= MAX_BAUD_RATES)
  {
    SERIAL_BAUD = 2;  // Initialise to 9600 if data out of range
  }
  // initialize serial communication:
  Serial.begin(baud_rates[SERIAL_BAUD]);

  // reserve 100 bytes for the Strings:
  inputString.reserve(50);
  errorString.reserve(15);
  returnString.reserve(100);

  // Read in the digital pins to check the Unit ID
  // This reads in three digital pins to set the Unit ID
  // UNIT_ID is a 8 bit byte
  // So we can have up to 8 IDs
  pinMode(GPIO_ID0, INPUT_PULLUP);
  pinMode(GPIO_ID1, INPUT_PULLUP);
  pinMode(GPIO_ID2, INPUT_PULLUP);
  // Here we set the bits of the UNIT_ID
  bitWrite(UNIT_ID, 0, !digitalRead(GPIO_ID0));
  bitWrite(UNIT_ID, 1, !digitalRead(GPIO_ID1));
  bitWrite(UNIT_ID, 2, !digitalRead(GPIO_ID2));
  // This is re-checked every second or after reset
  if (DEBUG_FLAG == true)
  {
    Serial.print(F("ID is: "));
    Serial.println(UNIT_ID);
  }

  Wire.begin();   // Start the I2C bus
  delay(10);

  // Reset devices
  MCP342x::generalCallReset();
  delay(1); // MC342x needs 300us to settle, wait 1ms
  // Check device present
  Wire.requestFrom(address, (uint8_t)1);
  if (!Wire.available()) {
    Serial.print("No device found at address ");
    Serial.println(address, HEX);
  }
  

  // Flash LEDs for test
  pinMode(LED0_PIN, OUTPUT);
  digitalWrite(LED0_PIN, HIGH);
  delay(250);
  digitalWrite(LED0_PIN, LOW);
  delay(250);

  pinMode(SWA_PIN, INPUT_PULLUP);
  buttonA.setDebounceTime(1000);
  buttonA.setTapHandler(tap);

  // Set up Scheduler:
  runner.init();
  runner.addTask(t1);
  runner.addTask(t1S);
  runner.addTask(t10S);
  runner.addTask(t60S);
  runner.addTask(t600S);
  runner.addTask(t3600S);

  t1.enable();
  t1S.enable();
  t10S.enable();
  t60S.enable();
  t600S.enable();
  t3600S.enable();
  DEBUGLN(DEBUG_FLAG, "Enabled Tasks");

  // set up the watch dog timer:
  wdt_enable(WDTO_2S);    // set for 2 seconds
}

// Main Loop
void loop()
{
  // Deal with schedules tasks
  runner.execute();
  // Check buttons for input
  buttonA.loop();
  // This flashes the LEDs as needed...
  flashLED();
  // feed the WDT
  wdt_reset();

  // Check for serial data
  if (stringComplete == true)
  {
    // This means we have had some data come in:
    // So parse it to find id and ave
    errorString = checkData.parseData(inputString, UNIT_ID, channels);

    if (checkData.error_flag == true)
    {
      Serial.println(errorString);    // This needs to be returned
      checkData.error_flag = false;
    }
    else
    {
      if (checkData.baud_return_flag == true)
      {
        // Here we return the baud rate
        returnString = "aaBD";
        returnString += baud_rates[SERIAL_BAUD];
        returnString += "#";
        checkData.baud_return_flag = false;
      }
      else if (checkData.baud_set_flag == true)
      {
        Serial.end();
        // Here we set the baud rate to a new value and store in EEPROM
        returnString = "aaSTBD";
        // Read the serial baud rate set in EEPROM
        SERIAL_BAUD = EEPROM.read(10);
        if (SERIAL_BAUD >= MAX_BAUD_RATES)
        {
          SERIAL_BAUD = 2;  // Initialise to 9600 if data out of range
        }
        // re-initialize serial communication:
        Serial.begin(baud_rates[SERIAL_BAUD]);
        returnString += baud_rates[SERIAL_BAUD];
        returnString += "#";
        checkData.baud_set_flag = false;
      }
      else if (checkData.data_sent_flag == true)
      {
        if (checkData.data_all_flag == true)
        {
          //******** RETURN ALL DATA FOR AVE *************************
          DEBUGLN(DEBUG_FLAG, "Return ALL DATA");
          returnString = "aaRAAA" + (String)checkData.ave_time; // Initialise the returned string
          for (int c = 0; c < 5; c++)
          {
            if (checkData.ave_time == c)
            {
              switch (c)
              {
                case 0:
                  for (int j = 0; j < NUM_CHANNELS; j++)
                  {
                    returnString += ":";
                    returnString += (String)channels[j].data_1s;
                  }
                  break;
                case 1:
                  for (int j = 0; j < NUM_CHANNELS; j++)
                  {
                    returnString += ":";
                    returnString += (String)channels[j].data_10s;
                  }
                  break;
                case 2:
                  for (int j = 0; j < NUM_CHANNELS; j++)
                  {
                    returnString += ":";
                    returnString += (String)channels[j].data_60s;
                  }
                  break;
                case 3:
                  for (int j = 0; j < NUM_CHANNELS; j++)
                  {
                    returnString += ":";
                    returnString += (String)channels[j].data_600s;
                  }
                  break;
                case 4:
                  for (int j = 0; j < NUM_CHANNELS; j++)
                  {
                    returnString += ":";
                    returnString += (String)channels[j].data_3600s;
                  }
                  break;
              }
            }
          }
          returnString += "#";
          checkData.data_all_flag = false;
        }
        else if (checkData.data_min_flag == true)
        {
          //******** RETURN ALL MINIMUMS *************************
          DEBUGLN(DEBUG_FLAG, "Return ALL MINIMUMS");
          returnString = "aaRMN"; // Initialise the returned string
          for (int j = 0; j < NUM_CHANNELS; j++)
          {
            returnString += ":";
            returnString += (String)channels[j].data_min;
          }
          returnString += "#";
          checkData.data_min_flag = false;
        }
        else if (checkData.data_max_flag == true)
        {
          //******** RETURN ALL MAXIMUMS  *************************
          DEBUGLN(DEBUG_FLAG, "Return ALL MAXIMUMS");
          returnString = "aaRMX"; // Initialise the returned string
          for (int j = 0; j < NUM_CHANNELS; j++)
          {
            returnString += ":";
            returnString += (String)channels[j].data_max;
          }
          returnString += "#";
          checkData.data_max_flag = false;
        }
        else
        {
          //******** RETURN DATA FOR 1 CHANNEL *************************
          // If we are here then we have had valid unit ID, channel ID and AVE are correct.
          // So need to create the correct return string
          DEBUG(DEBUG_FLAG, ("Channel: " + (String)checkData.id + " AVE is: " + (String)checkData.ave_time + " Data: "));
          // the id must be < NUM_CHANNELS
          // the ave_time must be within the array_averages
          // If that i the case return the correct value.
          if (checkData.id >= 0 && checkData.id < NUM_CHANNELS)
          {
            returnString = "aaR"; // Initialise the returned string
            if (checkData.id < 10)
            {
              returnString = returnString + "0" + (String)checkData.id;
            }
            else
            {
              returnString = returnString + (String)checkData.id;
            }
            for (int c = 0; c < 5; c++)
            {
              if (checkData.ave_time == c)
              {
                uint32_t data_reply;
                // If here then the AVE is right!!
                switch (c)
                {
                  case 0:
                    data_reply = channels[checkData.id].data_1s;
                    break;
                  case 1:
                    data_reply = channels[checkData.id].data_10s;
                    break;
                  case 2:
                    data_reply = channels[checkData.id].data_60s;
                    break;
                  case 3:
                    data_reply = channels[checkData.id].data_600s;
                    break;
                  case 4:
                    data_reply = channels[checkData.id].data_3600s;
                    break;
                }
                returnString = returnString + "A" + (String)data_reply;
                returnString = returnString + "MN" + (String)channels[checkData.id].data_min;
                returnString = returnString + "MX" + (String)channels[checkData.id].data_max + "#";
                DEBUGLN(DEBUG_FLAG, (String)data_reply);    // Print the 1 second data value from the checkData id
                checkData.data_sent_flag = false;
              }
            }
            if (checkData.data_sent_flag == true)
            {
              Serial.println(F("aaFAILAV#"));    // This needs to be returned
              returnString = F("aaFAILAV#");
              checkData.data_sent_flag = false;
            }
          }
        }
      }
      else if (checkData.data_reset_flag == true)
      {
        returnString = F("aaRESET#");   // This needs to be returned
        checkData.data_reset_flag = false;
        checkData.data_sent_flag = false;
      }
      else
      {
        Serial.println(F("aaFAILID#"));    // This needs to be returned
        returnString = F("aaFAILID#");
        checkData.data_sent_flag = false;
      }
      DEBUGLN(DEBUG_FLAG, "Returned string:");
      Serial.println(returnString);
    }
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent()
{
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
