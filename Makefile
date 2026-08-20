CC=clang
CPP=g++

DEBUG=gdb

SRCDIR=src
OBJDIR=obj
BINDIR=bin
TESTDIR=test
INCLUDEDIR=include

INCLUDE=-I$(INCLUDEDIR)
# LIB=-Llib
LIB=-Llib

CFLAGS=-g -Wall --std=c23 $(INCLUDE) $(LIB)
CPPFLAGS=-g -Wall --std=c++26 $(INCLUDE) $(LIB)

MAIN=$(BINDIR)/main

ARGS="examples/test.stl"

$(MAIN): $(OBJDIR)/main.o $(OBJDIR)/string_util.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o $@ -c $^

$(OBJDIR)/string_util.o: $(INCLUDEDIR)/src/string_util.c
	$(CC) $(CFLAGS) -o $@ -c $^

run: $(MAIN)
	./$^ $(ARGS)

debug: $(MAIN)
	$(DEBUG) --args ./$^ $(ARGS)

clean:
	rm -rf obj/* bin/*
