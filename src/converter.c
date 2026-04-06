#include "../include/converter.h"
#include "../include/parser.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

long convert(char *src, long src_len, char *dest)
{
    int src_base, dest_base, num_len;

    num_len = parse(src, src_len, &src_base, &dest_base);

    if (num_len < 0) {
        return num_len;
    }

    /* After parsing it is guaranteed that only digit chars would be handled */
    while (src[0]) {
        int len = 0, num = 0, digit;

        for (int i = 0; i < num_len; i++) {
            digit = get_digit(src[i]);

            num = num * src_base + digit;

            if (num < dest_base) {
                continue;
            }
            src[len] = num / dest_base; /* TODO: convert to src_base char */
            num %= dest_base;
            len++;
        }
        *dest = num; /* TODO: convert to char */
        dest++;
        num_len = len;
    }
    return num_len;
}