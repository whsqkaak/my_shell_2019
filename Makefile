CC=gcc
TARGETS =cat chmod echo ls mkdir mv my_shell pwd rm
all: $(TARGETS)
.PHONY: all
%:
	$(CC) -o $@ $@.c

clean:
	rm $(TARGETS)

