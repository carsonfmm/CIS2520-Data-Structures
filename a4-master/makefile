CC = gcc
CFLAGS = -std=c99 -Wall -pedantic


make all: ttest tree.o

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c -o tree.o

ttest.o: ttest.c
	$(CC) $(CFLAGS) -c ttest.c -o ttest.o

ttest: ttest.o tree.o
	$(CC) $(CFLAGS) -o ttest ttest.o tree.o

clean:
	rm ttest *.o


