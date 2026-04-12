CC = gcc
CFLAGS = -Wall -g

# add more utilites here

TARGETS = bin/shell bin/sh_rm bin/sh_help bin/sh_cat bin/sh_grep

all: $(TARGETS)

bin/%: src/%.c
	@mkdir -p bin
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf bin/*