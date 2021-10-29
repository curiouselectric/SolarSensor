#pragma once

#include <Arduino.h>
#include <Wire.h>

//// The pin that the Arduino receives 
//// serial data on. 
//#define SERIAL_RX_PIN   0

#define LED0_PIN          7 

#define SWA_PIN           8

#define LED_FLASH_TIME    5000   // time in mS between LED flashes
#define LED_ON_TIME       100   // time in mS between LED flashes

//// The baud rate for serial communications
//// Need to be able to adjust this!
//#define SERIAL_BAUD       57600

#define     MAX_BAUD_RATES    5

#define DEBUG_FLAG        false    // Use this for debugging. Not need for roll out.
#define DEBUG_DATA_1S     false   // Use this for debugging. Not need for roll out.
#define DEBUG_DATA_10S    false   // Use this for debugging. Not need for roll out.
#define DEBUG_DATA_60S    false   // Use this for debugging. Not need for roll out.
#define DEBUG_DATA_600S   false   // Use this for debugging. Not need for roll out.
#define DEBUG_DATA_3600S  false   // Use this for debugging. Not need for roll out.

#define NUM_CHANNELS  3             // 13 is the maximum before hitting memory issues!!
                                    // This holds irradiance value (0) and the temperature value (1)  
                                    // It also holds the other general ADC value (2)
                            
// These three digital pins are for the Device ID selection:
#define  GPIO_ID0      A0  //  A0 Digital 4 on Arduino
#define  GPIO_ID1      A1  //  A1 Digital 5 on Arduino
#define  GPIO_ID2      A2  //  A3 Digital 6 on Arduino

// I2C ADC is on standard I2C Pins: A4 (SDA) and A5 (SCL)
