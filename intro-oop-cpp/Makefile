CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -O2
BUILD    := build
# fiboLog needs the header-only ttmath library: make fibo TTMATH_DIR=/path/to/ttmath-0.9.3
TTMATH_DIR ?=

.PHONY: all fibo clean
all: $(BUILD)/lista $(BUILD)/abeja

$(BUILD):
	mkdir -p $@

$(BUILD)/lista: ListaSE/main.cc ListaSE/lista.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ ListaSE/main.cc

$(BUILD)/abeja: Practica/ProblemaAbeja.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $<

fibo: $(BUILD)/fiboLog
$(BUILD)/fiboLog: Practica/fiboLog.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $(if $(TTMATH_DIR),-I$(TTMATH_DIR)) -o $@ $<

clean:
	rm -rf $(BUILD)
