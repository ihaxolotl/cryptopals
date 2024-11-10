#define _GNU_SOURCE
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "common.h"

static const char *INPUT_01 =
    "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f"
    "7573206d757368726f6f6d";

static const char BASE64_CHARS[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

ssize_t base64_encode(const unsigned char *input, size_t input_length,
                      char **output)
{
    unsigned int ac = 0;
    int bits = 0;
    char *buf, *cp;
    const size_t n = align_up(4 * input_length / 3, 4);

    assert(n + 1 < SSIZE_MAX);

    buf = malloc(n + 1);
    if (!buf)
        return -1;

    cp = buf;

    for (size_t i = 0; i < input_length; i++) {
        ac = (ac << 8) | input[i];
        bits += 8;
        do {
            bits -= 6;
            *cp++ = BASE64_CHARS[(ac >> bits) & 0x3f];
        } while (bits >= 6);
    }
    if (bits) {
        *cp++ = BASE64_CHARS[(ac << (6 - bits)) & 0x3f];
        bits -= 6;
    }
    while (bits < 0) {
        *cp++ = '=';
        bits += 2;
    }

    *cp = '\0';
    *output = buf;
    return (ssize_t)(cp - buf);
}

int main(void)
{
    unsigned char *buf;
    char *output;
    size_t buflen;
    const char *input = INPUT_01;
    const size_t input_length = strlen(input);

    if (from_hex_string(input, input_length, &buf, &buflen) < 0)
        return EXIT_FAILURE;
    if (base64_encode(buf, buflen, &output) < 0) {
        free(buf);
        return EXIT_FAILURE;
    }

    printf("%s\n", output);
    free(output);
    free(buf);
    return EXIT_SUCCESS;
}
