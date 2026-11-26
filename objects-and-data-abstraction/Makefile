CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -O2
BUILD    := build

PROGRAMS := $(BUILD)/euclides $(BUILD)/game $(BUILD)/curses-hello $(BUILD)/puzzle $(BUILD)/lista-doble

.PHONY: all clean test
all: $(PROGRAMS)

$(BUILD):
	mkdir -p $@

$(BUILD)/euclides: EuclidesExtendido/ext.cc | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD)/game: GameNcurses/main.cc $(wildcard GameNcurses/*.h) | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ GameNcurses/main.cc -lncurses

$(BUILD)/curses-hello: GameNcurses/pr.cc | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $< -lncurses

$(BUILD)/puzzle: Puzzle/main.cpp Puzzle/Puzzle.cpp Puzzle/Puzzle.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ Puzzle/main.cpp Puzzle/Puzzle.cpp

$(BUILD)/lista-doble: ListaDoblementeEnlazada/main.cc ListaDoblementeEnlazada/lista.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ ListaDoblementeEnlazada/main.cc

# Unit tests run under AddressSanitizer and UBSan.
$(BUILD)/unit_tests: tests/unit_tests.cc Puzzle/Puzzle.cpp Puzzle/Puzzle.h EuclidesExtendido/ext.cc $(wildcard GameNcurses/*.h) | $(BUILD)
	$(CXX) -std=c++17 -g -O1 -fsanitize=address,undefined -fno-sanitize-recover=undefined -o $@ tests/unit_tests.cc Puzzle/Puzzle.cpp -lncurses

test: all $(BUILD)/unit_tests
	$(BUILD)/unit_tests
	tests/smoke_game.sh

clean:
	rm -rf $(BUILD)
