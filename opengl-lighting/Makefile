CXX      ?= g++
CXXFLAGS ?= -O2 -Wall
TARGET   := iluminacion

ifeq ($(shell uname),Darwin)
LDLIBS := -framework GLUT -framework OpenGL
else
LDLIBS := -lglut -lGLU -lGL
endif

all: $(TARGET)

$(TARGET): main.cpp Camara.h Light.h primitivas.h Vector_tools.h
	$(CXX) $(CXXFLAGS) -o $@ main.cpp $(LDLIBS)

# -ftrivial-auto-var-init=pattern fills uninitialised locals with a non-zero
# pattern, so a forgotten `ierr = 0` fails the tests instead of passing by luck.
tests/unit_tests: tests/unit_tests.cc Light.h Vector_tools.h
	$(CXX) -std=c++17 -g -O1 -ftrivial-auto-var-init=pattern -fsanitize=address,undefined -o $@ $< $(LDLIBS)

# The smoke run always uses a private virtual display (xvfb-run -a), never the
# caller's DISPLAY, so no window ever opens on a real desktop.
# `timeout` exiting 124 means the window was still open after 5 s: a pass.
test: tests/unit_tests $(TARGET)
	tests/unit_tests
	@env -u DISPLAY -u WAYLAND_DISPLAY xvfb-run -a timeout 5 ./$(TARGET) > /dev/null; rc=$$?; \
	if [ $$rc -eq 124 ]; then echo "ok   $(TARGET) ran for 5 s"; else echo "FAIL $(TARGET) exited with $$rc"; exit 1; fi

clean:
	rm -f $(TARGET) tests/unit_tests

.PHONY: all clean test
