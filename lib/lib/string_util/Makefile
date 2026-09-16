CC := clang
CFLAGS := -Wall -g --std=c23

include Makefile.in

SRCDIR := src
OBJDIR := obj
INCLUDEDIR := include

SRCS := $(notdir $(wildcard $(SRCDIR)/*.c))
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

INCLUDE := -I$(INCLUDEDIR)

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
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

clean: 
	rm -f $(OBJS)


