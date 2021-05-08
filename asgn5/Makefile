CC = clang
CFLAGS = -Wall -Wextra -g -Werror -Wpedantic -Werror -Wnewline-eof

all: encode decode error entropy

format:
	clang-format -i -style=file *.c *.h

encode: encode.o
	$(CC) -o encode encode.o bm.o bv.o hamming.o
encode.o:
	$(CC) $(CFLAGS) -c bm.c bv.c hamming.c encode.c

decode: decode.o
	$(CC) -o decode decode.o bm.o bv.o hamming.o
decode.o:
	$(CC) $(CFLAGS) -c bm.c bv.c hamming.c decode.c

error: error.o
	$(CC) -o error error.o bm.o bv.o hamming.o
error.o:
	$(CC) $(CFLAGS) -c bm.c bv.c hamming.c error.c

entropy: entropy.o
	$(CC) -o entropy entropy.o bm.o bv.o hamming.o -lm
entropy.o:
	$(CC) $(CFLAGS) -c bm.c bv.c hamming.c entropy.c

clean:
	rm -f encode encode.o decode decode.o error error.o entropy entropy.o pain.o bm.o bv.o hamming.o
scan-build: clean
	scan-build make
