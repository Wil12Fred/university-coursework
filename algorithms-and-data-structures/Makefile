CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -pthread
BUILD    := build

# Every .cc file that defines main() becomes build/<Dir>-<file>.
SOURCES  := $(filter-out tests/%,$(shell grep -l 'int main' */*.cc))
PROGRAMS := $(patsubst %.cc,$(BUILD)/%,$(subst /,-,$(SOURCES)))

.PHONY: all clean list test
all: $(PROGRAMS)

list:
	@echo $(PROGRAMS) | tr ' ' '\n'

$(BUILD):
	mkdir -p $@

.SECONDEXPANSION:
$(PROGRAMS): $(BUILD)/%: $$(subst -,/,$$*).cc $$(wildcard $$(dir $$(subst -,/,$$*))*.h) | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $< $(if $(findstring Bomb,$*),-lncurses)

# Unit tests run under AddressSanitizer so an out-of-bounds access fails them.
# The AVL and red-black code never frees its nodes, so leak checking is off.
$(BUILD)/unit_tests: tests/unit_tests.cc $(SOURCES) $(wildcard */*.h) | $(BUILD)
	$(CXX) -std=c++17 -g -O1 -pthread -fsanitize=address,undefined -fno-sanitize-recover=undefined -o $@ $<

test: all $(BUILD)/unit_tests
	ASAN_OPTIONS=detect_leaks=0 $(BUILD)/unit_tests
	tests/run_golden.sh

clean:
	rm -rf $(BUILD)
