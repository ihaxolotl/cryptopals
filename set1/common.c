#include <stddef.h>
#include <stdlib.h>

unsigned char from_hex_char(unsigned char ch)
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

int from_hex_string(const char *in, size_t inlen, unsigned char **out,
                    size_t *outlen)
{
    unsigned char *buf = NULL;
    const size_t buflen = (inlen + 1) / 2;

    buf = malloc(buflen);
    if (!buf)
        return -1;

    for (size_t i = 0, j = 0; i < inlen && j < buflen; i += 2, j++) {
        const unsigned char a = from_hex_char((unsigned char)in[i]);
        const unsigned char b = from_hex_char((unsigned char)in[i + 1]);

        buf[j] = (unsigned char)((a << 4) | b);
    }
    *out = buf;
    *outlen = buflen;
    return 0;
}

size_t align_up(size_t value, size_t alignment)
{
    return (value + alignment - 1) & ~(alignment - 1);
}
