#include "WaveTable.h"
#include <SdFat.h>
#include <string>

// 127 X 127 array
#define ROW_DIM 127
#define COL_DIM 127

SdFat SD;
File file;
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


size_t readField(File* file, char* str, size_t size, const char* delim) {
  char ch;
  size_t n = 0;
  while ((n + 1) < size && file->read(&ch, 1) == 1) {
    // Delete CR.
    if (ch == '\r') {
      continue;
    }
    str[n++] = ch;
    if (strchr(delim, ch)) {
        break;
    }
  }
  str[n] = '\0';
  return n;
}
//------------------------------------------------------------------------------
#define errorHalt() {SysCall::halt();}
//------------------------------------------------------------------------------
void loadTable() {
  // Initialize the SD.
  if (!SD.begin()) {
    Serial.println("1");
    errorHalt();
  } 
  // Create or open the file.
  file = SD.open("transferfunction.csv", FILE_READ);
  if (!file) {
    Serial.println("2");
    errorHalt();
  }

  // Rewind the file for read.
  file.rewind();

  int i = 0;     // First array index.
  int j = 0;     // Second array index
  size_t n;      // Length of returned field with delimiter.
  char str[20];  // Must hold longest field with delimiter and zero byte.
  char *ptr;     // Test for valid field.

  // Read the file and store the data.
  
  for (i = 0; i < ROW_DIM; i++) {
    for (j = 0; j < COL_DIM; j++) {
      n = readField(&file, str, sizeof(str), ",\n");
      if (n == 0) {
        Serial.println("3");
        errorHalt();
      }
      wtable[i][j] = strtod(str, &ptr);
      if (ptr == str) {
        Serial.println("4");
        errorHalt();
      }
      while (*ptr == ' ') {
        ptr++;
      }
      if (*ptr != ',' && *ptr != '\n' && *ptr != '\0') {
        errorHalt();
      }
      if (j < (COL_DIM-1) && str[n-1] != ',') {
        Serial.println("5");
        errorHalt();
      }
    }
    // Allow missing endl at eof.
    if (str[n-1] != '\n' && file.available()) {
      Serial.println("6");
      errorHalt();
    }    
  }

  file.close();
}

float getWaveTableValue(int table, int index) {
  //loadTable();
  return wtable[table][index];
}
