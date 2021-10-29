#pragma once

#include <stdio.h>
#include <Arduino.h>
#include "config.h"

class data_channel {
  public:
    int   id;
    int16_t data_1s;
    int16_t data_10s;
    int16_t data_60s;
    int16_t data_600s;
    int16_t data_3600s;
    int32_t data_min;     // Holds the minimum value ever recorded until reset
                          // Once read and recorded then this value is reset 
    int32_t data_max;     // Holds the maximum value ever recorded until reset
                          // Once read and recorded then this value is reset 
    int32_t data_1s_holder;
    int32_t data_10s_holder;
    int32_t data_60s_holder;
    int32_t data_600s_holder;
    int32_t data_3600s_holder;
    
    // This is the constructor
    data_channel() {
      data_1s = 0; data_10s = 0; data_60s = 0; data_600s = 0; data_3600s = 0; 
      data_min = 99999; data_max = -99999;
    }
};
