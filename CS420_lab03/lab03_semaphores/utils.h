#ifndef _utils_h
#define _utils_h

#include <stdio.h>
#include <stdlib.h>

FILE* open_file(char* filename, char* rw);
void close_file(FILE* fp);

#endif

