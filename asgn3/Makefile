CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sorting 

format: 
	clang-format -i -style=file *.c *.h

sorting: sorting.o 
	$(CC) -o sorting sorting.o shell.o bubble.o quick.o stack.o queue.o

sorting.o: 
	$(CC) $(CFLAGS) -c bubble.c shell.c sorting.c quick.c stack.c queue.c

clean:
	rm -f sorting sorting.o bubble.o shell.o quick.o stack.o queue.o

scan-build: clean
	scan-build make
