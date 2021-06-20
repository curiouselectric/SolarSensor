/**********************************************************
  /****** Solar Sensor:  **********************************
  /****** by Matt Little **********************************
  /****** Date: 06/09/2017 ********************************
  /****** info@re-innovation.co.uk ************************
  /****** www.re-innovation.co.uk *************************
  /********************************************************

  See www.re-innovation.co.uk for information and construction details

  /*************Details of Code*****************************

  The pin assisgnments are as follows:
  D0 - Rx
  D1 - Tx
  D2 - SW_UP
  D3 - SW_DOWN
  D4 - CS_ADC
  D5 - DS18B20 Data
  D6 - N/C
  D7 - N/C
  D8 -
  D9 -
  D10 -
  D11 -
  D12 -
  D13 -

  A0 - Irradiance voltage (direct)
  A1 -
  A2 -
  A3 -
  A4 - I2C SDA (For OLED and ADC)
  A5 - I2C SCLK (For OLED and ADC)
  A6 - (nano only) External analog
  A7 - (nano only) External analog



  Updates:
  06/09/17 Initial tesing of all functions


  TO DO:
  Test DS18B20
  Test ADC MCP3201
  Test Irradiance input
  Test Buttons


  //********* OLED DETAILS*****************************
  Universal 8bit Graphics Library, https://github.com/olikraus/u8glib/
  Use this one: U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); // I2C / TWI



**********************************************************************************************************/



/************ External Libraries*****************************/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ADS1X15.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Definitions

// ********** OLED Information *********************//
#define SCREEN_WIDTH          128         // OLED display width, in pixels
#define SCREEN_HEIGHT         64          // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET            -1          // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_VOLTAGE_CONTROL  SSD1306_SWITCHCAPVCC
#define OLED_I2C_ADDRESS      0x3C        // Address 0x3D for 128x64

#define SW_UP 2
#define SW_DOWN 3

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 5

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String dataString;        // This holds any data for OLED to display
uint32_t timer;     // This is a timer to update the display

/************User variables and hardware allocation**********************************************/
void setup() {

  // Setup Serial connection
  Serial.begin(115200);

  // OLED Setup
  if (!display.begin(OLED_VOLTAGE_CONTROL, OLED_I2C_ADDRESS))
  {
    // This doesnt actually matter!
    // DOnt need to loop forever
    Serial.println("SSD1306 allocation failed. QUIT ALL");
    //for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(2, 10);           // Start at top-left corner
  display.println("Solar Sensor v2");
  display.display();

  // Button Setup
  // make the pushbutton's pin an input:
  pinMode(SW_UP, INPUT_PULLUP);
  pinMode(SW_DOWN, INPUT_PULLUP);

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

  // Start up the library
  sensors.begin();

  delay(1000);  // Wait to display start up message

}

void loop() {

  // Test Buttons
  if (digitalRead(SW_UP) == false)
  {
    dataString = "UP";
  }
  else if (digitalRead(SW_DOWN) == false)
  {
    dataString = "DOWN";
  }

  // Test ADC
  /* Be sure to update this value based on the IC and the gain settings! */
  float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  int32_t dataValue = ads.readADC_Differential_2_3();
  float dataFloat = (float)dataValue * (float)multiplier;

  Serial.print("Differential: ");
  Serial.print(dataValue);
  Serial.print("(");
  Serial.print(dataFloat);
  Serial.println("mV)");


  // Test DS18B20
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }


  // Update OLED
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(2, 20);           // Start at top-left corner
  display.println(dataFloat, 0);
  display.setCursor(2, 30);           // Start at top-left corner
  display.println(tempC, 2);
  
  display.display();

  delay(500); // Slow it all down
}
