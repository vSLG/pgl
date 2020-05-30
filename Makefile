PHONY := __all
__all:

MAKEFLAGS := --no-print-directory

srctree := .
objtree := obj
bintree := bin

export srctree objtree bintree

include scripts/Makefile.include.sub

SHELL = sh
CC = gcc
CXX = g++
AR = ar

INCLUDE_DIR   := -I$(srctree)/include
BUILD_CFLAGS  := -Wall -Wundef -O2 $(CFLAGS)
BUILD_CXXFLAGS := -g -Wall -O2 -std=c++17 $(CXXFLAGS)

export BUILD_CFLAGS BUILD_CXXFLAGS INCLUDE_DIR SHELL CC AR

link_libraries := -lSDL2 -lGL -ldl
build-dirs     := src


PHONY += $(build-dirs)
$(build-dirs):
	@$(MAKE) $(build)=$@

__all: build
	
PHONY += build run clean

build: $(build-dirs)
	$(shell mkdir -p $(bintree))
	$(CXX) $(link_libraries) -o $(bintree)/main $(objtree)/src/built-in.a

run: __all
	@$(bintree)/main

clean:
	-rm -rf $(objtree)
	-rm -rf $(bintree)

.PHONY: $(PHONY)