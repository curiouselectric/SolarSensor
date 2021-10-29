#pragma once

#include <stdio.h>
#include <Arduino.h>
#include "config.h"

class wind_vane_array {
  public:

    String    vane_directions[8] = {"N","NE","E","SE","S","SW","W","NW"};   // Holds the array of different directions
    
    uint16_t  vane_bands[8];                // These are readings for each of the directions (N,NE,E,SE,S,SW,W,NW)
                                            // This will need to be changed for different vane types
    int16_t   data_1s;                      // This holds a 1 second average of the vane direction
    int32_t   data_1s_holder;
    
    uint16_t  vane_lower_bands[8];          // Holds the lower bands (calculated in set-up)
    uint16_t  vane_upper_bands[8];          // Holds the upper bands (calculated in set-up)
    uint32_t  direction_array[8];           // This holds the number of seconds vane has been in each the different directions [N, NE, E, SE, S, SW ,W, NW]
    float     direction_array_values[8];    // This holds the number of seconds vane has been in each the different directions [N, NE, E, SE, S, SW ,W, NW]
    uint8_t   vane_rollover_index;          // This holds the index of the band which rolls over from 1024 to 0

    // Functions:
    void find_lower_bands(bool my_debug);
    void find_upper_bands(bool my_debug);
    void find_rollover_index(bool my_debug);
    void build_direction_array(uint16_t vane_value);
    void read_direction_array();    // Gets the direction data stored in EEPROM
    void write_direction_array(int my_direction, uint16_t my_value);
    void reset_vane_direction_array();
    String return_direction(uint16_t my_value);  // This returns the direction, depending upon the value given...
    
};
