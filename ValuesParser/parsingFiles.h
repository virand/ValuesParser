#pragma once

// Get field from line
const char* getField(char* line, int num);

int countRowsInFile(char * filename);

/*
Read certain column [columnNumber] from file [fileName] to outputArray
*/
double * readColumnFromFile(char * fileName, int numberOfLinesInFile, int columnNumber);