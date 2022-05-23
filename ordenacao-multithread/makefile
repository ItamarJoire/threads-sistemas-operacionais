TARGET=ordenacao
CC=gcc
WARN=-Wall
VERSION=-std=c99
PTHREAD=-lpthread
CCFLAGS= $(WARN) $(VERSION) 
OBJS= ordenacao.o

all: clean $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(PTHREAD)
 
ordenacao.o:
	$(CC) -c ordenacao.c $(CCFLAGS) -o ordenacao.o
 
clean:
	rm -f *.o ordenacao