CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -pthread
BUILD    := build

# Every .cc file that defines main() becomes build/<Dir>-<file>.
SOURCES  := $(shell grep -l 'int main' */*.cc)
PROGRAMS := $(patsubst %.cc,$(BUILD)/%,$(subst /,-,$(SOURCES)))

.PHONY: all clean list
all: $(PROGRAMS)

list:
	@echo $(PROGRAMS) | tr ' ' '\n'

$(BUILD):
	mkdir -p $@

.SECONDEXPANSION:
$(PROGRAMS): $(BUILD)/%: $$(subst -,/,$$*).cc $$(wildcard $$(dir $$(subst -,/,$$*))*.h) | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $< $(if $(findstring Bomb,$*),-lncurses)

clean:
	rm -rf $(BUILD)
