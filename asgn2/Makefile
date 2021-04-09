CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: mathlib 

mathlib: mathlib.o 
	$(CC) -o mathlib mathlib.o mathlib-test.o 

mathlib.o: 
	$(CC) $(CFLAGS) -c mathlib.c mathlib-test.c

clean:
	rm -f mathlib mathlib.o mathlib-test.o

scan-build: clean
	scan-build make
