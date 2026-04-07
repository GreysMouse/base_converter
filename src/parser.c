#include "../include/parser.h"
#include <stdio.h>

long parse(const char *src, long src_len, int *src_base, int *dest_base)
{
    int src_base_loc = 0, dest_base_loc = 0, digit, max_digit = 0;
    long i, num_len = 0, src_base_len = 0, dest_base_len = 0;

    for (i = 0; i < src_len; i++) {
        if (src[i] == ' ') {
            break;
        }
        digit = get_digit(src[i]);

        if (digit == -1) {
            fprintf(stderr, "Base of provided number exceeds 62\n");
            return -1;
        }
        if (digit > max_digit) {
            max_digit = digit;
        }
        num_len++;
    }
    for (++i; i < src_len; i++) {
        if (src[i] == ' ') {
            break;
        }
        digit = get_digit(src[i]);

        if (digit > 9) {
            fprintf(stderr, "The source base should be decimal\n");
            return -1;
        }
        src_base_loc = src_base_loc * 10 + digit;
        src_base_len++;
    }
    for (++i; i < src_len; i++) {
        if (src[i] == ' ') {
            break;
        }
        digit = get_digit(src[i]);

        if (digit > 9) {
            fprintf(stderr, "The target base should be decimal\n");
            return -1;
        }
        dest_base_loc = dest_base_loc * 10 + digit;
        dest_base_len++;
    }
    if (!num_len || !src_base_len || !dest_base_len) {
        fprintf(stderr,
                "Invalid format: \"<num> <source base> <target base>\"\n");
        return -1;
    }
    if (src_base_loc < 2 || src_base_loc > 62) {
        fprintf(stderr, "The source base should be between 2 and 62\n");
        return -1;
    }
    if (dest_base_loc < 2 || dest_base_loc > 62) {
        fprintf(stderr, "The target base should be between 2 and 62\n");
        return -1;
    }
    if (max_digit >= src_base_loc) {
        fprintf(stderr, "The source number is not in a base %d\n",
                src_base_loc);
        return -1;
    }
    *src_base = src_base_loc;
    *dest_base = dest_base_loc;

    return num_len;
}

int get_digit(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 36;
    }
    return -1;
}

char get_digit_char(int d)
{
    if (d >= 0 && d < 10) {
        return d + '0';
    }
    if (d >= 10 && d < 36) {
        return d + 'a';
    }
    if (d >= 36 && d < 62) {
        return d + 'A';
    }
    return -1;
}