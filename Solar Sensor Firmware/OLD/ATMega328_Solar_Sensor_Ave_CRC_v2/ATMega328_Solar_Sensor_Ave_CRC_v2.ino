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

   Serial commands you can use:

   REQUEST: Get data:    “aaI0SSA?#” where ? is the averaging number from 0-4.
   Averaging number: 0 = 1 second, 1 = 10 second, 2 = 60 second, 3 = 600 second (10 min), 4 = 3600 second (1hr)
   RETURNED: "aaI0SSA1:28.51:28.60:28.50:18.00#"
   where the first number (between semi-colons) is the average, 2nd number is the Maximum (until a reset is done),
   3rd number is the Minimum and 4th number is the temperature.
   Temperature has a resolution of 0.5 C.
   Response will include the averaging number.

   REQUEST: Get Maximum:    “aaI0SSMX#”
   RETURNED: "aaI0SSMX:28.90#" where the number after semi-colon is the maximum

   REQUEST: Get Miniimum:    “aaI0SSMN#”
   RETURNED: "aaI0SSMN:27.90#" where the number after semi-colon is the minimum

   REQUEST: Reset Min & Max:    “aaI0RESET#”
   RETURNED: Nothing
   This will reset the maximum and minimum values

   REQUEST:   What is baud rate?:  "aaI0BD#"
   RETURNED:  "aaI0BD9600#" Where the number between D and # is the baud rate.
   This is stored in EEPROM so will stay the same even on power down.

   REQUEST:  Set Baud Rate:   "aaI0STBD*#"  Where * is 0,1,2,3,4 for 1200, 2400, 9600, 57600, 115200
   RETURNED: "aaI0STBD9600#"  Where the number between D and # is the baud rate.

   REQUEST: What is ID?:   "aaI?#"      Mentioned at start up of unit as well - its solder-programmed... cannot be changed in code.
   RETURNED: "aaIx#" where x is the ID (from the soldered ID pads. Default is 0);
   The ID can be set using the soldered pads from 0-7.
   The default (no pads soldered) is an ID of 0.
   Other combinations are (X = not soldered, = = soldered):
   A0     A1    A2    ID
   X      X     X     0
   =      X     X     1
   X      =     X     2
   =      =     X     3
   X      X     =     4
   =      X     =     5
   X      =     =     6
   =      =     =     7

  Data conversion:
  The unit has a linear y=mx+c type conversion applied to the solar data (to scale and offset).
  So the output value (y) will be the voltage read (x) multiplied by m and then adding c
  The values for m and c are stored in EEPROM
  They can be requested and adjusted as stated here:

  REQUEST:  "aaI0SSCON#"    Ask for the stored conversion values
  RETURNED: "aaI0SSCONm10.00c0.00#"  With the numbers after m and c being the conversion values

  REQUEST:  "aaI0SSSETm123.4c567.89#"    SET the stored conversion values
  RETURNED: "aaI0SSSETm123.4c567.89#"     With the numbers after m and c being the conversion values

  Send data for checking/display:

  REQUEST:  "aaI0SEND?#" where ? is the averaging number from 0-5.
  Averaging number: 0 = 1 second, 1 = 10 second, 2 = 60 second,
  3 = 600 second (10 min), 4 = 3600 second (1hr), 5 = STOP send
  RETURNED: "aaI0SENDON#" or "aaI0SENDOFF#
  Then at regular intervals
  RETURNED: "aaI0SSA?:9.00:9.00:9.00:19.00#"  Data will be returned at the averaging period.

  If you press the SWA button for about 0.5-1 second then the unit will also enter SEND data mode.
  It will cycle through the send averaging numbers from 0 = 1 second, 1 = 10 second, 2 = 60 second,
  3 = 600 second (10 min), 4 = 3600 second (1hr), 5 = STOP send
  This will loop back around. 0 -> 5 -> 0
  The LED will flash 1 time for 0, 2 for 1, 3 for 2, 4 for 3 and 5 for 4 (I know!) and then one long led light for OFF.

  Pressing and holding the button for > 3 seconds will set the unit directly into OFF

   **Temperature Compensation
   The output from the photo diode will depend upon temperature.
   Need to know the temperature variation from the photo diode datasheet
   Using a: SFH203 T1 3/4 PHOTODIODE (UNFILTERED) RC
   Datasheet here: https://www.osram.com/ecat/Radial%20T1%203-4%20SFH%20203/com/en/class_pim_web_catalog_103489/prd_pim_device_2219554/
   This comes from the light sensor datasheet. I have settled on the SFH-203 from OSRAM. This is rated at 25C and has coefficients for voltage and short circuit current.
   We are using the short circuit current which is measured by the op-amp.
   The temperature coefficient of the short circuit current is 0.18 % / K.
   So to compensate the reading for temperature we need to adjust up/down depending upon the temperature.
   The adjustment is: Adjustment = (LM75B temperature - 25) * 0.18 %
   We then need to apply this factor to our irradiance value: Real irradiance = Measured Value - Measured Value * (Adjustment / 100)
   There is the "APPLY_TEMP_COMP" flag in the config to say if this is applied or not


  **Analog Output
  Only have 256 levels for the analog output.
  Need to know Vcc to get absolute value
  This gives headroom for > 1000W/m2
  Can output up to MAX_IRRADIANCE W/m2 MAX
  Example: So 1000 W/m2 = 256*1000/MAX_IRRADIANCE = 128 = Vcc/ 2 (for MAX_IRRADIANCE = 2000 W/m2)
  Example: So 100 W/m2 = 256*100/MAX_IRRADIANCE = 12.8 (or 12 in discrete levels) (for MAX_IRRADIANCE = 2000 W/m2)
  Adjust the PWM according to this.
  solar_data.data_1s is the float value in W/m2
  So PWM value is:
  PWM_float = ( 256.0 * solar_data.data_1s ) / (float)MAX_IRRADIANCE;
  Then convert to an INT
  analogWrite(ANALOG_OUT_PIN, PWM_float);

   Details on the design of this device are here:
   https://www.re-innovation.co.uk/docs/low-cost-diy-solar-irradiance-sensor-for-pv-system-monitoring/

   Please see the github rpository readme for all the serial commands available.
   https://github.com/curiouselectric/SolarSensor

   To program it then MiniCore is used:
   // For optiboot using 3.3V and 8MHz and with WDT we need to sort out new code:
   Easiest method is:
   Install MiniCore from here: https://github.com/MCUdude/MiniCore
   Add https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json to preferences and then board manager.

   Use minicore to burn the bootloader with an Arduino as an ISP using the 'Burn Bootloader' option

