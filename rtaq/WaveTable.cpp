#include "WaveTable.h"
//#include <SdFat.h>
#include <string>

// 127 X 127 array
#define ROW_DIM 127
#define COL_DIM 127

//SdFat SD;
//File file;
float wtable[ROW_DIM][COL_DIM];
/*
 * Read a file one field at a time.
 *
 * file - File to read.
 *
 * str - Character array for the field.
 *
 * size - Size of str array.
 *
 * delim - String containing field delimiters.
 *
 * return - length of field including terminating delimiter.
 *
 * Note, the last character of str will not be a delimiter if
 * a read error occurs, the field is too long, or the file
 * does not end with a delimiter.  Consider this an error
 * if not at end-of-file.
 *
 */


float getWaveTableValue(int table, int index) {
  //loadTable();
  return wtable[table][index];
}
