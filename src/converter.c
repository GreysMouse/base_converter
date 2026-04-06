#include "../include/converter.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static const char DIGITS[] =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static int get_digit(char c);
static long parse(const char *src, long src_len, int *src_base, int *dest_base);

long convert(char *src, long src_len)
{
    int src_base, dest_base, num_len;

    num_len = parse(src, src_len, &src_base, &dest_base);

    if (num_len < 0) {
        return num_len;
    }
    return num_len;
}

static int get_digit(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 36;
    } else {
        return -1;
    }
}

static long parse(const char *src, long src_len, int *src_base, int *dest_base)
{
    int digit, max_digit = 0;
    long i, num_len = 0, src_base_len = 0, dest_base_len = 0;

    for (i = 0; i < src_len; i++) {
        if (src[i] == ' ') {
            break;
        }
        digit = get_digit(src[i]);

        if (digit == -1) {
            fprintf(stderr, "Base of provided number exceeds 62");
            return -1;
        }
        if (digit > max_digit) {
            max_digit = digit;
        }
        num_len++;
    }
    for (; i < src_len; i++) {
        if (src[i] == ' ') {
            break;
        }
        digit = get_digit(src[i]);

        if (digit > 9) {
            fprintf(stderr, "The source base should be decimal\n");
            return -1;
        }
        *src_base = *src_base * 10 + digit;
        src_base_len++;
    }
    for (; i < src_len; i++) {
        digit = get_digit(src[i]);

        if (digit > 9) {
            fprintf(stderr, "The target base should be decimal\n");
            return -1;
        }
        *dest_base = *dest_base * 10 + digit;
        dest_base_len++;
    }

    if (!num_len || !src_base_len || !dest_base_len) {
        fprintf(
            stderr,
            "Invalid source foramat: \"<num> <source base> <target base>\"\n");
        return -1;
    }
    if (max_digit >= *src_base) {
        fprintf(stderr, "The source number is not in a base %d\n", *src_base);
        return -1;
    }
}