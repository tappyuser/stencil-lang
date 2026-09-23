# Creates libraries in each directory and places it in this current directory
include ../Makefile.in
CC := clang
CFLAGS := -Wall -g

DIRS := string_util


.PHONY: $(DIRS) all clean
all: $(DIRS)

ifeq ($(DETECTED_OS),Windows)
LIBS := $(shell getlibs)
endif 
ifneq ($(DETECTED_OS),Unknown)
override LIBS := $(foreach dir,$(DIRS),$(shell find $(dir) -name *.a 2> /dev/null))
endif

$(DIRS): $(LIBS)
	$(MAKE) -C $@
	cp $(LIBS) .

clean:
	rm -f $(notdir $(LIBS))
