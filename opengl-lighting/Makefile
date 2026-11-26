CXX      ?= g++
CXXFLAGS ?= -O2 -Wall
TARGET   := iluminacion

ifeq ($(shell uname),Darwin)
LDLIBS := -framework GLUT -framework OpenGL
else
LDLIBS := -lglut -lGLU -lGL
endif

$(TARGET): main.cpp Camara.h Light.h primitivas.h Vector_tools.h
	$(CXX) $(CXXFLAGS) -o $@ main.cpp $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean
