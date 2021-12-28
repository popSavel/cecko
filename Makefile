CC = gcc

CFLAGS = -Wall -Wextra -pedantic -ansi -g -std=c99
LDFLAGS = $(CFLAGS) -lm

BIN = ccl.exe

clean: $(BIN)

$(BIN): $main.o $pgm.o
	$(CC) -o $@ $^ $(LDFLAGS)

$main.o: main.c
	$(CC) -c $(CFLAGS) -o $@ $<

$pgm.o: pgm.c pgm.h
	$(CC) -c $(CFLAGS) -o $@ $<


