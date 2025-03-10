#pragma once

#include <stdio.h>
#include <Arduino.h>
#include "config.h"

// ****** This is for the CRC calculation ***********************************************
//  AUTHOR: Rob Tillaart
// https://github.com/RobTillaart/CRC
#include "CRC.h"

String add_CRC(String &my_check_string);     // This adds an 8 bit CRC check to a string passed to the subroutine
                                            // It returns the string with CRC added.

uint8_t return_CRC(String &my_check_string);  // This returns an 8 bit CRC calculated from the string sent (for checking received data)
                                      
bool check_CRC(String &my_check_string);     // This checks a string for the CRC and returns true if OK or false of failed
