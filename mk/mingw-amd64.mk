notest = 1

LDFLAGS += -static-libgcc
LDLIBS += -l:libpthread.a

CC = x86_64-w64-mingw32-gcc

config=$(shell realpath config/mingw.h)

a-ext = .a.lib
so-ext = .dll
o-ext = .obj
bin-ext = .exe
