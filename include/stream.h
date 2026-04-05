#include <stdio.h>

#ifndef STREAM_H
#define STREAM_H

FILE *open_file(const char *name, const char *mode);

long file_size(FILE *fp);

#endif