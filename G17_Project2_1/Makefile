cc = gcc
cflags = -Wall -Werror -O2 -g

all : clean psh

clean : 
	rm psh.o psh

psh.o : psh.c
	$(cc) -c psh.c

psh: psh.o
	$(cc) $(cflags) psh.o -o psh

