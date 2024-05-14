notest = 1
# TODO: Polyfill threads.h. stdatomic.h exists.
LDFLAGS += -static-libgcc
LDLIBS += -l:libpthread.a

CC = x86_64-w64-mingw32-gcc

a-ext = .a.lib
so-ext = .dll
o-ext = .obj
bin-ext = .exe
