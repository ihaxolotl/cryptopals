#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

static const char *INPUT_02 = "1c0111001f010100061a024b53535009181c";
static const char *INPUT_02b = "686974207468652062756c6c277320657965";

int main(void)
{
    unsigned char *araw, *braw;
    size_t araw_len, braw_len;
    const char *a = INPUT_02;
    const char *b = INPUT_02b;
    const size_t a_len = strlen(a);
    const size_t b_len = strlen(b);

    if (from_hex_string(a, a_len, &araw, &araw_len) < 0)
        return EXIT_FAILURE;
    if (from_hex_string(b, b_len, &braw, &braw_len) < 0) {
        free(araw);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < araw_len; i++) {
        printf("%02x", araw[i] ^ braw[i]);
    }

    printf("\n");
    free(araw);
    free(braw);
    return EXIT_SUCCESS;
}
