CC=gcc
CFLAGS=-c -Wall -g

all: build

build: des.o testDES.c
	gcc testDES.c DES.o -o testDES

testDES.o: testDES.c
	$(CC) $(CFLAGS) testDES.c -o testDES.o

des.o: des.c
	$(CC) $(CFLAGS) DES.c -o DES.o
	
testKeyScheduling.o: testKeyScheduling.c
	$(CC) $(CFLAGS) testKeyScheduling.c -o testKeyScheduling.o

testkeys: des.o testKeyScheduling.c
	gcc testKeyScheduling.c DES.o -o testKeyScheduling
clean:
	rm *.o