EXEC = dijkstra
CC = g++
CFLAGS = -c -Wall

$(EXEC) :main.o util.o heap.o Graph.o stack.o
	$(CC) -o $(EXEC) main.o util.o heap.o Graph.o stack.o

main.o :main.cpp
	$(CC) $(CFLAGS) main.cpp

util.o :util.h util.cpp
	$(CC) $(CFLAGS) util.cpp

heap.o :heap.h heap.cpp
	$(CC) $(CFLAGS) heap.cpp

Graph.o :Graph.h Graph.cpp
	$(CC) $(CFLAGS) Graph.cpp

stack.o :stack.h stack.cpp
	$(CC) $(CFLAGS) stack.cpp

clean :
	rm *.o