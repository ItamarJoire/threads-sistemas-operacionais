TARGET=sudoku
CC=gcc
WARN=-Wall
VERSION=-std=c99
PTHREAD=-lpthread
CCFLAGS= $(WARN) $(VERSION) 
OBJS= sudoku.o

all: clean $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(PTHREAD)
 
sudoku.o:
	$(CC) -c sudoku.c $(CCFLAGS) -o sudoku.o
 
clean:
	rm -f *.o sudoku