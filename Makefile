# ifndef CC
# 	CC=gcc
# endif
# CFLAGS=-std=c99 -Werror -Wall -Wpedantic -Wextra
# SRCS=bdsm.c
# OBJS=$(subst .c,.o,$(SRCS))
# RM=rm -f
#
# all: bdsm
#
# #foo: main.o
# #	$(CC) $(CFLAGS) -o main main.c
#
# clean:
# 	$(RM) $(OBJS) bdsm

CC = g++
CFLAGS = -Wall -g

main: main.o Board.o
	$(CC) $(CFLAGS) -o main main.o Board.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Board.o: Board.cpp
	$(CC) $(CFLAGS) -c Board.cpp

clean:
	rm -f core *.o
