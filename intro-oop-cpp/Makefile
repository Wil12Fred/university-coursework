CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -O2
BUILD    := build
# fiboLog uses the header-only ttmath library, vendored in third_party/.
TTMATH_DIR ?= third_party/ttmath-0.9.3

.PHONY: all fibo test clean
all: $(BUILD)/lista $(BUILD)/abeja $(BUILD)/fiboLog

$(BUILD):
	mkdir -p $@

$(BUILD)/lista: ListaSE/main.cc ListaSE/lista.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ ListaSE/main.cc

$(BUILD)/abeja: Practica/ProblemaAbeja.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $<

fibo: $(BUILD)/fiboLog
# -isystem: ttmath's own headers produce warnings that are not ours to fix
$(BUILD)/fiboLog: Practica/fiboLog.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -isystem $(TTMATH_DIR) -o $@ $<

test: all
	tests/run_golden.sh

clean:
	rm -rf $(BUILD)
