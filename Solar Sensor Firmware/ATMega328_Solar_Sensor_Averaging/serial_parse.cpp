#include "serial_parse.h"
#include "solar_data.h"
#include <EEPROM.h>       // for saving mode to EEPROM

String check_data::parseData(String _inputString, byte _UNIT_ID, data_channel _local_solar_data)
{
  // Here we parse the data we get on the serial port
  // Check the main page for all the serial port requests

  String _outputString = "";    // Set output string for the output

  if (_inputString.charAt(0) == 'a' && _inputString.charAt(1) == 'a'
      && _inputString.charAt(_inputString.length() - 2) == '#')
  {
    // If we get here then the start/end chars are correct:
    if (_inputString.length() > 60)
    {
      _outputString = FAIL_STR;   // String is too long
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
          if (_inputString.charAt(4) == 'B' && _inputString.charAt(5) == 'D')
          {
            // if we ask for "aaI0BD#" then it will return the baud rate
            baud_return_flag = true;
          }
          else if (_inputString.charAt(4) == 'S' && _inputString.charAt(5) == 'T' && _inputString.charAt(6) == 'B' && _inputString.charAt(7) == 'D')
          {
            // if we ask for "aaI0STBD?#" then it will return the baud rate, with ? being a number to set baud rate from array
            int baud_id = (_inputString.substring(8, 9)).toInt();
            EEPROM.write(4, baud_id);
            baud_set_flag = true;
          }
          else if (_inputString.charAt(4) == 'S' && _inputString.charAt(5) == 'E' && _inputString.charAt(6) == 'N' && _inputString.charAt(7) == 'D')
          {
            // if we ask for "aaI0SEND?#" then it will start sending regular serial data
            int send_id = (_inputString.substring(8, 9)).toInt();
            if (send_id >= 0 && send_id < 6)
            {
              EEPROM.write(120, send_id);
              send_data_flag = true;
            }
          }
          else if (_inputString.charAt(4) == 'S' && _inputString.charAt(5) == 'S' && _inputString.charAt(6) == 'C' && _inputString.charAt(7) == 'O' && _inputString.charAt(8) == 'N')
          {
            // If we ask for "aaI0SSCON#" then it will return the conversion data
            conversion_return_flag = true;
          }
          else if (_inputString.charAt(4) == 'S' && _inputString.charAt(5) == 'S' && _inputString.charAt(6) == 'S' && _inputString.charAt(7) == 'E' && _inputString.charAt(8) == 'T')
          {
            // If we ask for "aaI0SSSTm123.4c567.89#" then it will set the conversion values for m and c
            // So need to find the data between m & c and between c and #
            // Then convert the data from string to a float
            String data_substring;
            int start_index;
            int end_index;

            start_index = _inputString.indexOf('m');
            end_index = _inputString.indexOf('c', start_index + 1);
            data_substring = _inputString.substring(start_index + 1, end_index);
            solar_conv_m = data_substring.toFloat();
            start_index = end_index;
            end_index = _inputString.indexOf('#', start_index + 1);
            data_substring = _inputString.substring(start_index + 1, end_index);
            solar_conv_c = data_substring.toFloat();
            conversion_set_flag = true;
          }
          else if (_inputString.charAt(4) == 'S' && _inputString.charAt(5) == 'S' && _inputString.charAt(6) == 'M' && _inputString.charAt(7) == 'N')
          {
            // We get here is asking for minimum data "MN"
            // We dont need the average number
            data_min_flag = true;
            data_sent_flag = true; // This flag allows the main loop to then check out the correct data value and return it.
          }
          else if (_inputString.charAt(4) == 'S' && _inputString.charAt(5) == 'S' && _inputString.charAt(6) == 'M' && _inputString.charAt(7) == 'X')
          {
            // We get here is asking for maximum data "MX"
            // We dont need the average number
            data_max_flag = true;
            data_sent_flag = true; // This flag allows the main loop to then check out the correct data value and return it.
          }
          else if (_inputString.charAt(4) == 'S' && _inputString.charAt(5) == 'S')
          {
            // We get here is asking for ALL channel data "AA"
            if (_inputString.charAt(6) == 'A' && isDigit(_inputString.charAt(7)))
            {
              // need to check if AVE is OK and a number
              ave_time = (_inputString.substring(7, 8)).toInt();
              // This means we have all the parts required and can return true - the data will be correct.
              data_sent_flag = true; // This flag allows the main loop to then check out the correct data value and return it.
              data_all_flag = true; // This means we return ALL the data
            }
            else
            {
              error_flag = true;
              data_sent_flag = false;
              _outputString = FAIL_STR;
            }
          }
          else if (_inputString.charAt(4) == 'R' && _inputString.charAt(5) == 'E' && _inputString.charAt(6) == 'S' && _inputString.charAt(7) == 'E' && _inputString.charAt(8) == 'T')
          {
            // We get here is asking for Min and Max data to be reset
            // *********** RESET ALL MAXIMUMS **********************
            _local_solar_data.data_max = -99999;

            // *********** RESET ALL MINIMUMS **********************
            _local_solar_data.data_min = 99999;

            data_sent_flag = false;
            data_min_flag = false;
            data_max_flag  = false;
            data_reset_flag = true; // Do not need this flag - not returning anything
          }
          else
          {
            error_flag = true;
            data_sent_flag = false;
            _outputString = FAIL_STR;
          }
        }
        else
        {
          error_flag = true;
          data_sent_flag = false;
          _outputString = FAIL_STR;
        }
      }
      else if (_inputString.charAt(2) == 'I' && _inputString.charAt(3) == '?')
      {
        // This is the case when we dont know what the ID is and we are requesting it:
        data_sent_flag = true; // This flag allows the main loop to then check out the correct data value and return it.
        id_return_flag = true;
      }
      else
      {
        error_flag = true;
        data_sent_flag = false;
        _outputString = FAIL_STR;
      }
    }
  }
  else
  {
    error_flag = true;
    _outputString = FAIL_STR;
  }
  return (_outputString);
}
