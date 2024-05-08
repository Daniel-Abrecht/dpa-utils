.SECONDARY:
.SUFFIXES:
.PHONY: all bin clean

CFLAGS += -std=c17
CXFLAGS += -Wall -Wextra -pedantic
CXFLAGS += -Wno-missing-field-initializers -Wno-missing-braces
CXFLAGS += -ffunction-sections -fdata-sections
CXFLAGS += -O2
CXFLAGS += -Iinclude
CFLAGS += $(CXFLAGS)
CXXFLAGS += $(CXFLAGS)
LDFLAGS += -Wl,--gc-sections
LDLIBS += -ldpa-utils

HEADERS := $(shell find include -type f -name "*.h" -not -name ".*")
SOURCES := $(shell find src -type f -iname "*.c" -or -iname "*.cpp")
OBJECTS := $(patsubst %,build/o/%.o,$(SOURCES))
BINS := $(patsubst src/main/%.c,bin/%,$(filter src/main/%.c,$(SOURCES)))

all: bin

bin: $(BINS)

benchmark: $(patsubst bin/%,res/%.svg,$(BINS))

bin/%: build/o/src/main/%.c.o build/all.a
	mkdir -p $(dir $@)
	$(CXX) -o $@ $(LDFLAGS) -Wl,--whole-archive $^ -Wl,--no-whole-archive $(LDLIBS)

build/all.a: $(filter-out build/o/src/main/%,$(OBJECTS))
	mkdir -p $(dir $@)
	rm -f $@
	$(AR) q $@ $^

build/o/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $(CFLAGS) $^

build/o/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c -o $@ $(CXXFLAGS) $^

clean:
	rm -rf res bin build

res/%.dat: bin/%
	mkdir -p $(dir $@)
	$< | tee $@
	chmod +x $@

res/%.svg: res/%.dat
	$< >$@

