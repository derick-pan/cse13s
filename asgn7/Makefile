CC = clang
CFLAGS = -Wall -Wextra -g -Werror -Wpedantic

all: banhammer

format:
	clang-format -i -style=file *.c *.h

banhammer: banhammer.o
	$(CC) -o banhammer banhammer.o bf.o bv.o ht.o ll.o parser.o node.o speck.o
banhammer.o:
	$(CC) $(CFLAGS) -c banhammer.c bf.c bv.c ht.c ll.c parser.c node.c speck.c

clean:
	rm -f banhammer banhammer.o bf.o bv.o ht.o ll.o parser.o node.o speck.o

scan-build: clean
	scan-build make
