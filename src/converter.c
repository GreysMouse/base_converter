#include "../include/converter.h"
#include "../include/parser.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int divide(char *num, long *num_len, int num_base, int divider);

long convert(char *src, long src_len, char *dest, long dest_len)
{
    int src_base, dest_base, rest;
    long num_len, dest_offset;

    num_len = parse(src, src_len, &src_base, &dest_base);

    if (num_len < 0) {
        return -1;
    }

    /* TODO: if src_base == dest_base just copy src to dest */

    /* After parsing, it is guaranteed that only numeric characters will be
     * processed. */

    while (*src != '0') {
        rest = divide(src, &num_len, src_base, dest_base);

        dest[dest_offset - 1] = get_digit_char(rest);
        dest_offset--;
    }
    return dest_len - dest_offset;
}

/* Params:
 * num - numeric chars representing source number;
 * num_len - count of numeric chars of num;
 * num_base - in decimal notation;
 * divider - in decimal notation.
 *
 * Places result of division represented as numeric chars into num rewriting it.
 * Rewrites num_len with count of numeric chars of result.
 * Returns modulo as if num was numeric variable.
 */
static int divide(char *num, long *num_len, int num_base, int divider)
{
    int subnum = 0;
    long subnum_len = 0;

    for (long i = 0; i < *num_len; i++) {
        subnum = subnum * num_base + get_digit(num[i]);

        if (subnum < divider && i < *num_len - 1 && !subnum_len) {
            continue;
        }
        num[subnum_len] = get_digit_char(subnum / divider);

        subnum %= divider;
        subnum_len++;
    }
    *num_len = subnum_len;

    return subnum;
}