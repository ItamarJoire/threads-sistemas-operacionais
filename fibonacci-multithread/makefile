TARGET=fibonacci
CC=gcc
WARN=-Wall
VERSION=-std=c99
PTHREAD=-lpthread
CCFLAGS= $(WARN) $(VERSION) 
OBJS= fibonacci.o

all: clean $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(PTHREAD)
 
fibonacci.o:
	$(CC) -c fibonacci.c $(CCFLAGS) -o fibonacci.o
 
clean:
	rm -f *.o fibonacci