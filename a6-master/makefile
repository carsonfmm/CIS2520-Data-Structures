CC = gcc
CFLAGS = -std=c99 -Wall -pedantic


make all: buildidx key2val val2key actors

buildidx.o: buildidx.c
	$(CC) $(CFLAGS) -c buildidx.c -o buildidx.o

buildidx: buildidx.o
	$(CC) $(CFLAGS) -o buildidx buildidx.o

key2val.o: key2val.c
	$(CC) $(CFLAGS) -c key2val.c -o key2val.o

key2val: key2val.o
	$(CC) $(CFLAGS) -o key2val key2val.o

val2key.o: val2key.c
	$(CC) $(CFLAGS) -c val2key.c -o val2key.o

val2key: val2key.o
	$(CC) $(CFLAGS) -o val2key val2key.o

actors.o: actors.c
	$(CC) $(CFLAGS) -c actors.c -o actors.o

actors: actors.o
	$(CC) $(CFLAGS) -o actors actors.o

clean:
	rm buildidx key2val val2key actors *.o
