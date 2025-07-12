
notest=1

CC = avr-gcc
AR = avr-ar

config=$(shell realpath config/avr-gcc.h)

CSTD = c11
CFLAGS += -Wno-error=pragmas -Wno-strict-aliasing
