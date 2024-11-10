.PHONY: all clean

BUILD_ROOT := dist
BUILD_TARGET := $(BUILD_ROOT)/cryptopals

Q       := @
CC      := clang
RM      := rm -rf
MKDIR   := mkdir -p

CFLAGS  := -Wall                       \
           -Wextra                     \
           -Werror                     \
           -Wpedantic                  \
           -Wno-unused-parameter       \
           -Wconversion                \
           -std=c99 -g3 -ggdb -O0

LDFLAGS := -fno-omit-frame-pointer     \
           -fsanitize=address          \
           -fsanitize=undefined        \

SRCS := set1/common.c                  \
        set1/01-convert-hex-to-base64.c

all: $(BUILD_ROOT) $(BUILD_TARGET)

clean:
	$(Q)$(RM) $(BUILD_ROOT)

$(BUILD_ROOT):
	$(Q)$(MKDIR) $@

$(BUILD_TARGET): $(SRCS)
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
