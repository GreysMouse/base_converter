#include "parser.h"
#include <stdio.h>

#define DELIMITER ' '
#define WHITESPACE(C) ((C) == '\n' || (C) == '\t' || (C) == '\v')

/* Description is in the "parser.h" */
long parse(const char *input, long input_len, int *from_base, int *to_base)
{
    int from_base_loc = 0, to_base_loc = 0, digit, max_digit = 0;
    long i, num_len = 0, from_base_len = 0, to_base_len = 0;

    for (i = 0; i < input_len; i++) {
        char c = input[i];

        if (c == DELIMITER) {
            break;
        }
        if (WHITESPACE(c)) {
            fprintf(stderr,
                    "Invalid format: \"<num> <source base> <target base>\"\n");
            return -1;
        }
        digit = get_digit(c);

        if (digit == -1) {
            fprintf(stderr, "Base of provided number exceeds 62\n");
            return -1;
        }
        if (digit > max_digit) {
            max_digit = digit;
        }
        num_len++;
    }
    for (++i; i < input_len; i++) {
        char c = input[i];

        if (c == DELIMITER) {
            break;
        }
        if (WHITESPACE(c)) {
            fprintf(stderr,
                    "Invalid format: \"<num> <source base> <target base>\"\n");
            return -1;
        }
        digit = get_digit(c);

        if (digit == -1 || digit > 9) {
            fprintf(stderr, "The source base should be decimal\n");
            return -1;
        }
        from_base_loc = from_base_loc * 10 + digit;
        from_base_len++;
    }
    for (++i; i < input_len; i++) {
        char c = input[i];

        if (c == DELIMITER || WHITESPACE(c)) {
            break;
        }
        digit = get_digit(c);

        if (digit == -1 || digit > 9) {
            fprintf(stderr, "The target base should be decimal\n");
            return -1;
        }
        to_base_loc = to_base_loc * 10 + digit;
        to_base_len++;
    }
    if (!num_len || !from_base_len || !to_base_len) {
        fprintf(stderr,
                "Invalid format: \"<num> <source base> <target base>\"\n");
        return -1;
    }
    if (from_base_loc < 2 || from_base_loc > 62) {
        fprintf(stderr, "The source base should be between 2 and 62\n");
        return -1;
    }
    if (to_base_loc < 2 || to_base_loc > 62) {
        fprintf(stderr, "The target base should be between 2 and 62\n");
        return -1;
    }
    if (max_digit >= from_base_loc) {
        fprintf(stderr, "The source number is not in a base %d\n",
                from_base_loc);
        return -1;
    }
    *from_base = from_base_loc;
    *to_base = to_base_loc;

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
        return d + 'a' - 10;
    }
    if (d >= 36 && d < 62) {
        return d + 'A' - 36;
    }
    return -1;
}