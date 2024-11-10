#ifndef __CRYPTOPALS_COMMON_H__
#define __CRYPTOPALS_COMMON_H__

#include <stddef.h>

extern unsigned char from_hex_char(unsigned char ch);
extern int from_hex_string(const char *in, size_t inlen, unsigned char **out,
                           size_t *outlen);
extern size_t align_up(size_t value, size_t alignment);

#endif
