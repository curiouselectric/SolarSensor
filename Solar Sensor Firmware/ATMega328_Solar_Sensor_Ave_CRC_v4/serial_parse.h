#pragma once

#include <stdio.h>
#include <Arduino.h>
#include "config.h"
#include "solar_data.h"

// This class takes in an input string, parses it and returns the ID and AVE values if they are OK
// If not it returns an error message

class check_data {
  public:
    int  id;
    int  ave_time;
    bool error_flag;
    bool data_sent_flag;
    bool data_all_flag;
    bool data_min_flag;
    bool data_max_flag;
    bool data_reset_flag;
    bool baud_return_flag;
    bool baud_set_flag;
    bool conversion_return_flag;
    bool conversion_set_flag;
    bool send_data_flag;
    bool id_return_flag;
    bool button_press_flag;
    bool temp_con_status_flag;
    bool temp_con_return_flag;
    bool temp_con_set_flag;
        
    float solar_conv_m;
    float solar_conv_c;   

    // Temperature conversion values
    float solar_tempcon_percentage; 
    float solar_tempcon_rated_c;
    bool  solar_tempcon_flag;
   
    // Member functions
    String  parseData(String dataString, byte unit_ID, data_channel local_wind_speed_data);

    // This is the constructor
    check_data() {
      id = 0; ave_time = 0;
      error_flag = false; data_sent_flag = false;
      data_all_flag = false; data_min_flag = false; data_max_flag = false; data_reset_flag = false;
      baud_return_flag = false; baud_set_flag = false;
      conversion_return_flag = false; conversion_set_flag = false; id_return_flag = false;
      button_press_flag = false;
      temp_con_status_flag = false; temp_con_return_flag = false; temp_con_set_flag = false;

      
    }
};
