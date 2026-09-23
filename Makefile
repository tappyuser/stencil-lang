CC := clang

# Include for platform detection
include Makefile.in

ifeq ($(DETECTED_OS),Windows)
DEBUGGER := 
else 
DEBUGGER := gdb
endif

DEBUG := true # Set to false for release build and false for debug build

override SRCDIR := src
override OBJDIR := obj
override BINDIR := bin
override TESTDIR := test
override INCLUDEDIR := include
override LIBDIR := lib

override INCLUDE := -I$(INCLUDEDIR)

ifeq ($(DETECTED_OS), Windows)
LIBS := $(notdir $(patsubst %.lib,%,$(shell getlibs)))
override LIB := $(foreach lib,$(LIBS),-l$(lib))
else
override LIB = -l$(patsubst lib%.a,%,$(LIBS))
endif

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
ifeq ($(strip $(DEBUG)),true) 
CFLAGS := -g -O0 -D_STNL_DEBUG_ $(CFLAGS)
else  
CFLAGS := -O3 $(CFLAGS)
endif

all: build

run: build
	./$(TARGET) $(ARGS)

build: $(TARGET)

clean:
	rm -rf obj/* bin/*

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBDIR) $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@



debug: $(TARGET)
	$(DEBUGGER) --args ./$^ $(ARGS)


