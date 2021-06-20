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
#include "U8glib.h"

// ********** OLED ******************************************/
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); // I2C / TWI


#define SW_UP 2
#define SW_DOWN 3

String data;

/************User variables and hardware allocation**********************************************/
void setup() {

  // Setup Serial connection
  Serial.begin(115200);
  
  // make the pushbutton's pin an input:
  pinMode(SW_UP, INPUT_PULLUP);
  pinMode(SW_DOWN, INPUT_PULLUP);
  //OLED set-up info
  // assign default color value
  u8g.begin();
  
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  
  // Test OLED
  data = "Solar Sensor v1";
  
  // Update Display
  u8g.firstPage();  
  do {
      //OLED test
      u8g.setFont(u8g_font_unifont);  
      u8g.drawStr( 10, 10, data.c_str());  
  } while( u8g.nextPage() );  
  delay(1000);  // Wait and display message
    
}

void loop() {

  // Test Buttons
  if(digitalRead(SW_UP)==false)
  {
    data = "UP";
  }
  else if(digitalRead(SW_DOWN)==false)
  {
    data = "DOWN";
  } 

  // Test ADC



  // Test DS18B20

  

  // Update Display
  u8g.firstPage();  
  do {
      //OLED test
      u8g.setFont(u8g_font_unifont);  
      u8g.drawStr( 10, 10, data.c_str());  
  } while( u8g.nextPage() );

  delay(100); // Slow it all down
}


