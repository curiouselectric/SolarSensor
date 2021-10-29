/*
   Solar Sensor Averaging firmware for ATMega328
   by:    Matt Little
   date:  27/10/2021
   w:     www.curiouselectric.co.uk
   e:     hello@curiouselectric.co.uk

   This code is for an ATMega328 unit solar sensor unit.
   This uses an ATMega328 running at 8MHz with 3.3v or 5V supply.

   It returns the average values when requested on serial port.
   Or it broadcasts solar speed and direction data at set intervals.
   At all other times then the unit is asleep.

   More construction details are here:
   *** UPDATE ***

   Details on this construction are here:
   *** UPDATE ****

   Please see the github rpository readme for all the serial commands available.

   To program it then MiniCore is used:
   // For optiboot using 3.3V and 8MHz and with WDT we need to sort out new code:
   Easiest method is:
   Install MiniCore from here: https://github.com/MCUdude/MiniCore
   Add to preferences and then board manager.

   Use minicore to burn the bootloader with an Arduino as an ISP using the 'Burn Bootloader' option

  Optiboot can also be used as the bootlloader:
  Need to download optiboot5a from here:
  https://code.google.com/archive/p/optiboot/downloads
  Install optiboot_atmega328.hex into a folder called "optiboot5a" in the hardware section
  Use this optiboot hex file for upload to the ATmega328
  Fuses are: Low = 0xFF, High = 0xDE, Extended = 0xFE

  Based on:
  http://www.arduino.cc/en/Tutorial/SerialEvent

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
#include "solar_data.h"


#include "utilitiesDL.h"
// 0x68 is the default address for all MCP342x devices
MCP342x adc = MCP342x(MCP_ADDRESS);

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
data_channel solar_data;    // This creates our data channels


// *********** These are global variables ***************************
String        inputString = "";           // a String to hold incoming data
String        errorString = "";           // a String to hold incoming data
String        returnString = "";          // A string to hold the returned data
bool          stringComplete = false;     // Checks if the string is complete
byte          UNIT_ID = B00000000;        // This is the unit_id of the board itself. This will be default value. Values from 0-255 can potentially be used. 4 bit binary number? = 16 channels.

uint32_t      led_flash_timer = millis();
bool          led_update_flag = true;
uint8_t       led_flash_counter = 0;        // Number of flashes to do
int           vane_training_direction = 0;    // This is used for the vane training mode

volatile int  data_counter_1s = 0;
volatile int  data_counter_10s = 0;
volatile int  data_counter_60s = 0;
volatile int  data_counter_600s = 0;
volatile int  data_counter_3600s = 0;
long int      debounce_time = millis();

void t1Callback() {
  // This loop runs every 100mS
  // This will record the value and store it

  // Check the sensor data
  long dataValue = 0;

  MCP342x::Config status;
  // Initiate a conversion; convertAndRead() will wait until it can be read
  uint8_t err = adc.convertAndRead(MCP342x::channel1, MCP342x::oneShot,
                                   MCP342x::resolution16, MCP342x::gain1,
                                   1000, dataValue, status);
  if (err)
  {
    // If there is an ADC error, highlight it and dont read the data into the unit
    Serial.print(F("MCP ERR:"));
    Serial.println(err);
  }
  else
  {
    // Otherwise store data and increment data counter
    solar_data.data_1s_holder += dataValue;
    // It will then be averaged for 1s, 10s, 60s 10min and 1 hour averages
    data_counter_1s++;   // This counts the correct number of samples we take within the 1S sample period. Used for averaging.
  }
}

void t1SCallback() {
  if (!t1S.isFirstIteration())
  {
    // Average the solar sensor data
    solar_data.data_1s = (float) solar_data.data_1s_holder / (float) data_counter_1s;

    // We only read the temperature every second - used for calibration?
    solar_data.sensor_temperature = (temperature.readTemperatureC()); // The value is a float

    // ******** Convert raw ADC reading into Irradiance ****************
    // Here we want to convert the data into real irradiance:
    // Values are large so its actually y = x/m +c conversion
    solar_data.data_1s = (solar_data.data_1s / solar_data.solar_conv_m) + solar_data.solar_conv_c;

    if (solar_data.data_1s < 0)
    {
      // Do not get negative irradiances! So set this to zero
      solar_data.data_1s = 0;
    }
    // ****************** END Conversion *******************************
    
    // Here we set the max and min for the sensor data
    if (solar_data.data_1s < solar_data.data_min)
    {
      solar_data.data_min = solar_data.data_1s;
    }
    if (solar_data.data_1s > solar_data.data_max)
    {
      solar_data.data_max = solar_data.data_1s;
    }

    // reset the data holder
    solar_data.data_1s_holder  = 0;    // Reset the value
    solar_data.data_10s_holder += solar_data.data_1s; // Increment the 10s average

    // Here we want to check if we are regularly sending the data and send if needed:
    if (solar_data.send_solar_data == 0)
    {
      sendData(0, true);
      reset_data();
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
    solar_data.data_10s = (float) solar_data.data_10s_holder / (float) data_counter_10s;
    // reset all the data holders
    solar_data.data_10s_holder  = 0;    // Reset the value
    // Add on values for next average
    solar_data.data_60s_holder += solar_data.data_10s;    // This is for the 60S averages

    // Here we want to check if we are regularly sending the data and send if needed:
    if (solar_data.send_solar_data == 1)
    {
      sendData(1, true);
      reset_data();
    }
    data_counter_60s++;
    data_counter_10s = 0;
  }
}

void t60SCallback() {
  if (!t60S.isFirstIteration())
  {
    // 1 minute averages
    solar_data.data_60s = (float)solar_data.data_60s_holder / (float)data_counter_60s;
    // reset all the data holders
    solar_data.data_60s_holder  = 0;
    // This is for the 600S averages
    solar_data.data_600s_holder += solar_data.data_60s;

    // Here we want to check if we are regularly sending the data and send if needed:
    if (solar_data.send_solar_data == 2)
    {
      sendData(2, true);
      reset_data();
    }
    data_counter_600s++;
    data_counter_60s = 0;
  }
}

void t600SCallback() {
  // 10 minute averages
  if (!t600S.isFirstIteration())
  {
    solar_data.data_600s = (float)solar_data.data_600s_holder / (float)data_counter_600s;
    // reset all the data holders
    solar_data.data_600s_holder  = 0;    // Reset the value
    // This is for the 3600S averages
    solar_data.data_3600s_holder += solar_data.data_600s;

    // Here we want to check if we are regularly sending the data and send if needed:
    if (solar_data.send_solar_data == 3)
    {
      sendData(3, true);
      reset_data();
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
    // 1 hour averages
    solar_data.data_3600s = (float)solar_data.data_3600s_holder / (float)data_counter_3600s;
    // reset all the data holders
    solar_data.data_3600s_holder  = 0;    // Reset the value

    // Here we want to check if we are regularly sending the data and send if needed:
    if (solar_data.send_solar_data == 4)
    {
      sendData(4, true);
      reset_data();
    }
  }
  data_counter_3600s = 0;
}


void tap(Button2 & btn)
{
  // In this routine we figure out which button has been pressed and deal with that:
  if (btn == buttonA)
  {
    // If SWA pressed then increment the "send_solar_data" from 0-1-2-3-4-5 and back to 0.
    // This means data will be shown at 1s/10s/60s/600s/3600s timescales.

    // In this case we start to send data at regular intervals.
    solar_data.send_solar_data++;
    if (solar_data.send_solar_data >= 6)
    {
      solar_data.send_solar_data = 0;
    }
    EEPROM.write(120, solar_data.send_solar_data);  // Update the EEPROM
    Serial.print(F("aaSEND"));
    Serial.print(solar_data.send_solar_data);
    Serial.println("#");

    // Also want to flash the LED to show what send mode the unit is in:
    for (int i = 0; i < solar_data.send_solar_data; i++)
    {
      digitalWrite(LED0_PIN, true);
      delay(250);
      digitalWrite(LED0_PIN, false);
      delay(250);
    }
  }
}

void flashLED()
{

  if (millis() > (led_flash_timer + LED_FLASH_TIME))
  {
    digitalWrite(LED0_PIN, true);
    led_flash_timer = millis();
    led_update_flag = true;
  }
  if (millis() > (led_flash_timer + LED_ON_TIME) && led_update_flag == true)
  {
    digitalWrite(LED0_PIN, !digitalRead(LED0_PIN));
    if (solar_data.send_solar_data > 4 || led_flash_counter > 2)
    {
      digitalWrite(LED0_PIN, false);
      led_update_flag = false;
      led_flash_counter = 0;
    }
    else
    {
      led_flash_counter++;
    }
    led_flash_timer = millis();
  }
}

// Start up
void setup() {

  // Read the serial baud rate set in EEPROM
  SERIAL_BAUD = EEPROM.read(4);
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

  // Get the m and c wind speed conversion data
  EEPROM.get(100, solar_data.solar_conv_m);
  EEPROM.get(110, solar_data.solar_conv_c);

  // Get the control int for sending data to serial port
  // This is for constant output data
  solar_data.send_solar_data = EEPROM.read(120);

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
  Wire.requestFrom(MCP_ADDRESS, (uint8_t)1);
  if (!Wire.available()) {
    Serial.print(F("No Device:"));
    Serial.println(MCP_ADDRESS, HEX);
  }

  // Flash LEDs for test
  pinMode(LED0_PIN, OUTPUT);
  digitalWrite(LED0_PIN, HIGH);
  delay(100);
  digitalWrite(LED0_PIN, LOW);
  // Set up the HC12 power output
  pinMode(HC12_PWR_PIN, OUTPUT);
  digitalWrite(HC12_PWR_PIN, LOW);

  digitalWrite(LED0_PIN, HIGH);
  delay(100);
  digitalWrite(LED0_PIN, LOW);

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
    errorString = checkData.parseData(inputString, UNIT_ID, solar_data);

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
        returnString = "aaI";
        returnString += (String)UNIT_ID;
        returnString += "BD";
        returnString += baud_rates[SERIAL_BAUD];
        returnString += END_STR;
        checkData.baud_return_flag = false;
        checkData.data_sent_flag = false;
      }
      else if (checkData.conversion_return_flag == true)
      {
        // Return conversion settings "aaI0STSSCONm123.4c567.89#"
        returnString = START_STR;
        returnString += (String)UNIT_ID;
        returnString += "SSCONm";
        returnString += (String)solar_data.solar_conv_m;
        returnString += "c";
        returnString += (String)solar_data.solar_conv_c;
        returnString += END_STR;
        checkData.conversion_return_flag = false;
        checkData.data_sent_flag = false;
      }
      else if (checkData.conversion_set_flag == true)
      {
        // Return conversion settings "aaI0STWSCONm123.4c567.89#"
        solar_data.solar_conv_m = checkData.solar_conv_m;
        solar_data.solar_conv_c = checkData.solar_conv_c;
        // Store this data to EEPROM
        EEPROM.put(100, solar_data.solar_conv_m);
        EEPROM.put(110, solar_data.solar_conv_c);
        returnString = START_STR;
        returnString += (String)UNIT_ID;
        returnString += "SSSETm";
        returnString += (String)solar_data.solar_conv_m;
        returnString += "c";
        returnString += (String)solar_data.solar_conv_c;
        returnString += END_STR;
        checkData.conversion_set_flag = false;
        checkData.data_sent_flag = false;
      }
      else if (checkData.baud_set_flag == true)
      {
        Serial.end();
        // Here we set the baud rate to a new value and store in EEPROM
        returnString = START_STR;
        returnString += (String)UNIT_ID;
        returnString += "STBD";
        // Read the serial baud rate set in EEPROM
        SERIAL_BAUD = EEPROM.read(10);
        if (SERIAL_BAUD >= MAX_BAUD_RATES)
        {
          SERIAL_BAUD = 2;  // Initialise to 9600 if data out of range
        }
        // re-initialize serial communication:
        Serial.begin(baud_rates[SERIAL_BAUD]);
        returnString += baud_rates[SERIAL_BAUD];
        returnString += END_STR;
        checkData.baud_set_flag = false;
        checkData.data_sent_flag = false;
      }
      else if (checkData.data_sent_flag == true)
      {
        if (checkData.data_all_flag == true)
        {
          //******** RETURN ALL DATA FOR AVE *************************
          DEBUGLN(DEBUG_FLAG, "Return ALL DATA");
          sendData(checkData.ave_time, false);
          checkData.data_all_flag = false;
          checkData.data_sent_flag = false;
        }
        else if (checkData.data_min_flag == true)
        {
          //******** RETURN ALL MINIMUMS *************************
          DEBUGLN(DEBUG_FLAG, "Return ALL MINIMUMS");
          returnString = START_STR;
          returnString += (String)UNIT_ID;
          returnString += "SSMN"; // Initialise the returned string
          returnString += ":";
          returnString += (String)solar_data.data_min;
          returnString += END_STR;
          checkData.data_min_flag = false;
          checkData.data_sent_flag = false;
        }
        else if (checkData.data_max_flag == true)
        {
          //******** RETURN ALL MAXIMUMS  *************************
          DEBUGLN(DEBUG_FLAG, "Return ALL MAXIMUMS");
          returnString = START_STR;
          returnString += (String)UNIT_ID;
          returnString += "SSMX"; // Initialise the returned string
          returnString += ":";
          returnString += (String)solar_data.data_max;
          returnString += END_STR;
          checkData.data_max_flag = false;
          checkData.data_sent_flag = false;
        }
      }
      else if (checkData.data_reset_flag == true)
      {
        // Want to reset the wind vane direction data as previous will be wrong!
        reset_data();
        returnString = F("aaRESET#");   // This needs to be returned
        checkData.data_reset_flag = false;
        checkData.data_sent_flag = false;
      }
      else if (checkData.send_data_flag == true)
      {
        // In this case we start to send data at regular intervals.
        solar_data.send_solar_data = EEPROM.read(120);
        returnString = F("aaSENDOK#");   // This needs to be returned
        checkData.send_data_flag = false;
        checkData.data_sent_flag = false;
      }
      else
      {
        returnString = FAIL_STR;
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

void sendData(int average_time, bool send_serial)
{
  // Send 1 second data
  digitalWrite(HC12_PWR_PIN, HIGH);
  delay(POWER_SETTLE_TIME);  // short settling delay
  returnString = START_STR;
  returnString += (String)UNIT_ID;
  returnString += "SSA";
  returnString += (String)average_time;
  returnString += ":";
  for (int c = 0; c < 5; c++)
  {
    if (average_time == c)
    {
      switch (c)
      {
        case 0:
          returnString += (String)solar_data.data_1s;
          break;
        case 1:
          returnString += (String)solar_data.data_10s;
          break;
        case 2:
          returnString += (String)solar_data.data_60s;
          break;
        case 3:
          returnString += (String)solar_data.data_600s;
          break;
        case 4:
          returnString += (String)solar_data.data_3600s;
          break;
      }
    }
  }
  returnString += ":";
  returnString += (String)solar_data.data_max;
  returnString += ":";
  returnString += (String)solar_data.data_min;
  returnString += ":";
  returnString += (String)solar_data.sensor_temperature;
  returnString += END_STR;
  if (send_serial == true)
  {
    Serial.println(returnString);
  }
  delay(POWER_SETTLE_TIME);  // short settling delay
  digitalWrite(HC12_PWR_PIN, LOW);
}

void reset_data()
{
  solar_data.data_min = 99999.9;
  solar_data.data_max = 0.0;  // Assumed no negative values
}