#include "include/converter.h"
#include "include/stream.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv)
{
    FILE *src, *dest = stdout;
    char *buf, *res;
    int ret = EXIT_FAILURE;
    long src_len, res_len, res_offset;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <src file> [<dest file>]\n", argv[0]);
        goto cleanup;
    }

    src = open_file(argv[1], "r");

    if (!src) {
        perror(argv[1]);
        goto cleanup;
    }

    src_len = file_size(src);

    if (src_len == -1) {
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

    buf = malloc(sizeof(char) * 2 * src_len);

    if (!buf) {
        perror(argv[0]);
        goto cleanup;
    }

    if (fread(buf, sizeof(char), src_len, src) != src_len) {
        fprintf(stderr, "%s read error\n", argv[1]);
        goto cleanup;
    };

    res = buf + src_len;
    res_len = convert(buf, src_len, res, src_len);

    if (res_len < 0) {
        goto cleanup;
    }

    res_offset = src_len - res_len;

    if (fwrite(res + res_offset, sizeof(char), res_len, dest) != res_len) {
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
    free(buf);

    return ret;
}