#include "serial_parse.h"
#include "average_data.h"
#include <EEPROM.h>       // for saving mode to EEPROM

String check_data::parseData(String _inputString, byte _UNIT_ID, data_channel _local_channels[])
{
  // Here we parse the data we get on the serial port
  // Single channel data String is:     “aaI0R01A4#”
  // All channel data String is:        “aaI0RAAA3#”
  // All channel minimum data String is:“aaI0RMNA4#”  - does not matter what averaging period. min/max are just the min/max seen at max data rate.
  // All channel maximum data String is:“aaI0RMXA0#”  - does not matter what averaging period. min/max are just the min/max seen at max data rate.
  String _outputString = "";    // Set output string for the output

  if (_inputString.charAt(0) == 'a' && _inputString.charAt(1) == 'a'
      && _inputString.charAt(_inputString.length() - 2) == '#')
  {
    // If we get here then the start/end chars are correct:
    if (_inputString.length() > 60)
    {
      _outputString = "aaFAIL1#";   // String is too long
    }
    else
    {
      // This is where we need to parse the data
      // Example input:
      // “aaI1R01A4#”
      if (_inputString.charAt(2) == 'I' && isDigit(_inputString.charAt(3)))
      {
        // This is where we check the ID with the Unit ID
        int _unit_id = (_inputString.substring(3, 4)).toInt();
        // This checks with the global variable from set-up
        if (_unit_id == (int)_UNIT_ID)
        {
          // The unit ID is OK so carry on checking, otherwise dont bother checking any further
          if (_inputString.charAt(4) == 'R' && isDigit(_inputString.charAt(5)) && isDigit(_inputString.charAt(6)))
          {
            // This is for ONE channel ONLY:
            // need to check if channel is a number & OK
            // if not then break out and return with fail.
            id = (_inputString.substring(5, 7)).toInt();
            // Got here so channel is OK
            if (_inputString.charAt(7) == 'A' && isDigit(_inputString.charAt(8)))
            {
              // need to check if AVE is OK and a number
              ave_time = (_inputString.substring(8, 9)).toInt();
              // This means we have all the parts required and can return true - the data will be correct.
              data_sent_flag = true; // This flag allows the main loop to then check out the correct data value and return it.
            }
            else
            {
              error_flag = true;
              data_sent_flag = false;
              _outputString = "aaFAIL4#";
            }
          }
          else if (_inputString.charAt(4) == 'B' && _inputString.charAt(5) == 'D')
          {
              // if we ask for "aaI0BD#" then it will return the baud rate
              baud_return_flag = true;
          }
          else if (_inputString.charAt(4) == 'S' && _inputString.charAt(5) == 'T'&&_inputString.charAt(6) == 'B' && _inputString.charAt(7) == 'D')
          {
              // if we ask for "aaI0STBD?#" then it will return the baud rate, with ? being a number to set baud rate from array
              int baud_id = (_inputString.substring(8, 9)).toInt();
              EEPROM.write(10, baud_id);
              baud_set_flag = true;
          }
          else if (_inputString.charAt(4) == 'R' && _inputString.charAt(5) == 'A' && _inputString.charAt(6) == 'A')
          {
            // We get here is asking for ALL channel data "AA"
            if (_inputString.charAt(7) == 'A' && isDigit(_inputString.charAt(8)))
            {
              // need to check if AVE is OK and a number
              ave_time = (_inputString.substring(8, 9)).toInt();
              // This means we have all the parts required and can return true - the data will be correct.
              data_sent_flag = true; // This flag allows the main loop to then check out the correct data value and return it.
              data_all_flag = true; // This means we return ALL the data
            }
            else
            {
              error_flag = true;
              data_sent_flag = false;
              _outputString = "aaFAIL4#";
            }
          }
          else if (_inputString.charAt(4) == 'R' && _inputString.charAt(5) == 'M' && _inputString.charAt(6) == 'N')
          {
            // We get here is asking for ALL minimum channel data "MN"
            // We dont need the average number
            data_min_flag = true;
            data_sent_flag = true; // This flag allows the main loop to then check out the correct data value and return it.
          }
          else if (_inputString.charAt(4) == 'R' && _inputString.charAt(5) == 'M' && _inputString.charAt(6) == 'X')
          {
            // We get here is asking for ALL maximum channel data "MX"
            // We dont need the average number
            data_max_flag = true;
            data_sent_flag = true; // This flag allows the main loop to then check out the correct data value and return it.
          }
          else if (_inputString.charAt(4) == 'R' && _inputString.charAt(5) == 'E' && _inputString.charAt(6) == 'S' && _inputString.charAt(7) == 'E' && _inputString.charAt(8) == 'T')
          {
            // We get here is asking for Min and Max data to be reset
            // *********** RESET ALL MAXIMUMS **********************
            for (int j = 0; j < NUM_CHANNELS; j++)
            {
              _local_channels[j].data_max = -99999;
            }
            // *********** RESET ALL MINIMUMS **********************
            for (int j = 0; j < NUM_CHANNELS; j++)
            {
              _local_channels[j].data_min = 99999;
            }

            data_sent_flag = false;
            data_min_flag = false;
            data_max_flag  = false;
            data_reset_flag = true; // Do not need this flag - not returning anything
          }
          else
          {
            error_flag = true;
            data_sent_flag = false;
            _outputString = "aaFAIL3#";
          }
        }
        else
        {
          error_flag = true;
          data_sent_flag = false;
          _outputString = "aaFAIL2#";
        }
      }
      else
      {
        error_flag = true;
        data_sent_flag = false;
        _outputString = "aaFAIL2#";
      }
    }
  }
  else
  {
    error_flag = true;
    _outputString = "aaFAIL5#";
  }
  return (_outputString);
}
