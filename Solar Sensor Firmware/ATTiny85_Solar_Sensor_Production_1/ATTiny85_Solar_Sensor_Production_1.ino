/*
   Solar Sensor firmware for ATTin85
   by:    Matt Little
   date:  20/6/2021
   w:     www.curiouselectric.co.uk
   e:     hello@curiouselectric.co.uk

   This code is for an ATTiny85 unit solar sensor unit.
   More construction details are here:
   https://github.com/curiouselectric/SolarSensor
   and
   *** link to web page for design documentation ***

   This unit serives serial port requests at 9600 baud.
   It measures irradiance from a photodiode sensor with an amplifier and then by an I2C ADC (ADS1115)
   It measure temperature via an I2C temperature sensor (LM75B)
   There is a push switch and LED for human interfacing.
   Floats have been removed as they take up >1k memory...

   It can be set to either:
   Respond to serial data requests or constantly (at 1s, 10s and 1min times) output data.
   Typically responding to serial data requests is best!
   Data supplied is the average irradiance level and the average temperature of the sensor.
   At other times it sleeps, to ensure low power consumption.

   Serial data requests:

   Change ID
   "aAACHIDBB#"
   Will change the ID from AA to BB.
   Will return "aBBOK#" if OK or "aAAFAIL#" if not changed
   "a**CHID&&#"
   Will just return the units ID

   Request data "aAARQ#"
   will return: "aAAI****T***#" or "aAAFAIL#"
   Where AA is the device ID


   ATTiny85 Upload Data

   Fuses required:
   Extended:  0xFF
   High:      0xD6
   Low:       0x62

   TO DO:
   Sort out return data on serial command
   Sort out Stored ID and changing ID


*/
#define F_CPU 8000000  // This is used by delay.h library

#include <stdlib.h>
#include <EEPROM.h>
#include <Arduino.h>
#include <avr/sleep.h>

// Routines to set and clear bits (used in the sleep code)
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#include <SoftwareSerial.h>
#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI
#include <Adafruit_ADS1X15.h>
#include <Temperature_LM75_Derived.h>

// ****** ATTiny85 Pin Definitions: ************** //
#define pinI2C_SDA    PB0  // convert to arduino digital pins
#define pinSW1        PB1
#define pinI2C_CLK    PB2
#define pinRx         PB3  // wake on interrupt here...  
#define pinTx         PB4
// *********************************************** //

SoftwareSerial mySerial(pinRx, pinTx); //rx, tx

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */

// The Generic_LM75 class will provide 9-bit (±0.5°C) temperature for any
// LM75-derived sensor. More specific classes may provide better resolution.
Generic_LM75 temperature;

// ********* USER VARIABLES *************************************
uint8_t samples = 8;   // Number of 0.25S samples to use for the data averaging

// ******* PROGRAM VARIABLES *************************************

uint32_t  dataAveTemp = 0;
uint32_t  dataAve = 0;        // Holds the average sensor readings
uint16_t  dataTemperature = 0;
uint8_t   dataCounter = 0;
uint32_t  dataWm2 = 0;            // Holds the converted W/m2 data

// This holds the calibration vlaues to perform y=mx+c conversion.
// Data in Irradiance (W/m2) is converter from sensor readings using y=mx+c
// You can enter c by covering totally and requesting the dark calibration
// You can write m by applying a known irradiance and requesting the light calibration

uint16_t  dataMIrradiance;
uint16_t  dataMSensor;
int       hiByte;      // These are used to store longer variables into EERPRPROM
int       loByte;

boolean show_data_flag = false;

// *********** This is for the serial data parsing ***************
char    inChar;         // incoming serial byte
String  str_buffer = "";         // a String to hold incoming data
String  outputString = "";         // a String to hold outgoing data
char    startChar = 'a';
char    endChar = '#';
char    tempChar = 'T';
char    irrChar = 'I';


// Variables for the Sleep/power down modes:
volatile boolean f_wdt = 1;

// Useful variables
char deviceID[2]; // A buffer to hold the device ID

void setup()
{
  // Read in the values from EEPROM
  // Read the device ID
  deviceID[0] = char(EEPROM.read(0));
  deviceID[1] = char(EEPROM.read(1));

  mySerial.begin(9600);

  TinyWireM.begin();                    // initialize I2C lib

  // ADC setup
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  ads.begin();

  // Resevres some memory for the string buffer
  str_buffer.reserve(10);
  outputString.reserve(15);

  // Watch dog timer setup
  setup_watchdog(4);      // approximately 0.064 seconds sleep between reads for averaging
  // 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
  // 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
}

