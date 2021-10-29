#pragma once

#include <stdio.h>
#include <Arduino.h>
#include "config.h"
#include "average_data.h"

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
    
    // Member functions
    String  parseData(String dataString, byte unit_ID, data_channel local_channels[]);

    // This is the constructor
    check_data() {
      id = 0; ave_time = 0;
      error_flag = false; data_sent_flag = false;
      data_all_flag = false; data_min_flag = false; data_max_flag = false; data_reset_flag = false;
      baud_return_flag = false; baud_set_flag = false;
    }
};
