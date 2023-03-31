CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

make all: ttt2.o ttt1.o show_node count_nodes alphatoe

ttt1.o: ttt1.c ttt.h
	$(CC) $(CFLAGS) -c ttt1.c -o ttt1.o

ttt2.o: ttt2.c ttt.h
	$(CC) $(CFLAGS) -c ttt2.c -o ttt2.o

show_node: show_node.o ttt1.o ttt2.o
	$(CC) $(CFLAGS) -o show_node show_node.o ttt1.o ttt2.o

count_nodes: count_nodes.o ttt1.o ttt2.o
	$(CC) $(CFLAGS) -o count_nodes count_nodes.o ttt1.o ttt2.o

alphatoe: alphatoe.c ttt2.o ttt1.o ttt.h
	$(CC) $(CFLAGS) alphatoe.c ttt2.o ttt1.o -o alphatoe

clean:
	rm show_node count_nodes alphatoe *.o
