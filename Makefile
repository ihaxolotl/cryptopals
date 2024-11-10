.PHONY: all clean

BUILD_ROOT := dist

Q       := @
CC      := clang
RM      := rm -rf
MKDIR   := mkdir -p

CFLAGS  := -Wall                           \
           -Wextra                         \
           -Werror                         \
           -Wpedantic                      \
           -Wno-unused-parameter           \
           -Wconversion                    \
           -std=c99 -g3 -ggdb -O0

LDFLAGS := -fno-omit-frame-pointer         \
           -fsanitize=address              \
           -fsanitize=undefined            \

SRCS_01 := set1/common.c                   \
           set1/01-convert-hex-to-base64.c

SRCS_02 := set1/common.c                   \
           set1/02-fixed-xor.c

BUILD_TARGET_01 := $(BUILD_ROOT)/01-convert-hex-to-base64
BUILD_TARGET_02 := $(BUILD_ROOT)/02-fixed-xor

all: $(BUILD_ROOT) $(BUILD_TARGET_01) $(BUILD_TARGET_02)

clean:
	$(Q)$(RM) $(BUILD_ROOT)

$(BUILD_ROOT):
	$(Q)$(MKDIR) $@

$(BUILD_TARGET_01): $(SRCS_01)
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_TARGET_02): $(SRCS_02)
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
