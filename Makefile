CXX = g++
VERSION = 14
CXXFLAGS = -std=c++$(VERSION) -Wall -g
INCLUDEDIR = lib
OUTDIR = bin
CPPFLAGS = -I.
DEPS = $(shell find $(INCLUDEDIR) -type f -name '*.cc')
TARGETS = $(basename $(notdir $(wildcard src/*.cc)))

default_target: all

all: clean $(TARGETS)

%: src/%.cc $(DEPS)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(USER_DEFINES) -o $(OUTDIR)/$@ $^ $(CPPFLAGS)

.PHONY: all clean tar

clean :
	rm -fr bin
	mkdir bin

tar:
	tar cvfz p09_Pablo_HenándezJiménez.tar.gz --exclude-from=.gitignore *