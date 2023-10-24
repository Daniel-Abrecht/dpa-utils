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

CFLAGS  += --std=c17
CFLAGS  += -Iinclude
CFLAGS  += -Wall -Wextra -pedantic -Werror
#CFLAGS  += -fstack-protector-all
CFLAGS  += -Wno-missing-field-initializers -Wno-missing-braces
#CFLAGS  += -fmax-errors=2

CFLAGS  += -fvisibility=hidden

ifndef debug
CFLAGS  += -ffunction-sections -fdata-sections
LDFLAGS += -Wl,--gc-sections
endif

LDLIBS += -lm

OBJECTS := $(patsubst %,build/$(TYPE)/o/%.o,$(SOURCES))
ASMOUT  := $(patsubst %,build/$(TYPE)/s/%.s,$(SOURCES))

B-TS := bin/$(TYPE)/dpa-testsuite

BINS  := $(patsubst src/main/%.c,bin/$(TYPE)/%,$(filter src/main/%.c,$(SOURCES)))
TESTS := $(patsubst test/%.c,%,$(filter test/%.c,$(SOURCES)))

export LD_LIBRARY_PATH=$(shell realpath -m "lib/$(TYPE)/")

SHELL_CMD="$$SHELL"


all: source-checks bin lib

.PHONY: all source-checks bin lib clean get//bin get//lib install uninstall shell test asm

source-checks: build/.check-all

build/.check-header-compile: $(HEADERS)
	mkdir -p $(dir $@)
	@echo "Verifying that headers compile on their own..."
	find include/dpa/ -type f -iname "*.h" -print0 | xargs -0tL1 $(CC) -x c -fPIC -c -o /dev/null $(CFLAGS)
	touch $@

build/.check-inline-export: $(HEADERS)
	mkdir -p $(dir $@)
	@echo "Serching for inline functions which have not been exported with DPA_U_EXPORT..."
	! grep -r "^inline" include/
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
	    line="$$(printf "%s\n" "$$macro" | grep -a ': .*DPA__G(')" || true; \
	    printf '%s\n' "$$line" | while IFS=':' read -r T V; \
	    do \
	      l="$$( ( \
	          printf '%s\n' "$$T" | sed 's/^  *\|  *$$//g'; \
	          printf '%s\n' "$$V" | grep -o 'DPA__G([^,]*' | sed 's/DPA__G(//'; \
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


bin: $(BINS)

asm: $(ASMOUT)

lib: lib/$(TYPE)/lib$(SONAME).a \
     lib/$(TYPE)/lib$(SONAME).so

get//bin:
	@echo bin/$(TYPE)/

get//lib:
	@echo lib/$(TYPE)/

bin/$(TYPE)/%: build/$(TYPE)/o/src/main/%.c.o lib/$(TYPE)/lib$(SONAME).so
	mkdir -p $(dir $@)
	$(CC) -o $@ $(LDFLAGS) $< -Llib/$(TYPE)/ -l$(SONAME) $(LDLIBS)

build/$(TYPE)/bin/%: build/$(TYPE)/o/test/%.c.o lib/$(TYPE)/lib$(SONAME).so
	mkdir -p $(dir $@)
	$(CC) -o $@ $(LDFLAGS) $< -Llib/$(TYPE)/ -l$(SONAME)

lib/$(TYPE)/lib$(SONAME).so: lib/$(TYPE)/lib$(SONAME).a
	ln -sf "lib$(SONAME).so" "$@.0"
	$(CC) -o $@ -Wl,-Map=$@.map -Wl,--no-undefined -Wl,-soname,lib$(SONAME).so.$(MAJOR) --shared -fPIC $(LDFLAGS) -Wl,--whole-archive $^ -Wl,--no-whole-archive

lib/$(TYPE)/lib$(SONAME).a: $(filter-out build/$(TYPE)/o/src/main/%,$(filter-out build/$(TYPE)/o/test/%,$(OBJECTS)))
	mkdir -p $(dir $@)
	rm -f $@
	$(AR) q $@ $^

build/$(TYPE)/s/%.c.s: %.c makefile $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) -fPIC -S -o $@ $(CFLAGS) $< # -fverbose-asm

build/$(TYPE)/o/%.c.o: %.c makefile $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) -fPIC -c -o $@ $(CFLAGS) $<

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
