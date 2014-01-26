CC=gcc
CFLAGS=-c -Wall

all: build

build: des.o testDES.c
	gcc testDES.c DES.o -o testDES

testDES.o: testDES.c
	$(CC) $(CFLAGS) testDES.c -o testDES.o

des.o: des.c
	$(CC) $(CFLAGS) DES.c -o DES.o

clean:
	rm *.o