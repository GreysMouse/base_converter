#ifndef PARSER_H
#define PARSER_H

/* Returns number string length.
 * Write values to src_base and dest_base. */
long parse(const char *src, long src_len, int *src_base, int *dest_base);

#endif