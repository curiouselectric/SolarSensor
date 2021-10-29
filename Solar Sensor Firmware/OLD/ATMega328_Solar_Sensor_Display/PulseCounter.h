#pragma once

#include <stdio.h>
#include <Arduino.h>
#include "config.h"

class pulse_counter_ {
  public:
    volatile uint32_t pulse_counter_1 = 0;
    uint32_t prev_pulse_counter_1 = 0;  
};
