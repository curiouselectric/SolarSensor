#pragma once

#include <stdio.h>
#include <Arduino.h>
#include "config.h"
#include "anemometer_data.h"

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
    bool vane_training_mode;   // This flag sets if we are in vane training mode or not....
    bool vane_data_flag;
    bool conversion_return_flag;
    bool conversion_set_flag;
    bool send_wind_data_flag;

    float wind_speed_conv_m;
    float wind_speed_conv_c;   
    
    // Member functions
    String  parseData(String dataString, byte unit_ID, data_channel local_wind_speed_data);

    // This is the constructor
    check_data() {
      id = 0; ave_time = 0;
      error_flag = false; data_sent_flag = false;
      data_all_flag = false; data_min_flag = false; data_max_flag = false; data_reset_flag = false;
      baud_return_flag = false; baud_set_flag = false; vane_data_flag = false; vane_training_mode = false;
      conversion_return_flag = false; conversion_set_flag = false;
    }
};
