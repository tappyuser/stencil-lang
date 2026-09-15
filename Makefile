CC := gcc
CPP := g++

DEBUG := gdb

SRCDIR := src
OBJDIR := obj
BINDIR := bin
TESTDIR := test
INCLUDEDIR := include
LIBDIR := lib

INCLUDE := -I$(INCLUDEDIR)
LIB = -l$(patsubst lib%.a,%,$(LIBS))

DEPS := $(LIBDIR)

CFLAGS := -g -Wall --std=c23 $(INCLUDE) 
CPPFLAGS := -g -Wall --std=c++26 $(INCLUDE)

MAIN := $(BINDIR)/main
SRCS := $(notdir $(wildcard $(SRCDIR)/*.c))
OBJS := $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))
LIBS = $(notdir $(wildcard $(LIBDIR)/*.a))

ARGS := "examples/test.stl"

.PHONY: all

all: $(MAIN)
$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBDIR) $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

run: $(MAIN)
	./$^ $(ARGS)

debug: $(MAIN)
	$(DEBUG) --args ./$^ $(ARGS)

lib:
	$(MAKE) -C $@

clean:
	rm -rf obj/* bin/*
