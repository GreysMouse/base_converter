#ifndef PARSER_H
#define PARSER_H

/* Params:
 * input - text data read from input file;
 * input_len - count of chars read from input file;
 * from_base - in decimal notation;
 * to_base - in decimal notation.
 *
 * Returns chars d(or digits) count of provided number. Writes values to
 * from_base and to_base.
 */
long parse(const char *input, long input_len, int *from_base, int *to_base);

int get_digit(char c);
char get_digit_char(int d);

#endif