void loop()
{

  // wait for timed out watchdog / flag is set when a watchdog timeout occurs
  if (f_wdt == 1)
  {
    f_wdt = 0;     // reset flag
    dataCounter++;

    // Read ADC
    /* Be sure to update this value based on the IC and the gain settings! */
    int32_t dataValue = ads.readADC_Differential_2_3();
    dataAveTemp += ( dataValue * 125) / 1000;    // Keep  /* 0.125 we need - here multiply but 125, later divide by 1000 ADS1115  @ +/- 6.144V gain (16-bit results) */

    if (dataCounter >= samples)
    {
      dataTemperature = temperature.readTemperatureC();
      dataAve = dataAveTemp / samples;
      dataCounter = 0; //reset the counter
      dataAveTemp = 0; // reset the temp store

      if (show_data_flag == true)
      {
        // Display the data if we want...
        // want to show the converted data...
        str_buffer = "";
        str_buffer = startChar;
        str_buffer += deviceID[0];
        str_buffer += deviceID[1];
        str_buffer += 'R';
        str_buffer += 'Q';
        str_buffer += endChar;
        str_buffer += '\n';
        checkCommand();
        mySerial.println(outputString);
      }
    }
    system_sleep();  // Send the unit to sleep
  }

  if (mySerial.available())
  {
    if (getData())
    {
      // If the data is in an OK format (with a at start and # at end:
      checkCommand();
      mySerial.println(outputString);
    }
    else
    {
      // Do NOT respond
    }
    mySerial.flush();
    system_sleep();  // Send the unit to sleep
  }
}

void system_sleep()
{
  cbi(ADCSRA, ADEN);                   // switch Analog to Digitalconverter OFF
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sleep_mode();                        // System actually sleeps here
  // ...zzzZZZzzz...
  sleep_disable();                     // System continues execution here when watchdog timed out
  sbi(ADCSRA, ADEN);                   // switch Analog to Digitalconverter ON
  // Want to disable interrupts here:
  GIMSK &= ~(_BV(INT0));  //disable INT0
}

//****************************************************************
// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii)
{
  byte bb;
  int ww;
  if (ii > 9 ) ii = 9;
  bb = ii & 7;
  if (ii > 7) bb |= (1 << 5);
  bb |= (1 << WDCE);
  ww = bb;
  MCUSR &= ~(1 << WDRF);
  // start timed sequence
  WDTCR |= (1 << WDCE) | (1 << WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}

// Watchdog Interrupt Service is executed when watchdog timed out
ISR(WDT_vect) {
  f_wdt = 1; // set global flag
}

boolean getData()
{
  // **********GET DATA*******************************************
  // We want to find the bit of interesting data in the serial data stream
  str_buffer = "";    // Reset the buffer
  delay(50);   // Wait for data to come in... MUST have this!
  while (mySerial.available())
  {
    inChar = (char)mySerial.read(); // Read whatever is happening on the serial port
    str_buffer += inChar;
    if ((inChar == endChar) || (inChar == '\r') || (inChar == '\n'))
    {
      break;
    }
    delay(10);   // Wait for data to come in... MUST have this!
  }
  if (str_buffer[0] == startChar && (str_buffer[str_buffer.length() - 1] == endChar))
  {
    return (true);
  }
  else
  {
    return (false);
  }
}

void checkCommand()
{
  outputString = "";  // reset the output string ready to return any data

  if ((str_buffer.charAt(1) == deviceID[0] && str_buffer.charAt(2) == deviceID[1]) || (str_buffer.charAt(1) == '*' && str_buffer.charAt(2) == '*'))
  {
    // This is where we need to parse the data
    // Check the ID corresponds to the stored EEPROM ID or to the wildcard "**"

    if (str_buffer.charAt(3) == 'C' && str_buffer.charAt(4) == 'H' && str_buffer.charAt(5) == 'I' && str_buffer.charAt(6) == 'D')
    {
      // ***** Change the ID *************
      outputString = startChar;
      deviceID[0] = str_buffer[7];
      deviceID[1] = str_buffer[8];
      // Also want to store this into EEPROM
      EEPROM.write(0, deviceID[0]);    // Do this seperately
      EEPROM.write(1, deviceID[1]);
      outputString += deviceID[0];
      outputString += deviceID[1];
      outputString += endChar;
    }
    else if (str_buffer.charAt(3) == 'R' && str_buffer.charAt(4) == 'Q')
    {
      // ****** Request Data ************
      // If this is the case then we respond with the average sensor value (and temperature value!)
      outputString = startChar;
      outputString += deviceID[0];
      outputString += deviceID[1];
      outputString += irrChar;
      outputString += dataAve;
      outputString += tempChar;
      outputString += dataTemperature;    // Need to check this works and shows our temperature data
      outputString += endChar;
    }
    else if (str_buffer.charAt(3) == 'S' && str_buffer.charAt(4) == 'D')
    {
      // ****** Show data - toggle show data flag ************
      show_data_flag = !show_data_flag;
    }
  }
  else
  {
    // Dont want anything to be shown here!
    // Just dont reply - as it might not be asking this sensor.
    //    outputString = startChar;
    //    outputString += deviceID[0];
    //    outputString += deviceID[1];
    //    outputString += F("FAIL#");   // Dont want it to say anything in the end!
  }
}
