#define _GNU_SOURCE
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static const char *INPUT_01 =
    "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f"
    "7573206d757368726f6f6d";

static const char BASE64_CHARS[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static unsigned char from_hex_char(unsigned char ch)
{
    if (ch >= 'A' && ch <= 'F') {
        return ch - 'A' + 10;
    } else if (ch >= 'a' && ch <= 'f') {
        return ch - 'a' + 10;
    } else if (ch >= '0' && ch <= '9') {
        return ch - '0';
    } else {
        return 0;
    }
}

static size_t align_up(size_t value, size_t alignment)
{
    return (value + alignment - 1) & ~(alignment - 1);
}

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
    unsigned char *buf = NULL;
    char *output = NULL;
    const char *input = INPUT_01;
    const size_t input_length = strlen(input);
    const size_t buflen = (input_length + 1) / 2;

    buf = malloc(buflen);
    if (!buf)
        return EXIT_FAILURE;

    for (size_t i = 0, j = 0; i < input_length && j < buflen; i += 2, j++) {
        const unsigned char a = from_hex_char((unsigned char)input[i]);
        const unsigned char b = from_hex_char((unsigned char)input[i + 1]);

        buf[j] = (unsigned char)((a << 4) | b);
    }

    if (base64_encode((unsigned char *)buf, buflen, &output) < 0)
        return EXIT_FAILURE;

    printf("%s\n", output);
    free(output);
    return EXIT_SUCCESS;
}
