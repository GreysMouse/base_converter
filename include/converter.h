#ifndef CONVERTER_H
#define CONVERTER_H

/* Fills the last bytes of dest buffer with its result - numeric chars of number
 * in new base.
 * Returns the number of bytes of the result to calculate the offset relative to
 * dest when printing.
 * Here src is an array of numeric chars of source number.
 * During processing src_len bytes of src buffer will be replaced with arbitrary
 * data. */
long convert(char *src, long src_len, char *dest, long dest_len);

#endif