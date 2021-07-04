/*
   Solar Sensor firmware for ATTin85
   by:    Matt Little
   date:  20/6/2021
   w:     www.curiouselectric.co.uk
   e:     hello@curiouselectric.co.uk

   This ciode is for an ATTiny85 unit solar sensor unit.
   More concstruction details are here:
   https://github.com/curiouselectric/SolarSensor
   and


   This unit serives serial port requests at 9600 baud.
   It measures irradiance from an I2C ADC (ADS1115)
   It measure temperature via an I2C temperature sensor (LM75B)
   There is a push switch and LED for human interfacing.

   It can be set to either:
   Respond to serial data requests or constantly (at 1s, 10s and 1min times) output data
   Data supplied is the average irradiance level and the average temperature of the sensor.

   At other times it sleeps, to ensure low power consumption

   Fuses required:
   Extended:  0xFF
   High:      0xD6
   Low:       0x62


   TO DO:

*/
#define F_CPU 8000000  // This is used by delay.h library
#include <stdlib.h>
#include <EEPROM.h>
#include <Arduino.h>
#include <avr/io.h>        // Adds useful constants
#include <util/delay.h>    // Adds delay_ms and delay_us functions
#include <avr/sleep.h>
#include <avr/interrupt.h>

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

#define pinI2C_SDA    PB0  // convert to arduino digital pins
#define pinSW1        PB1
#define pinI2C_CLK    PB2
#define pinRx         PB3  // wake on interrupt here...  
#define pinTx         PB4

SoftwareSerial mySerial(pinRx, pinTx); //rx, tx

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */

// Variables for the Sleep/power down modes:
volatile boolean f_wdt = 1;
volatile boolean triggered = false;

char inChar;         // incoming serial byte
String inputString = "";         // a String to hold incoming data

void setup() {

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
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  ads.begin();

  // Watch dog timer setup
  setup_watchdog(8); // approximately 4 seconds sleep

  //  // Interrupt setup onto pin D3 (Rx from serial port)
  //  pin_change_interrupt();

  // reserve 50 bytes for the inputString:
  inputString.reserve(50);
}

void loop()
{

  // wait for timed out watchdog / flag is set when a watchdog timeout occurs
  if (f_wdt == 1)
  {
    f_wdt = 0;     // reset flag
    mySerial.print("Data: ");
    // Test ADC
    /* Be sure to update this value based on the IC and the gain settings! */
    float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */
    int32_t dataValue = ads.readADC_Differential_2_3();
    float dataFloat = (float)dataValue * (float)multiplier;
    mySerial.println(dataFloat, 0);
    // Service any Serial requests/data
    mySerial.println("..zzZZ"); //going to sleep
    system_sleep();  // Send the unit to sleep
  }

  if (mySerial.available())
  {
    if (triggered == false)
    {
      triggered = true;
    }
    delay(100);
    // Here we can read anything on the serial line (stay awake for a bit?)
    while (mySerial.available() > 0)
    {
      //get incoming byte:
      inChar = mySerial.read();
      inputString += inChar;
//      if (inChar == '\n') {
//        break;
//      }
    }
  }
  if (triggered == true)
  {

    mySerial.println(inputString);

    inputString = ""; // Reset the input string
    triggered = false;
    mySerial.println("..zzZZ"); //going to sleep
    system_sleep();  // Send the unit to sleep
  }
}

//void pin_change_interrupt()
//{
//  GIMSK |= (1 << PCIE);
//  PCMSK |= (1 << PCINT3);
//}

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