*/

#include <stdio.h>
#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>       // for saving mode to EEPROM
#include <avr/wdt.h>      // for the watch dog timer

// For the LM75 I2C temperature sensor:
// https://github.com/jeremycole/Temperature_LM75_Derived
#include <Temperature_LM75_Derived.h>

//For the MCP3426 ADC I2C sensor:
// https://github.com/stevemarple/MCP342x
#include <MCP342x.h>


#include "Button2.h"      // Need to include this to the library
#include "config.h"
#include "serial_parse.h"
#include "solar_data.h"
#include "crc_check.h"

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
                                   1000000, dataValue, status);
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
    // ******* Apply temperature compensation? *************************
    if (APPLY_TEMP_COMP == true)
    {
      // Applying temperature compensation here:
      float Adjust_percent = (solar_data.sensor_temperature - RATED_TEMP) * TEMP_COMP_VAL;
      float Irradiance_tcomp = solar_data.data_1s - (solar_data.data_1s * (Adjust_percent / 100.0));
      solar_data.data_1s = Irradiance_tcomp;
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
      //reset_data();   // Resets Max and Min for each send cycle - uncomment if this is needed
    }

    // Every second we recheck the bits of the UNIT_ID
    bitWrite(UNIT_ID, 0, !digitalRead(GPIO_ID0));
    bitWrite(UNIT_ID, 1, !digitalRead(GPIO_ID1));
    bitWrite(UNIT_ID, 2, !digitalRead(GPIO_ID2));

    // Here we write the PWM to the output. from 0-255
    float PWM_float = ( 256.0 * solar_data.data_1s ) / (float)MAX_IRRADIANCE;
    analogWrite(ANALOG_OUT_PIN, (int)PWM_float);

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
  unsigned int time = btn.wasPressedFor();
  if (time > 3000)
  {
    // This is a long press
    // Instantly set send_solar_data to 5 (SEND OFF):
    solar_data.send_solar_data = 5;
    EEPROM.write(SEND_ID_EEPROM_LOC, solar_data.send_solar_data);  // Update the EEPROM
  }
  else
  {
    // If SWA pressed then increment the "send_solar_data" from 0-1-2-3-4-5 and back to 0.
    // This means data will be shown at 1s/10s/60s/600s/3600s timescales.

    // In this case we start to send data at regular intervals.
    solar_data.send_solar_data++;
    if (solar_data.send_solar_data > 5)
    {
      solar_data.send_solar_data = 0;
    }
    EEPROM.write(SEND_ID_EEPROM_LOC, solar_data.send_solar_data);  // Update the EEPROM
  }

  if (solar_data.send_solar_data < 5)
  {
    returnString = F("aaSEND");
    returnString += solar_data.send_solar_data;
    if (ADD_CRC_CHECK)
    {
      // Add the CRC here: This adds the ? the CRC and the # to the end
      returnString = add_CRC(returnString);
    }
    else
    {
      returnString += "#";
    }
    Serial.println(returnString);
    // Also want to flash the LED to show what send mode the unit is in:
    for (int i = 0; i < (solar_data.send_solar_data + 1); i++)
    {
      digitalWrite(LED0_PIN, true);
      delay(100);
      digitalWrite(LED0_PIN, false);
      delay(200);
    }
  }
  else
  {
    returnString = F("aaSENDOFF");
    if (ADD_CRC_CHECK)
    {
      // Add the CRC here: This adds the ? the CRC and the # to the end
      returnString = add_CRC(returnString);
    }
    else
    {
      returnString += "#";
    }
    Serial.println(returnString);
    digitalWrite(LED0_PIN, true);   // Long pulse ON
    delay(1000);
    digitalWrite(LED0_PIN, false);
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
  SERIAL_BAUD = EEPROM.read(BAUD_RATE_EEPROM_LOC);
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
  // But if they are NAN then initialise the values

  EEPROM.get(CONV_M_EEPROM_LOC, solar_data.solar_conv_m);
  //check for NAN
  if (isnan(solar_data.solar_conv_m))
  {
    solar_data.solar_conv_m = M_CONV_INIT;
    EEPROM.put(CONV_M_EEPROM_LOC, solar_data.solar_conv_m);
  }
  EEPROM.get(CONV_C_EEPROM_LOC, solar_data.solar_conv_c);
  //check for NAN
  if (isnan(solar_data.solar_conv_c))
  {
    solar_data.solar_conv_c = C_CONV_INIT;
    EEPROM.put(CONV_C_EEPROM_LOC, solar_data.solar_conv_c);
  }


  // Get the control int for sending data to serial port
  // This is for constant output data
  // Set this to 5 if not set previously..
  if (EEPROM.read(SEND_ID_EEPROM_LOC) < 0 || EEPROM.read(SEND_ID_EEPROM_LOC) > 5)
  {
    EEPROM.write(5, SEND_ID_EEPROM_LOC);
  }
  solar_data.send_solar_data = EEPROM.read(SEND_ID_EEPROM_LOC);


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
    Serial.print(UNIT_ID);
    Serial.print(F(" BD: "));
    Serial.println(baud_rates[SERIAL_BAUD]);
  }

  Wire.begin();   // Start the I2C bus
  delay(10);

  // Reset devices
  MCP342x::generalCallReset();
  delay(5); // MC342x needs 300us to settle, wait 1ms

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
  buttonA.setDebounceTime(50);
  buttonA.setTapHandler(tap);

  pinMode(ANALOG_OUT_PIN, OUTPUT);  // sets the ANALOG_OUT_PIN as output
  analogWrite(ANALOG_OUT_PIN, 0);   // set PWM off

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
      if (ADD_CRC_CHECK)
      {
        // Add the CRC here: This adds the ? the CRC and the # to the end
        errorString = add_CRC(errorString);
      }
      else
      {
        errorString += "#";
      }
      if (DEBUG_FLAG == true)
      {
        Serial.println(errorString);    // This needs to be returned only in debug mode!
      }
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
        //returnString += END_STR;
        checkData.baud_return_flag = false;
        checkData.data_sent_flag = false;
      }
      else if (checkData.id_return_flag == true)
      {
        // Return the ID of the unit
        returnString = "aaI";
        returnString += (String)UNIT_ID;
        //returnString += "#";
        checkData.id_return_flag = false;
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
        //returnString += END_STR;
        checkData.conversion_return_flag = false;
        checkData.data_sent_flag = false;
      }
      else if (checkData.conversion_set_flag == true)
      {
        // Return conversion settings "aaI0STWSCONm123.4c567.89#"
        solar_data.solar_conv_m = checkData.solar_conv_m;
        solar_data.solar_conv_c = checkData.solar_conv_c;
        // Store this data to EEPROM
        EEPROM.put(CONV_M_EEPROM_LOC, solar_data.solar_conv_m);
        EEPROM.put(CONV_C_EEPROM_LOC, solar_data.solar_conv_c);
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

        Serial.end();  // STOP the serial and restart at new baud rate
        // Here we set the baud rate to a new value and store in EEPROM

        returnString = START_STR;
        returnString += (String)UNIT_ID;
        returnString += "STBD";
        // Read the serial baud rate set in EEPROM
        SERIAL_BAUD = EEPROM.read(BAUD_RATE_EEPROM_LOC);
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
        solar_data.send_solar_data = EEPROM.read(SEND_ID_EEPROM_LOC);
        if (solar_data.send_solar_data < 5)
        {
          returnString = F("aaSENDON#");
        }
        else
        {
          returnString = F("aaSENDOFF#");
        }
        checkData.send_data_flag = false;
        checkData.data_sent_flag = false;
      }
      else
      {
        // Do not want anything sent back here when connected to logger:
        if (DEBUG_FLAG == true)
        {
          returnString = F("aaFAILCRC");
        }
        checkData.data_sent_flag = false;
      }


      if (ADD_CRC_CHECK)
      {
        // Add the CRC here: This adds the ? the CRC and the # to the end
        returnString = add_CRC(returnString);
      }
      else
      {
        returnString += END_STR;
      }

      DEBUGLN(DEBUG_FLAG, "Returned string:");
      if (returnString != FAIL_STR)
      {
        Serial.println(returnString);
      }
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
  char buff[10];
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
          dtostrf(solar_data.data_1s, 2, 1, buff);  //2 is mininum width, 1 is precision
          break;
        case 1:
          dtostrf(solar_data.data_10s, 2, 1, buff);  //2 is mininum width, 1 is precision
          //snprintf (buff, sizeof(buff), "%f", solar_data.data_10s);
          //returnString += (String)solar_data.data_10s;
          break;
        case 2:
          dtostrf(solar_data.data_60s, 2, 1, buff);  //2 is mininum width, 1 is precision
          //returnString += (String)solar_data.data_60s;
          break;
        case 3:
          dtostrf(solar_data.data_600s, 2, 1, buff);  //2 is mininum width, 1 is precision
          //snprintf (buff, sizeof(buff), "%f", solar_data.data_600s);
          //returnString += (String)solar_data.data_600s;
          break;
        case 4:
          dtostrf(solar_data.data_3600s, 2, 1, buff);  //2 is mininum width, 1 is precision
          //snprintf (buff, sizeof(buff), "%f", solar_data.data_3600s);
          //returnString += (String)solar_data.data_3600s;
          break;
      }
      returnString += buff;
    }
  }

  returnString += ":";
  dtostrf(solar_data.data_max, 2, 1, buff);  //2 is mininum width, 1 is precision
  returnString += (String)buff;
  returnString += ":";
  dtostrf(solar_data.data_min, 2, 1, buff);  //2 is mininum width, 1 is precision
  returnString += (String)buff;
  returnString += ":";
  dtostrf(solar_data.sensor_temperature, 2, 1, buff);  //2 is mininum width, 1 is precision
  returnString += (String)buff;
  if (ADD_CRC_CHECK)
  {
    // Add the CRC here: This adds the ? the CRC and the # to the end
    returnString = add_CRC(returnString);
  }
  else
  {
    returnString += END_STR;
  }

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
