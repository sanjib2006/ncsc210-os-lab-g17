CC = gcc
CFLAGS = -Wall -g

# add more utilites here
TARGETS = bin/shell 

all: $(TARGETS)

bin/%: src/%.c
	@mkdir -p bin
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f bin/*