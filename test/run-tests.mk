
tests := $(shell cat $(TEST_FILE))

all: $(tests:%=$(TEST_PREFIX)%.result)
	for test in $$(cat $(TEST_FILE)); \
	do \
	  f="$(TEST_PREFIX)$$test.result"; \
	  f="$$f" dpa-testsuite $$test sh -c '[ -f "$$f" ] && exit $$(cat "$$f")'; \
	done; \
	true

force:

$(TEST_PREFIX)%.result:
	r="$@"; \
	e="$${r%.result}"; \
	( $(MAKE) -s --no-print-directory "$$e" 2>"$$e.mk.err"; ) && ( "$$e" 2>"$$e.err"; ); \
	echo $$? >'$@'; \
	if [ ! -s "$$e.mk.err" ]; then rm -f "$$e.mk.err"; fi; \
	if [ ! -s "$$e.err" ]; then rm -f "$$e.err"; fi; \
	true
