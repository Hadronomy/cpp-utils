CXX = g++
VERSION = 14
CXXFLAGS = -std=c++$(VERSION) -Wall -g
INCLUDEDIR = src
OUTDIR = bin
OBJDIR = obj
CPPFLAGS = -I./includes/utils -I./src
DEPS = $(addsuffix .o, $(basename $(shell find $(INCLUDEDIR) -type f -name '*.cc')))
TARGETS = $(basename $(notdir $(wildcard test/*.cc)))

default_target: lib

lib: libutils.a

libutils.a: $(DEPS)
	ar rcs $@ $^

.PHONY: clean

clean :
	rm -fr bin
	find . -name *.o -type f -delete
	mkdir bin
