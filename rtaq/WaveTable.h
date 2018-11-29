#ifndef WAVETABLE_H_
#define WAVETABLE_H_

#include <SdFat.h>
#include <string>

// 127 X 127 array
#define ROW_DIM 127
#define COL_DIM 127

extern SdFat SD;
extern File file;

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

extern float wtable[ROW_DIM][COL_DIM];

size_t readField(File* file, char* str, size_t size, const char* delim);
//------------------------------------------------------------------------------
#define errorHalt() {SysCall::halt();}
//------------------------------------------------------------------------------
void loadTable();
float getWaveTableValue(int table, int index);
#endif
