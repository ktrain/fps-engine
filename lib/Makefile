# Makefile for lib

UNAME := $(shell uname)
LIBNAME = game

ifeq ($(UNAME), Darwin)
# OS X
OSFLAGS = -framework GLUT -framework OpenGL
GPPFLAGS = -dynamiclib -O2 -Wall -pedantic -ansi
LIBFILE = $(LIBNAME).dylib
else
# Linux
OSFLAGS = -lglut -lGLU -lGL
GPPFLAGS = -shared -fPIC -O2 -Wall -pedantic -ansi
LIBFILE = $(LIBNAME).so
endif

COMPILE = g++ $(GPPFLAGS) $(OSFLAGS)
SOURCES = Timing.cc BasicMath.cc Vector.cc Matrix.cc Camera.cc SceneGraph.cc Light.cc Object.cc Player.cc

default: *.h *.cc
	$(COMPILE) \
	$(SOURCES) \
	-o $(LIBFILE)

clean:
	$(RM) $(LIBFILE) *.gch

