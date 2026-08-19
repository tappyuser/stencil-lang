CC=clang
CPP=g++

DEBUG=gdb

SRCDIR=src
OBJDIR=obj
BINDIR=bin
TESTDIR=test

INCLUDE=-Iinclude
# LIB=-Llib
LIB=-Llib -lcollectc

CFLAGS=-g -Wall --std=c23 $(INCLUDE) $(LIB)
CPPFLAGS=-g -Wall --std=c++26 $(INCLUDE) $(LIB)

MAIN=$(BINDIR)/main

ARGS="examples/test.stl"

$(MAIN): $(OBJDIR)/main.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

run: $(MAIN)
	./$^ $(ARGS)

debug: $(MAIN)
	$(DEBUG) --args ./$^ $(ARGS)

clean:
	rm -rf obj/* bin/*
