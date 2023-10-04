.SECONDARY:

HEADERS := $(shell find include -type f -name "*.h" -not -name ".*")
SOURCES := $(shell find src test -type f -iname "*.c")

SONAME = dpa-utils
MAJOR  = 0
MINOR  = 0
PATCH  = 0

prefix = /usr/local/

TYPE := release

unexport LD_PRELOAD

ifdef debug
TYPE := debug
CFLAGS  += -O0 -g
LDFLAGS += -g
else
CFLAGS  += -O3
endif

ifdef asan
TYPE := $(TYPE)-asan
CFLAGS  += -fsanitize=address,undefined,bounds,enum
LDFLAGS += -fsanitize=address,undefined,bounds,enum
endif

ifdef coverage
TYPE := $(TYPE)-coverage
CFLAGS  += --coverage
LDFLAGS += --coverage
endif

CFLAGS  += --std=c17
CFLAGS  += -Iinclude
CFLAGS  += -Wall -Wextra -pedantic -Werror
CFLAGS  += -fstack-protector-all
CFLAGS  += -Wno-missing-field-initializers -Wno-missing-braces

CFLAGS  += -fvisibility=hidden

ifndef debug
CFLAGS  += -ffunction-sections -fdata-sections
LDFLAGS += -Wl,--gc-sections
endif

OBJECTS := $(patsubst %,build/$(TYPE)/o/%.o,$(SOURCES))

B-TS := bin/$(TYPE)/dpa-testsuite

BINS  := $(patsubst src/main/%.c,bin/$(TYPE)/%,$(filter src/main/%.c,$(SOURCES)))
TESTS := $(patsubst test/%.c,%,$(filter test/%.c,$(SOURCES)))

export LD_LIBRARY_PATH=$(shell realpath "lib/$(TYPE)/")

SHELL_CMD="$$SHELL"

.PHONY: all bin lib clean get//bin get//lib install uninstall shell test

all: bin lib

bin: $(BINS)

lib: lib/$(TYPE)/lib$(SONAME).a \
     lib/$(TYPE)/lib$(SONAME).so

get//bin:
	@echo bin/$(TYPE)/

get//lib:
	@echo lib/$(TYPE)/

bin/$(TYPE)/%: build/$(TYPE)/o/src/main/%.c.o lib/$(TYPE)/lib$(SONAME).so
	mkdir -p $(dir $@)
	$(CC) -o $@ $(LDFLAGS) $< -Llib/$(TYPE)/ -l$(SONAME)

build/$(TYPE)/bin/%: build/$(TYPE)/o/test/%.c.o lib/$(TYPE)/lib$(SONAME).so
	mkdir -p $(dir $@)
	$(CC) -o $@ $(LDFLAGS) $< -Llib/$(TYPE)/ -l$(SONAME)

lib/$(TYPE)/lib$(SONAME).so: lib/$(TYPE)/lib$(SONAME).a
	ln -sf "lib$(SONAME).so" "$@.0"
	$(CC) -o $@ -Wl,--no-undefined -Wl,-soname,lib$(SONAME).so.$(MAJOR) --shared -fPIC $(LDFLAGS) -Wl,--whole-archive $^ -Wl,--no-whole-archive

lib/$(TYPE)/lib$(SONAME).a: $(filter-out build/$(TYPE)/o/src/main/%,$(filter-out build/$(TYPE)/o/test/%,$(OBJECTS)))
	mkdir -p $(dir $@)
	rm -f $@
	$(AR) q $@ $^

build/$(TYPE)/o/%.c.o: %.c makefile $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) -fPIC -c -o $@ $(DFLAGS) $(CFLAGS) $<

clean:
	rm -rf build/$(TYPE)/ bin/$(TYPE)/ lib/$(TYPE)/

install:
	cp "lib/$(TYPE)/lib$(SONAME).so" "$(DESTDIR)$(prefix)/lib/lib$(SONAME).so.$(MAJOR).$(MINOR).$(PATCH)"
	ln -sf "lib$(SONAME).so.$(MAJOR).$(MINOR).$(PATCH)" "$(DESTDIR)$(prefix)/lib/lib$(SONAME).so.$(MAJOR).$(MINOR)"
	ln -sf "lib$(SONAME).so.$(MAJOR).$(MINOR).$(PATCH)" "$(DESTDIR)$(prefix)/lib/lib$(SONAME).so.$(MAJOR)"
	ln -sf "lib$(SONAME).so.$(MAJOR).$(MINOR).$(PATCH)" "$(DESTDIR)$(prefix)/lib/lib$(SONAME).so"
	cp "lib/$(TYPE)/lib$(SONAME).a" "$(DESTDIR)$(prefix)/lib/lib$(SONAME).a"
	cp -a include/dpa/utils/./ "$(DESTDIR)$(prefix)/include/dpa/utils/"
	cp include/dpa/utils.h "$(DESTDIR)$(prefix)/include/dpa/"
	ldconfig

uninstall:
	rm -f "$(DESTDIR)$(prefix)/lib/lib$(SONAME).so.$(MAJOR).$(MINOR).$(PATCH)"
	rm -f "$(DESTDIR)$(prefix)/lib/lib$(SONAME).so.$(MAJOR).$(MINOR)"
	rm -f "$(DESTDIR)$(prefix)/lib/lib$(SONAME).so.$(MAJOR)"
	rm -f "$(DESTDIR)$(prefix)/lib/lib$(SONAME).so"
	rm -f "$(DESTDIR)$(prefix)/lib/lib$(SONAME).a"
	rm -rf "$(DESTDIR)$(prefix)/include/dpa/utils/"
	rm -f "$(DESTDIR)$(prefix)/include/dpa/utils.h"

shell:
	if [ -z "$$SHELL" ]; then SHELL="$$(getent passwd $$(id -u) | cut -d : -f 7)"; fi; \
	if [ -z "$$SHELL" ]; then SHELL="/bin/sh"; fi; \
	PROMPT_COMMAND='if [ -z "$$PS_SET" ]; then PS_SET=1; PS1="(dpa-utils) $$PS1"; fi' \
	PATH="$$PWD/bin/$(TYPE)/:scripts/:$$PATH" \
	MANPATH="$$PWD/build/docs/api/man/:$$(man -w)" \
	  $(SHELL_CMD)
