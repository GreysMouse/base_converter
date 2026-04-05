#include "../include/converter.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static const char DIGITS[] =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static int is_digit(char c, size_t base);
static long parse(char *src, long src_len, int *src_base, int *dest_base);

long convert(char *src, long src_len)
{
    int src_base, dest_base, num_len;

    num_len = parse(src, src_len, &src_base, &dest_base);

    if (num_len < 0) {
        return num_len;
    }
    return num_len;
}

static int is_digit(char c, size_t base)
{
    return c >= DIGITS[0] && c <= DIGITS[base - 1];
}

static long parse(char *src, long src_len, int *src_base, int *dest_base)
{
    int p = 1, err = 0;
    int stage = 2; /* 0 - num, 1 - src base, 2 - dest base */
    long i, len = 0;

    *src_base = -1;
    *dest_base = -1;

    for (i = src_len - 1; i >= 0; i--) {
        if (src[i] == ' ') {
            if (stage == 2) {
                if (*dest_base == -1) {
                    err = 1;
                    break;
                }
                if (*dest_base < 2 || *dest_base > sizeof(DIGITS)) {
                    err = 2;
                    break;
                }
            }
            if (stage == 1) {
                if (*src_base == -1) {
                    err = 1;
                    break;
                }
                if (*src_base < 2 || *src_base > sizeof(DIGITS)) {
                    err = 3;
                    break;
                }
            }
            if (stage == 0) {
                err = 1;
                break;
            }
            if (err) {
                break;
            }
            stage--;
            p = 1;
            len = i;

            continue;
        }
        if (stage == 0) {
            if (!is_digit(src[i], *src_base)) {
                err = 2;
            }
            continue;
        }
        if (stage == 1) {
            if (!is_digit(src[i], 10)) {
                err = 3;
            }
            *src_base += (src[i] - '0') * p;
            p *= 10;
            continue;
        }
        if (stage == 2) {
            if (!is_digit(src[i], 10)) {
                err = 4;
            }
            *dest_base += (src[i] - '0') * p;
            p *= 10;
        }
    }

    if (!src_len || err == 1) {
        fprintf(stderr,
                "Invalid source foramat: \"<num> <from-base> <to-base>\"\n");
    } else if (err == 2) {
        fprintf(stderr, "The target base should be between 2 and %ld\n",
                sizeof(DIGITS));
    } else if (err == 3) {
        fprintf(stderr, "The source base should be between 2 and %ld\n",
                sizeof(DIGITS));
    } else if (err == 2) {
        fprintf(stderr, "The number provided is not in a base %d\n", *src_base);
    } else if (err == 3) {
        fprintf(stderr, "The source base should be decimal\n");
    } else if (err == 4) {
        fprintf(stderr, "The target base should be decimal\n");
    }
    return -err || len;
}