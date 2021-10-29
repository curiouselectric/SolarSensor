#include "wind_vane.h"
#include <EEPROM.h>       // for saving mode to EEPROM


void wind_vane_array::find_lower_bands(bool _debug)
{
  // Here we calculate the upper and lower bands for the wind vane measurments:
  if (_debug == true)
  {
    Serial.print(F("BANDS\t"));
    for (int y = 0; y < 8; y++)
    {
      Serial.print(F("\t :"));
      // Print the direction array
      Serial.print(vane_bands[y]);
    }
    Serial.println();
  }
  // Here we calculate the lower band for each vane_band element. Need to find the next closest lower value (!)
  for (int y = 0; y < 8; y++)
  {
    uint16_t value = vane_bands[y];
    uint8_t index_lower = 99;
    uint16_t value_min = 0;
    uint16_t value_max = 0;
    uint8_t index_max;
    // Want to know the one just below it
    for (int i = 0; i < 8; i++)
    {
      if (vane_bands[i] > value_max)
      {
        value_max = vane_bands[i];
        index_max = i;
      }
      if (vane_bands[i] < value && vane_bands[i] >= value_min)
      {
        index_lower = i;
        value_min = vane_bands[i];
      }
    }
    if (index_lower == 99)
    {
      // Sepcial case for lowest value
      vane_lower_bands[y] = vane_bands[index_max] + (((1024 - vane_bands[index_max]) + value) / 2);
      if (vane_lower_bands[y] > 1024)
      {
        vane_lower_bands[y] = vane_lower_bands[y] - 1024;
      }
      index_lower = index_max;
    }
    else
    {
      vane_lower_bands[y] = (value + vane_bands[index_lower]) / 2;
    }
  }
  if (_debug == true)
  {
    Serial.print(F("LOWER BANDS"));
    for (int y = 0; y < 8; y++)
    {
      Serial.print(F("\t :"));
      // Print the direction array
      Serial.print(vane_lower_bands[y]);
    }
    Serial.println();
  }
}

void wind_vane_array::find_upper_bands(bool _debug)
{
  // Here we calculate the upper band for each vane_band element. Need to find the next closest value above(!)
  for (int y = 0; y < 8; y++)
  {
    uint16_t value = vane_bands[y];
    uint8_t index_higher = 99;
    uint16_t value_min = 9999;
    uint16_t value_max = 9999;
    uint8_t index_min;
    // Want to know the one just below it
    for (int i = 0; i < 8; i++)
    {
      if (vane_bands[i] < value_min)
      {
        value_min = vane_bands[i];
        index_min = i;
      }
      if (vane_bands[i] > value && vane_bands[i] <= value_max)
      {
        index_higher = i;
        value_max = vane_bands[i];
      }
    }
    if (index_higher == 99)
    {
      // Sepcial case for lowest value
      vane_upper_bands[y] = vane_bands[index_min] + (((1024 - vane_bands[index_min]) + value) / 2);
      if (vane_upper_bands[y] > 1024)
      {
        vane_upper_bands[y] = vane_upper_bands[y] - 1024;
      }
      index_higher = index_min;
    }
    else
    {
      vane_upper_bands[y] = (value + vane_bands[index_higher]) / 2;
    }
  }
  if (_debug == true)
  {
    Serial.print(F("UPPER BANDS"));
    for (int y = 0; y < 8; y++)
    {
      Serial.print(F("\t :"));
      // Print the direction array
      Serial.print(vane_upper_bands[y]);
    }
    Serial.println();
  }
}


void wind_vane_array::find_rollover_index(bool _debug)
{
  // This finds the value closest to either 0 or 1024.
  // The index of this is the value which rolls over from 1024 to 0, so need to know it

  // Example:
  //BANDS        :50   :500  :200  :850  :400  :1000   :600  :700
  //LOWER BANDS  :13   :450  :125  :775  :300  :925  :550  :650
  //UPPER BANDS  :125  :550  :300  :925  :450  :13   :650  :775

  // Want to know the closest to 1024 or closest to 0
  // So in this case it would be 1000.

  uint16_t difference_to_limit = 9999; // Limits are 1024 or 0
  uint8_t closest_index;

  for (int y = 0; y < 8; y++)
  {
    uint16_t value = vane_bands[y];
    if ((1024 - value) < difference_to_limit)
    {
      difference_to_limit = (1024 - value);
      closest_index = y;
    }
    if ((value) < difference_to_limit)
    {
      difference_to_limit = (value);
      closest_index = y;
    }
  }
  vane_rollover_index = closest_index;
  if (_debug == true)
  {
    Serial.print(F("ROLLOVER:"));
    Serial.println(vane_rollover_index);
  }
}

void wind_vane_array::build_direction_array(uint16_t _vane_value)
{
  // This routine takes the vane data and figures out which direction it is and saves into the direction_array

  for (int y = 0; y < 8; y++)
  {
    // If its the special case then we need to change things:
    if (y == vane_rollover_index)
    {
      if ((_vane_value > vane_lower_bands[y] && _vane_value <= 1024) || (_vane_value >= 0 && _vane_value < vane_upper_bands[y]))
      {
        direction_array[y] ++;
      }
    }
    else if (_vane_value > vane_lower_bands[y] && _vane_value <= vane_upper_bands[y])
    {
      direction_array[y] ++;
    }
  }
}



void wind_vane_array::read_direction_array()
{
  // Gets the direction data stored in EEPROM these are ints, not bytes, hence need to create longer data...
  for (int y = 0; y < 8; y++)
  {
    int address = (y * 2) + 10;
    vane_bands[y] = word(EEPROM.read(address), EEPROM.read(address + 1));
  }
}

void wind_vane_array::write_direction_array(int _direction, uint16_t _value)
{
  //Writes the data to the specified direction
  byte byte1 = _value >> 8;
  byte byte2 = _value & 0xFF;
  int address = (_direction * 2) + 10;
  EEPROM.write(address, byte1);
  EEPROM.write(address + 1, byte2);
}

void wind_vane_array::reset_vane_direction_array()
{
  for (int y = 0; y < 8; y++)
  {
    direction_array_values[y] = 0;
    direction_array[y] = 0;
  }
  // Serial.println(F("Reset Vane Data"));
}

String wind_vane_array::return_direction(uint16_t _vane_value)
{
  // This takes the direction value.
  // It then returns the direction as a string...
  for (int y = 0; y < 8; y++)
  {
    // If its the special case then we need to change things:
    if (y == vane_rollover_index)
    {
      if ((_vane_value > vane_lower_bands[y] && _vane_value <= 1024) || (_vane_value >= 0 && _vane_value < vane_upper_bands[y]))
      {
        return (vane_directions[y]);
      }
    }
    else if (_vane_value > vane_lower_bands[y] && _vane_value <= vane_upper_bands[y])
    {
      return (vane_directions[y]);
    }
  }
}
