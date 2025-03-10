
#include "crc_check.h"

// ****** This is for the CRC calculation ***********************************************
//  AUTHOR: Rob Tillaart
// https://github.com/RobTillaart/CRC
#include "CRC.h"

/*
   ADD CRC
   Add the CRC checksum to a serial string
   We send to this a string of data
   The ? and CRC and # are added to the end
   We include the aa at the beginning

*/
String add_CRC(String &_check_string)
{
  uint8_t crc_info = return_CRC(_check_string);
  char crc_str[3];
  itoa (crc_info, crc_str, HEX);
  _check_string += "?";
  if (strlen(crc_str) <= 1)
  {
    _check_string += "0";
    _check_string += crc_str[0];
  }
  else
  {
    _check_string += crc_str[0];
    _check_string += crc_str[1];
  }
  _check_string += "#";
  return (_check_string);
}

/*
   RETURN CRC
   This returns just the CRC from the check string
*/
uint8_t return_CRC(String &_check_string)
{
  uint8_t * data = (uint8_t *) &_check_string[0];
  uint8_t buf_length = _check_string.length();
  uint8_t crc_info = crc8(data, buf_length, 0x07);
  return (crc_info);
}

/*
   CHECK CRC
   This takes a series string (including the ? CRC #)
   It calculates the CRC from the data
   It compares this to the CRC sent in the string
   It returns true/1 if they are the same
   It returns false/0 if they are different
*/

bool check_CRC(String &_check_string)
{
  int question_index = _check_string.indexOf('?', 0);
  int end_index = _check_string.indexOf('#', 0);
  // Find the crc from the incomming data:
  String _crc_to_check = _check_string.substring(question_index + 1, end_index);


  
  // Find the data to perform crc check on
  String _data_substring = _check_string.substring(0, question_index);
  //calculate the CRC and create a string to compare with above.

  uint8_t crc_info = return_CRC(_data_substring);
  char crc_str[3];
  String _crc_string = "";
  itoa (crc_info, crc_str, HEX);
  if (strlen(crc_str) <= 1)
  {
    _crc_string += "0";
    _crc_string += crc_str[0];
  }
  else
  {
    _crc_string += crc_str[0];
    _crc_string += crc_str[1];
  }
  
//  // This is a test for CRC
//  Serial.print("CRC from Data:");
//  Serial.println(_crc_string);
//  Serial.print("CRC to check:");
//  Serial.println(_crc_to_check); 
//  // End test
  
  // now compare the strings for boolean outout
  if (_crc_string == _crc_to_check)
  {
    return (true);
  }
  else
  {
    return (false);
  }
}
