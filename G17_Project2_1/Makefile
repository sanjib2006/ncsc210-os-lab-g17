CC = gcc
CFLAGS = -Wall -g

# add more utilites here
TARGETS = bin/shell bin/sh_rm bin/sh_help bin/sh_cat bin/sh_ls bin/sh_tail bin/sh_head bin/sh_wc bin/sh_grep


all: $(TARGETS) move

bin/%: src/%.c
	@mkdir -p bin
	$(CC) $(CFLAGS) $< -o $@

move:
	@mv ./bin/shell ./
clean:
	@rm -rf bin
	@rm shell
