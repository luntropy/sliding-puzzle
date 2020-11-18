CC = g++
CFLAGS = -Wall -g -O3

main: main.o Board.o Node.o
	$(CC) $(CFLAGS) -o main main.o Board.o Node.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Board.o: Board.cpp
	$(CC) $(CFLAGS) -c Board.cpp

Node.o: Board.cpp Node.cpp
	$(CC) $(CFLAGS) -c Board.cpp Node.cpp

clean:
	rm -f core *.o
