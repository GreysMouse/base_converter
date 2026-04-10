#ifndef CONVERTER_H
#define CONVERTER_H

/* Params:
 * src - text line read from input file;
 * src_len - count of chars read from input file;
 * dest - buffer to write result of convertation (has enought size);
 * dest_len - count of chars available for result;
 *
 * Fills last bytes of dest with numeric chars of result.
 * During processing src_len bytes of src will be replaced with arbitrary data.
 * Returns count of chars of result to calculate the offset relative to dest
 * for printing.
 */
long convert(char *src, long src_len, char *dest, long dest_len);

#endif