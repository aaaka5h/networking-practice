CC=gcc
CFLAGS=-g -Wall -std=gnu11 -I/opt/homebrew/include

all: main

main: compute.o main.o
	gcc $(CFLAGS) -o main compute.o main.o

main.o: compute.h
compute.o: compute.h

clean:
	rm compute.o main.o main