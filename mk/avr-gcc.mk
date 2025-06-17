
notest=1

CC = avr-gcc
AR = avr-ar

CSTD = c11
CFLAGS += '-DDPA_U_CONFIG="$(shell realpath config/avr-gcc.h)"'
CFLAGS += -Wno-error=pragmas -Wno-strict-aliasing
