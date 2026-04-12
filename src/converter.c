#include "converter.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int divide(char *num, long *num_len, int num_base, int divider);
static long get_result_len(long num_len, int from_base, int to_base);

/* Description is in the "converter.h" */
char *convert(char *num, long num_len, int from_base, int to_base)
{
    int rest;
    long res_len, res_offset;
    char *res;

    if (from_base == to_base) {
        num[num_len] = '\0';
        return num;
    }

    res_len = get_result_len(num_len, from_base, to_base);
    res = malloc(sizeof(char) * (res_len + 1));

    if (!res) {
        return NULL;
    }

    res_offset = res_len - 1;

    while (*num != '0') {
        rest = divide(num, &num_len, from_base, to_base);

        res[res_offset] = get_digit_char(rest);
        res_offset--;
    }
    while (res_offset >= 0) {
        res[res_offset] = '0';
        res_offset--;
    }
    res[res_len] = '\0';

    return res;
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

/* Params:
 * num_len - count of digits of some number;
 * from_base - in decimal notation;
 * to_base - in decimal notation.
 *
 * Returns approximate count of digits of number after possible convertation
 * from from_base to to_base.
 */
static long get_result_len(long num_len, int from_base, int to_base)
{
    int pow, rest;

    if (from_base < to_base) {
        for (pow = 1; from_base < to_base; pow++) {
            rest = from_base % to_base;
            to_base /= from_base;
        };
        return num_len / (pow - (rest > 0 ? 1 : 0));
    }
    if (from_base > to_base) {
        for (pow = 1; from_base > to_base; pow++) {
            rest = from_base % to_base;
            from_base /= to_base;
        };
        return num_len * (pow + (rest > 0 ? 1 : 0));
    }
    return num_len;
}