.SECONDARY:
.SUFFIXES:

SHELL=/bin/bash

ifdef use
include $(patsubst %,mk/%.mk,$(use))
endif

ifdef config
export DPA_U_CONFIG=$(shell realpath $(config))
CFLAGS += '-DDPA_U_CONFIG="$(DPA_U_CONFIG)"'
endif

ifndef notest
HEADERS := $(shell find include -type f -name "*.h" -not -name ".*")
SOURCES := $(shell find src -not -path "src/special/*" -type f -iname "*.c")
else
HEADERS := $(shell find include -type f -name "*.h" -not -name ".*" -not -iname "*test*")
SOURCES := $(shell find src -not -path "src/special/*" -type f -iname "*.c" -not -iname "*test*")
endif

SOURCES += $(EXTRA_SOURCES)

SONAME = dpa-utils
MAJOR  = 0
MINOR  = 0
PATCH  = 0

prefix = /usr/local/

TYPE := release

unexport LD_PRELOAD

a-ext ?= .a
so-ext ?= .so
o-ext ?= .o
bin-ext ?= 

ifdef debug
ifeq ($(debug), v)
CFLAGS += -DDPA_U_DEBUG_VERBOSE
endif
TYPE := debug
CFLAGS  += -O0 -gdwarf-4 -DDPA_U_DEBUG
LDFLAGS += -gdwarf-4
else
CFLAGS  += -O2
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

CSTD ?= c17
CFLAGS  += --std=$(CSTD)
CFLAGS  += -D_DEFAULT_SOURCE
CFLAGS  += -Iinclude -I.
CFLAGS  := -Wall -Wextra -pedantic $(CFLAGS)
#CFLAGS  += -fstack-protector-all
CFLAGS  += -Wno-missing-field-initializers -Wno-missing-braces -Wno-static-in-inline
#CFLAGS  += -fmax-errors=2
CFLAGS  += -fdiagnostics-color=always

CFLAGS  += -fvisibility=hidden

ifndef debug
CFLAGS  += -ffunction-sections -fdata-sections
LDFLAGS += -Wl,--gc-sections
endif

LDLIBS += -lm

OBJECTS := $(patsubst %,build/$(TYPE)/o/%$(o-ext),$(SOURCES))
ASMOUT  := $(patsubst %,build/$(TYPE)/s/%.s,$(SOURCES))

B-TS := bin/$(TYPE)/dpa-testsuite$(bin-ext)

