# Creates libraries in each directory and places it in this current directory
CC := clang
CFLAGS := -Wall -g

DIRS := string_util

.PHONY: $(DIRS) all clean
all: $(DIRS)

$(DIRS):
	$(MAKE) -C $@
	cp $@/*.a .


clean:
	rm -f *.a
