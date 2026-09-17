CC := clang
CFLAGS := -Wall -g --std=c23

include Makefile.in

override SRCDIR := src
override OBJDIR := obj
override TESTDIR := test
override INCLUDEDIR := include
override BINDIR := bin
override LIBDIR := .

SRCS := $(notdir $(wildcard $(SRCDIR)/*.c))
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))


INCLUDE := -I$(INCLUDEDIR)
CFLAGS += $(INCLUDE)


ifeq ($(DETECTED_OS),Windows)
LIB := libstringutil.lib
else ifneq ($(DETECTED_OS),Unknown)
LIB := libstringutil.a
endif

.PHONY: all
all: $(LIB)

$(LIB): $(OBJS)
	@echo Creating the static library $@
	ar rcs $(LIB) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo Compiling the $@ from $^
	$(CC) $(CFLAGS) -c $^ -o $@

clean: 
	rm -f $(OBJS) $(LIB)

# Test 
TESTSRCS := $(wildcard $(TESTDIR)/*.c)
TESTOBJS := $(patsubst %.c,%.o,$(TESTSRCS))
TEST := $(TESTDIR)/test

test: $(LIB) $(TESTOBJS)
	$(CC) $(CFLAGS) -o $(TEST) $(TESTOBJS) -L$(LIBDIR) -l$(subst lib,,$(basename $(LIB)))
	./$(TEST)

clean-test:
	rm -f $(TEST) $(TESTOBJS)

clean-all: clean clean-test
