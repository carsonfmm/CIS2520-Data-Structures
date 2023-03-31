CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

program: hello.o
	$(CC) $(CFLAGS) hello.o -o hello

hello.o:
	$(CC) $(CFLAGS) -c hello.c -o hello.o

run:
	./hello

clean:
	rm hello *.o
