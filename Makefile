# Makefile for Game

UNAME := $(shell uname)
LIBDIR = lib
LIBBASENAME = game

ifeq ($(UNAME), Darwin)
# OS X
OSFLAGS = -L$(LIBDIR) -framework GLUT -framework OpenGL
LIBNAME = $(LIBBASENAME).dylib
else
# Linux
OSFLAGS = -lglut -lGLU -lGL
LIBNAME = $(LIBBASENAME).so
endif

LIBFILE = $(LIBDIR)/$(LIBNAME)
GPPFLAGS = -O2 -Wall -pedantic -ansi
COMPILE = g++ $(GPPFLAGS) $(OSFLAGS)
HEADERS = Game.h Input.h GUI.h
SOURCES = Game.cc Input.cc GUI.cc
EXECUTABLE = game

default: *.h *.cc
	@make $(LIBFILE)
	@echo ""
	@echo "Symlinking lib file ..."
	ln -sf $(LIBFILE) $(LIBNAME)
	@echo ""
	@echo "Building game executable ..."
	$(COMPILE) \
	$(SOURCES) \
	$(LIBFILE) \
	-o $(EXECUTABLE)
	@echo ""
	@echo "Built."
	@echo ""

$(LIBFILE): $(LIBDIR)/*.h $(LIBDIR)/*.cc
	@echo "Building lib file ..."
	@cd $(LIBDIR); make

clean:
	@echo "Cleaning lib directory ..."
	cd $(LIBDIR); make clean
	@echo ""
	@echo "Cleaning game directory ..."
	$(RM) $(LIBNAME) $(EXECUTABLE) core
	@echo ""
	@echo "Squeaky."
	@echo ""

new:
	make clean
	make
