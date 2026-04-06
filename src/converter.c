#include "../include/converter.h"
#include "../include/parser.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

long convert(char *src, long src_len)
{
    int src_base, dest_base, num_len;

    num_len = parse(src, src_len, &src_base, &dest_base);

    if (num_len < 0) {
        return num_len;
    }
    return num_len;
}