# Nothing to compile: SPIM assembles and runs each .asm file directly.
SPIM ?= spim

.PHONY: all test
all:
	@echo "Run a program with: $(SPIM) -file hello.asm"

test:
	SPIM=$(SPIM) tests/run_golden.sh
