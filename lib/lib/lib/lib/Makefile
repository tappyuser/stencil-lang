# Creates libraries in each directory and places it in this current directory
include Makefile.in
CC := clang
CFLAGS := -Wall -g

DIRS := string_util


.PHONY: $(DIRS) all clean
all: $(DIRS)

ifeq ($(DETECTED_OS),Windows)
override LIBS := $(shell where /r *.lib 2> nul)
endif 
ifneq ($(DETECTED_OS),Unknown)
override LIBS := $(shell find . -name *.a 2> /dev/null)
k = 2
endif

$(DIRS): $(LIBS)
	$(MAKE) -C $@
	@echo $(DETECTED_OS)
	cp $(LIBS) ./

clean:
	rm -f $(LIBS)
