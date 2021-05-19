CC = clang
CFLAGS = -Wall -Wextra -g -Werror -Wpedantic -Werror

all: encode decode entropy

format:
	clang-format -i -style=file *.c *.h

decode: decode.o
	$(CC) -o decode decode.o node.o pq.o stack.o code.o io.o huffman.o
decode.o:
	$(CC) $(CFLAGS) -c decode.c node.c pq.c stack.c code.c io.c huffman.c

encode: encode.o
	$(CC) -o encode encode.o node.o pq.o stack.o code.o io.o huffman.o
encode.o:
	$(CC) $(CFLAGS) -c encode.c node.c pq.c stack.c code.c io.c huffman.c

entropy: entropy.o
	$(CC) -o entropy entropy.o node.o pq.o stack.o code.o io.o huffman.o -lm
entropy.o:
	$(CC) $(CFLAGS) -c entropy.c node.c pq.c stack.c code.c io.c huffman.c

clean:
	rm -f encode encode.o decode decode.o entropy entropy.o node.o pq.o stack.o code.o io.o huffman.o

scan-build: clean
	scan-build make
