CC := clang
CFLAGS := -Wall -g --std=c23

SRCDIR := src
OBJDIR := obj
INCLUDEDIR := include

SRCS := $(notdir $(wildcard $(SRCDIR)/*.c))
OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

INCLUDE := -I$(INCLUDEDIR)

LIB := libstringutil.a

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
	rm $(LIB)


