# Makefile for the UBHeap assignment

OBJS = term_control.o error_handling.o UBHeap.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic -ansi $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ubheap

main.o: main.cpp error_handling.h UBHeap.h term_control.h
	$(CC) -c $(CFLAGS) main.cpp

# UBHeap makes use of error handling routines
UBHeap.o: error_handling.o UBHeap.h UBHeap.cpp
	$(CC) -c $(CFLAGS) UBHeap.cpp

# error handling routines make use of terminal control routines
error_handling.o : term_control.o error_handling.h error_handling.cpp
	$(CC) -c $(CFLAGS) error_handling.cpp

# this object file is at the "lowest level"
term_control.o : term_control.h term_control.cpp
	$(CC) -c $(CFLAGS) term_control.cpp

clean:
	rm -f *.o a.out ubheap
