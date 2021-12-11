CXX = g++
VERSION = 14
CXXFLAGS = -std=c++$(VERSION) -Wall -g
INCLUDEDIR = src
OUTDIR = bin
CPPFLAGS = -I./includes -I./src
DEPS = $(shell find $(INCLUDEDIR) -type f -name '*.cc')
TARGETS = $(basename $(notdir $(wildcard test/*.cc)))

default_target: all

all: clean $(TARGETS)

%: test/%.o $(DEPS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(USER_DEFINES) -o $(OUTDIR)/$@ $^ $(CPPFLAGS)

.PHONY: all clean tar

clean :
	rm -fr bin
	mkdir bin
