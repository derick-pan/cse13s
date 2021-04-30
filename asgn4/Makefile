CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -Werror -Wnewline-eof

all: tsp 

format: 
	clang-format -i -style=file *.c *.h

tsp: tsp.o 
	$(CC) -o tsp tsp.o graph.o stack.o path.o 

tsp.o: 
	$(CC) $(CFLAGS) -c graph.c stack.c path.c tsp.c

clean:
	rm -f tsp tsp.o graph.o stack.o path.o 

scan-build: clean
	scan-build make
