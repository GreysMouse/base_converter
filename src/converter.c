#include "../include/converter.h"
#include "../include/parser.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

long convert(char *src, long src_len, char *dest, long dest_len)
{
    int src_base, dest_base;
    long acc_len, dest_offset = dest_len;

    acc_len = parse(src, src_len, &src_base, &dest_base);

    if (acc_len < 0) {
        return -1;
    }

    /* After parsing, it is guaranteed that only numeric characters will be
     * processed. */

    while (acc_len) {
        int quot, quot_len = 0, acc = 0;

        for (int i = 0; i < acc_len; i++) {
            acc = acc * src_base + get_digit(src[i]);

            if (acc < dest_base && i < acc_len - 1) {
                continue;
            }
            quot = acc / dest_base;

            src[quot_len] = get_digit_char(quot);
            acc %= dest_base;

            if (quot > 0) {
                quot_len++;
            }
        }
        acc_len = quot_len;

        dest[dest_offset - 1] = get_digit_char(acc);
        dest_offset--;
    }
    return dest_len - dest_offset;
}