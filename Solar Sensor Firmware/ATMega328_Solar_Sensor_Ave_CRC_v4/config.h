#pragma once

#include <Arduino.h>
#include <Wire.h>

#define LED0_PIN          7 
#define SWA_PIN           8
#define ANALOG_OUT_PIN    6

#define LED_FLASH_TIME    5000  // time in mS between LED flashes
#define LED_ON_TIME       50   // time in mS of the flash length

#define HC12_PWR_PIN      9     // This is a power output for the HC12 unit - set to D9 at present. Not yet implemented.
#define POWER_SETTLE_TIME 0     // Time in mS to wait after power is applied before sending serial data and time to wait after data set before switching off power.

//// The baud rate for serial communications
#define MAX_BAUD_RATES            5
#define BAUD_RATE_EEPROM_LOC      10    // EEPROM location for baud rate save
#define CONV_M_EEPROM_LOC         100      // EEPROM location for  save
#define CONV_C_EEPROM_LOC         110      // EEPROM location for  save
#define SEND_ID_EEPROM_LOC        120      // EEPROM location for  save
#define TEMP_COMP_FLAG_LOC        130
#define TEMP_COMP_RATED_C_LOC     132
#define TEMP_COMP_PERCENTAGE_LOC  140

#define APPLY_TEMP_COMP_INIT   true  // Do you want the irradiance compensated for temperature?
#define TEMP_COMP_VAL_INIT     0.18  // % change in short circuit current away from rated temperature
#define RATED_TEMP_INIT        25.0  // Datasheet value about temperature rating

#define ADD_CRC_CHECK     false    // Use this to add CRC check to incomming and outgoing messages

#define DEBUG_FLAG        false   // Use this for debugging. Not need for roll out.
#define DEBUG_DATA_1S     false   // Use this for debugging. Not need for roll out.
#define DEBUG_DATA_10S    false   // Use this for debugging. Not need for roll out.
#define DEBUG_DATA_60S    false   // Use this for debugging. Not need for roll out.
#define DEBUG_DATA_600S   false   // Use this for debugging. Not need for roll out.
#define DEBUG_DATA_3600S  false   // Use this for debugging. Not need for roll out. 
                           
#define DEBOUNCE_DELAY    5       // debounce delay time in milli-Seconds This also gives max pulses - 5mS = 200 pulses per second                                   
                            
// These three digital pins are for the Device ID selection:
#define  GPIO_ID0      A0  //  A0 Digital 4 on Arduino
#define  GPIO_ID1      A1  //  A1 Digital 5 on Arduino
#define  GPIO_ID2      A2  //  A3 Digital 6 on Arduino

// I2C ADC is on standard I2C Pins: A4 (SDA) and A5 (SCL)

#define FAIL_STR              "aaFAIL"
#define START_STR             "aaI"
#define END_STR               "#"

#define MCP_ADDRESS           0x68

#define M_CONV_INIT           10.0    // Initialisation value is EEPROM not previously set
#define C_CONV_INIT           0.0     // Initialisation value is EEPROM not previously set

#define MAX_IRRADIANCE        2000    // This is the value for the PWM output being Vcc. So 1000W/m2 is Vcc/2
