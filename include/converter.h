#ifndef CONVERTER_H
#define CONVERTER_H

/* Params:
 * num - numeric chars of number;
 * num_len - count of chars (or digits) of num;
 * from_base - in decimal notation;
 * to_base - in decimal notation.
 *
 * Returns null-terminated string containing numeric chars of convertation
 * result. Inserts some number of leading zeros. During processing num_len
 * bytes of num buffer will be replaced with arbitrary data. Returns NULL if
 * memory allocation for the result fails.
 */
char *convert(char *num, long num_len, int from_base, int to_base);

#endif