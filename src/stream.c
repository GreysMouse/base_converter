#include "../include/stream.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

FILE *open_file(const char *name, const char *mode)
{
    FILE *file = fopen(name, mode);

    if (!file) {
        return NULL;
    }
    return file;
}

long file_size(FILE *fp)
{
    int end = fseek(fp, 0L, SEEK_END);

    if (end == -1) {
        return -1;
    }

    long pos = ftell(fp);

    if (pos == -1) {
        return -1;
    }
    rewind(fp);

    return pos;
}