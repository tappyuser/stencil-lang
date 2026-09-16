CC := clang

# Include for platform detection
include Makefile.in

ifeq ($(DETECTED_OS),Windows)
DEBUGGER := 
else 
DEBUGGER := gdb
endif

DEBUG := 1 # Set to 0 for release build and 1 for debug build

override SRCDIR := src
override OBJDIR := obj
override BINDIR := bin
override TESTDIR := test
override INCLUDEDIR := include
override LIBDIR := lib

override INCLUDE := -I$(INCLUDEDIR)
override LIB = -l$(patsubst lib%.a,%,$(LIBS))

DEPS := $(LIBDIR)

CFLAGS := -Wall --std=c23 $(INCLUDE) 

TARGET := $(BINDIR)/main
SRCS := $(notdir $(wildcard $(SRCDIR)/*.c))
OBJS := $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))
LIBS = $(notdir $(wildcard $(LIBDIR)/*.a))

# Command line arguments to pass to the TARGET
ARGS := "examples/test.stl"

.PHONY: all build debug

# Checking to enable the debug build
ifeq ($(strip $(DEBUG)),1) 
CFLAGS := -g -O0 $(CFLAGS)
else  
CFLAGS := -O3 $(CFLAGS)
endif

all: build

build: $(TARGET)

clean:
	rm -rf obj/* bin/*

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBDIR) $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

run: $(TARGET)
	./$^ $(ARGS)

debug: $(TARGET)
	$(DEBUGGER) --args ./$^ $(ARGS)


