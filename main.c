#include "include/converter.h"
#include "include/parser.h"
#include "include/stream.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv)
{
    FILE *src, *dest = stdout;
    char *input, *res;
    int from_base, to_base, ret = EXIT_FAILURE;
    long input_len, num_len;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <src file> [<dest file>]\n", argv[0]);
        goto cleanup;
    }

    src = open_file(argv[1], "r");

    if (!src) {
        perror(argv[1]);
        goto cleanup;
    }

    input_len = file_size(src);

    if (input_len == -1) {
        perror(argv[1]);
        goto cleanup;
    }

    if (argv[2]) {
        dest = open_file(argv[2], "w");
    }

    if (!dest) {
        perror(argv[2]);
        goto cleanup;
    }

    input = malloc(sizeof(char) * input_len);

    if (!input) {
        perror(argv[0]);
        goto cleanup;
    }

    if (fread(input, sizeof(char), input_len, src) != input_len) {
        fprintf(stderr, "%s read error\n", argv[1]);
        goto cleanup;
    };

    /* Validate input data and get from_base and to_base values */
    num_len = parse(input, input_len, &from_base, &to_base);

    if (num_len < 0) {
        goto cleanup;
    }

    /* Return result as C-string to avoid length pass */
    res = convert(input, num_len, from_base, to_base);

    if (!res) {
        perror(argv[0]);
        goto cleanup;
    }

    if (fputs(res, dest) == EOF) {
        fprintf(stderr, "%s write error\n", argv[2] ? argv[2] : "stdout");
        goto cleanup;
    };

    if (dest == stdout) {
        fputc('\n', dest);
    }

    ret = EXIT_SUCCESS;

cleanup:
    if (src) {
        fclose(src);
    }
    if (dest != stdout) {
        fclose(dest);
    }
    free(input);

    return ret;
}