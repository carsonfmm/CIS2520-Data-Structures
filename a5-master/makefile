CC = gcc
CFLAGS = -std=c99 -Wall -pedantic


make all: htest1 htest2 htest3 htest4 hash.o

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c -o hash.o

htest1.o: htest1.c
	$(CC) $(CFLAGS) -c htest1.c -o htest1.o

htest1: htest1.o hash.o
	$(CC) $(CFLAGS) -o htest1 htest1.o hash.o

htest2.o: htest2.c
	$(CC) $(CFLAGS) -c htest2.c -o htest2.o

htest2: htest2.o hash.o
	$(CC) $(CFLAGS) -o htest2 htest2.o hash.o

htest3.o: htest3.c
	$(CC) $(CFLAGS) -c htest3.c -o htest3.o

htest3: htest3.o hash.o
	$(CC) $(CFLAGS) -o htest3 htest3.o hash.o

htest4.o: htest4.c
	$(CC) $(CFLAGS) -c htest4.c -o htest4.o

htest4: htest4.o hash.o
	$(CC) $(CFLAGS) -o htest4 htest4.o hash.o

clean:
	rm htest1 htest2 htest3 htest4 *.o
