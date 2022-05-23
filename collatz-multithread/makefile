TARGET=collatz
CC=gcc
WARN=-Wall
VERSION=-std=c99
PTHREAD=-lpthread
CCFLAGS= $(WARN) $(VERSION) 
OBJS= collatz.o

all: clean $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(PTHREAD)
 
collatz.o:
	$(CC) -c collatz.c $(CCFLAGS) -o collatz.o
 
clean:
	rm -f *.o collatz