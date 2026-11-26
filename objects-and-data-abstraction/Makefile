CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -O2
BUILD    := build

PROGRAMS := $(BUILD)/euclides $(BUILD)/game $(BUILD)/curses-hello $(BUILD)/puzzle $(BUILD)/lista-doble

.PHONY: all clean
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

clean:
	rm -rf $(BUILD)
