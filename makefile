c=gcc
op=-Wall -Wextra

all : huffman.o elt.o main.c  	
	$(c) $(op)   elt.o huffman.o main.c -o huffman	
include/huffman.o : include/huffman.c include/huffman.h
	$(c) $(op) -c include/huffman.c	
include/elt.o : include/elt.c include/elt.h	
	$(c) $(op) -c include/elt.c

