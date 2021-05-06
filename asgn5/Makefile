CC = clang
CFLAGS = -Wall -Wextra -g -Werror -Wpedantic -Werror -Wnewline-eof

all: encode decode error entropy

format:
	clang-format -i -style=file *.c *.h

decode: decode.o
	$(CC) -o decode decode.o bm.o bv.o hamming.o
decode.o:
	$(CC) $(CFLAGS) -c bm.c bv.c test.c hamming.c decode.c

entropy: entropy.o
	$(CC) -o entropy entropy.o bm.o bv.o hamming.o -lm
entropy.o:
	$(CC) $(CFLAGS) -c bm.c bv.c test.c hamming.c entropy.c

error: error.o
	$(CC) -o error error.o bm.o bv.o hamming.o
error.o:
	$(CC) $(CFLAGS) -c bm.c bv.c test.c hamming.c error.c

encode: encode.o
	$(CC) -o encode encode.o bm.o bv.o hamming.o

encode.o:
	$(CC) $(CFLAGS) -c bm.c bv.c test.c hamming.c encode.c

clean:
	rm -f entropy entropy.o encode encode.o decode decode.o error error.o pain.o bm.o bv.o hamming.o

scan-build: clean
	scan-build make