BINS  := $(patsubst src/main/%.c,bin/$(TYPE)/%$(bin-ext),$(filter src/main/%.c,$(SOURCES)))
TESTS := $(patsubst test/%.c,test//%,$(wildcard test/*.c))
TESTS += test//bo-conv
BO-CONV-TESTS := $(patsubst test/%.c,test//%,$(wildcard test/gen/*.c))

DOCSRC += README.md
DOCSRC += $(find docs -type f)

export LD_LIBRARY_PATH=$(shell realpath -m "lib/$(TYPE)/")

SHELL_CMD="$$SHELL"

ifndef noshared
shared_test := $(shell $(CC) -o build/.shared-test$(so-ext) --shared -fPIC src/special/nop.c >/dev/null 2>/dev/null; echo $$?)
else
shared_test=1
endif

ifeq (0,$(shared_test))
has_shared := 1
LIB := lib/$(TYPE)/lib$(SONAME)$(so-ext)
CFLAGS  += -fPIC
else
LIB := lib/$(TYPE)/lib$(SONAME)$(a-ext)
endif

export TYPE

all: source-checks bin lib

.PHONY: all source-checks bin lib clean get//bin get//lib install uninstall shell test asm docs test//bo-conv FORCE
FORCE:

do-test//set-map: build/unique-random

# Having a bunch of random, but unique, numbers is useful for tests
# This makes it easy to get a new unique number, as well as to get an already used one.
build/unique-random:
	( \
	  printf '%02X\n' $$(seq 0 255) | shuf; \
	  echo; \
	  printf '%04X\n' $$(seq 0 65535) | shuf; \
	  echo; \
	  tr -dc A-F0-9 </dev/urandom | fold -w 8 | head -n 65536 | sort -u | shuf; \
	  echo; \
	  tr -dc A-F0-9 </dev/urandom | fold -w 16 | head -n 65536 | sort -u | shuf; \
	  echo; \
	  tr -dc A-F0-9 </dev/urandom | fold -w 32 | head -n 65536 | sort -u | shuf; \
	  echo; \
	  tr -dc A-F0-9 </dev/urandom | fold -w 64 | head -n 65536 | sort -u | shuf; \
	  echo; \
	  tr -dc A-F0-9 </dev/urandom | fold -w 128 | head -n 65536 | sort -u | shuf; \
	  echo; \
	  tr -dc A-F0-9 </dev/urandom | fold -w 256 | head -n 65536 | sort -u | shuf; \
	  echo; \
	  tr -dc A-F0-9 </dev/urandom | fold -w 512 | head -n 65536 | sort -u | shuf; \
	  echo; \
	  cat /usr/share/dict/words | sort -u | shuf | head -n 65536; \
	  echo; \
	) >"$@"

source-checks: build/.check-all

build/.check-header-compile: $(HEADERS)
	mkdir -p $(dir $@)
	@echo "Verifying that headers compile on their own..."
	find include/dpa/ -type f -iname "*.h" -not -path '*/_*' -print0 | xargs -0tL1 $(CC) -x c -c -o /dev/null $(CFLAGS)
	touch $@

build/.check-inline-export: $(HEADERS)
	mkdir -p $(dir $@)
	@echo "Serching for inline functions which have not been exported with dpa__u_api..."
	! grep -r "\(^\| \)inline .*(" include/ | grep -v "\(:\| \)dpa__u_api "
	touch $@

build/.check-inline-extern: $(HEADERS)
	mkdir -p $(dir $@)
	@echo "Serching for inline functions without a following extern declaration..."

	grep -r --no-filename -o ' inline [^(]*(' include/ | sed -n 's/.* \([^( ]\+\)(.*/\1/p' | sort -u > build/inline-functions.txt
	grep -r --no-filename -o '^extern [^(]*(' src/ | sed -n 's/.* \([^( ]\+\)(.*/\1/p' | sort -u > build/extern-src-decs.txt
	diff build/inline-functions.txt build/extern-src-decs.txt

build/.check-g-macro: $(HEADERS)
	@echo "Checking DPA__G macros"
	@set -e; \
	trap 'echo "$$f"' EXIT; \
	for f in include/dpa/utils/*.h; \
	do \
	  perl -pe 's/\\\n/\xFF/' <"$$f" | grep -a '#define .*\(dpa_u_generic\|_Generic\)' | \
	  while IFS= read -r line; \
	  do \
	    macro="$$(printf "%s\n" "$$line" | sed 's/\xFF/\n/g')"; \
	    line="$$(printf "%s\n" "$$macro" | grep -a ': .*DPA_U_G(')" || true; \
	    printf '%s\n' "$$line" | while IFS=':' read -r T V; \
	    do \
	      l="$$( ( \
	          printf '%s\n' "$$T" | sed 's/^  *\|  *$$//g'; \
	          printf '%s\n' "$$V" | grep -o 'DPA_U_G([^,]*' | sed 's/DPA_U_G(//'; \
	        ) | sed 's/^\s*\|\s*$$//' | sed 's/\([a-zA-Z0-9_]\)  *\([a-zA-Z_]\)/\1 \2/' \
	          | sed 's/ \([^a-zA-Z_]\)/\1/' | sed 's/\([^a-zA-Z_]\) /\1/' \
	          | sort -u \
	      )"; \
	      if [ "$$(printf "%s\n" "$$l" | wc -l)" != 1 ]; \
	      then \
	        printf "Mismatching types.\nLine: %s\n%s\n" "$$T:$$V" "$$macro"; \
	        exit 1; \
	      fi; \
	    done; \
	  done; \
	done; \
	f=
	touch $@

build/.check-all: \
  build/.check-header-compile \
  build/.check-inline-export \
  build/.check-inline-extern \
  build/.check-g-macro
	@echo "Source code checks passed"
	touch $@

do-test//%: build/$(TYPE)/bin/test/%$(bin-ext) $(B-TS)
	$<

do-test//%: test/% $(B-TS)
	$<

test//%: $(B-TS) FORCE
	PATH="bin/$(TYPE)/:script/:$$PATH" $(B-TS) $* $(MAKE) "do-test//$*"

test//bo-conv: $(B-TS) FORCE
	$(B-TS) bo-conv $(MAKE) -k $(BO-CONV-TESTS)

test: $(B-TS)
	$(B-TS) utils $(MAKE) -k $(TESTS)

bin: $(BINS)
	@f="$$(find build/$(TYPE) -iname '*$(o-ext).err' | grep -v '/test/')"; \
	if [ -n "$$f" ]; then printf "\nThere have been warnings, see logs:\n%s\n" "$$f"; fi

asm: $(ASMOUT)

lib: $(LIB)

get//bin:
	@echo bin/$(TYPE)/

get//lib:
	@echo lib/$(TYPE)/

bin/$(TYPE)/%$(bin-ext): build/$(TYPE)/o/src/main/%.c$(o-ext) $(LIB)
	mkdir -p $(dir $@)
	$(CC) -o $@ $(LDFLAGS) $< -Llib/$(TYPE)/ -l$(SONAME) $(LDLIBS)

build/$(TYPE)/bin/%$(bin-ext): build/$(TYPE)/o/%.c$(o-ext) $(LIB)
	mkdir -p $(dir $@)
	$(CC) -o $@ $(LDFLAGS) $< -Llib/$(TYPE)/ -l$(SONAME)

lib/$(TYPE)/lib$(SONAME)$(so-ext): lib/$(TYPE)/lib$(SONAME)$(a-ext) $(filter build/$(TYPE)/o/src/special/%,$(OBJECTS))
	mkdir -p $(dir $@)
	ln -sf "lib$(SONAME)$(so-ext)" "$@.0"
	$(CC) -o $@ -Wl,-Map=$@.map -Wl,--no-undefined -Wl,-soname,lib$(SONAME)$(so-ext).$(MAJOR) --shared -fPIC $(LDFLAGS) -Wl,--whole-archive $^ -Wl,--no-whole-archive  $(LDLIBS)

lib/$(TYPE)/lib$(SONAME)$(a-ext): $(filter-out build/$(TYPE)/o/src/main/%,$(filter-out build/$(TYPE)/o/src/special/%,$(filter-out build/$(TYPE)/o/test/%,$(OBJECTS))))
	mkdir -p $(dir $@)
	rm -f $@
	$(AR) q $@ $^

build/$(TYPE)/s/%.c.s: %.c makefile $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) -S -o $@ $(CFLAGS) $< -fverbose-asm

build/$(TYPE)/o/%.c$(o-ext): %.c makefile $(HEADERS)
	mkdir -p $(dir $@)
	set -e -o pipefail; \
	( $(CC) -c -o $@ -DDPA__U_BUILD_LIB $(CFLAGS) $< 2>&1 >&3 | tee "$@.err" >&2; ) 3>&1
	@if [ ! -s "$@.err" ]; then rm -f "$@.err"; fi

build/$(TYPE)/o/main/%.c$(o-ext): %.c makefile $(HEADERS)
	mkdir -p $(dir $@)
	set -e -o pipefail; \
	( $(CC) -c -o $@ $(CFLAGS) $< >&3 2>&1 | tee "$@.err" >&2; ) 3>&1
	@if [ ! -s "$@.err" ]; then rm -f "$@.err"; fi

build/docs/api/.done: $(HEADERS) $(DOCSRC) Doxyfile
	rm -rf build/docs/api/
	mkdir -p build/docs/api/
	-doxygen
	-cp -r docs/. build/docs/api/html/
	-touch "$@"

clean//docs:
	rm -rf build/docs/api/

clean:
	rm -rf build/$(TYPE)/ bin/$(TYPE)/ lib/$(TYPE)/

install:
	mkdir -p "$(DESTDIR)$(prefix)/include/dpa/utils/"
	mkdir -p "$(DESTDIR)$(prefix)/lib/"
ifdef has_shared
	cp "lib/$(TYPE)/lib$(SONAME)$(so-ext)" "$(DESTDIR)$(prefix)/lib/lib$(SONAME)$(so-ext).$(MAJOR).$(MINOR).$(PATCH)"
	ln -sf "lib$(SONAME)$(so-ext).$(MAJOR).$(MINOR).$(PATCH)" "$(DESTDIR)$(prefix)/lib/lib$(SONAME)$(so-ext).$(MAJOR).$(MINOR)"
	ln -sf "lib$(SONAME)$(so-ext).$(MAJOR).$(MINOR).$(PATCH)" "$(DESTDIR)$(prefix)/lib/lib$(SONAME)$(so-ext).$(MAJOR)"
	ln -sf "lib$(SONAME)$(so-ext).$(MAJOR).$(MINOR).$(PATCH)" "$(DESTDIR)$(prefix)/lib/lib$(SONAME)$(so-ext)"
endif
ifndef notest
	cp "bin/$(TYPE)/dpa-testsuite$(bin-ext)" "$(DESTDIR)$(prefix)/bin/"
endif
	cp "lib/$(TYPE)/lib$(SONAME)$(a-ext)" "$(DESTDIR)$(prefix)/lib/lib$(SONAME)$(a-ext)"
	mkdir -p "$(DESTDIR)$(prefix)/include/dpa/utils/"
	cp -a include/dpa/utils/./ "$(DESTDIR)$(prefix)/include/dpa/utils/"
	cp include/dpa/utils.h "$(DESTDIR)$(prefix)/include/dpa/"
	if [ -n "$$DPA_U_CONFIG" ]; then cp "$$DPA_U_CONFIG" "$(DESTDIR)$(prefix)/include/dpa/config.h"; fi
	-ldconfig

uninstall:
	rm -f "$(DESTDIR)$(prefix)/lib/lib$(SONAME)$(so-ext).$(MAJOR).$(MINOR).$(PATCH)"
	rm -f "$(DESTDIR)$(prefix)/lib/lib$(SONAME)$(so-ext).$(MAJOR).$(MINOR)"
	rm -f "$(DESTDIR)$(prefix)/lib/lib$(SONAME)$(so-ext).$(MAJOR)"
	rm -f "$(DESTDIR)$(prefix)/lib/lib$(SONAME)$(so-ext)"
	rm -f "$(DESTDIR)$(prefix)/lib/lib$(SONAME)$(a-ext)"
	rm -f "bin/$(TYPE)/dpa-testsuite$(bin-ext)"
	rm -rf "$(DESTDIR)$(prefix)/include/dpa/utils/"
	rm -f "$(DESTDIR)$(prefix)/include/dpa/utils.h"

shell:
	if [ -z "$$SHELL" ]; then SHELL="$$(getent passwd $$(id -u) | cut -d : -f 7)"; fi; \
	if [ -z "$$SHELL" ]; then SHELL="/bin/sh"; fi; \
	PROMPT_COMMAND='if [ -z "$$PS_SET" ]; then PS_SET=1; PS1="(dpa-utils) $$PS1"; fi' \
	PATH="$$PWD/bin/$(TYPE)/:$$PWD/script/:$$PATH" \
	MANPATH="$$PWD/build/docs/api/man/:$$(man -w)" \
	  $(SHELL_CMD)

docs: build/docs/api/.done
