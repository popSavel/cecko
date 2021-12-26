CC = gcc

CFLAGS = -Wall -Wextra -pedantic -ansi -g -std=c99
LDFLAGS = $(CFLAGS) -lm

BUILD_DIR = build
BIN = semestralka.exe

clean: $(BUILD_DIR) $(BUILD_DIR)/$(BIN)

$(BUILD_DIR)/$(BIN): $(BUILD_DIR)/main.o $(BUILD_DIR)/pgm.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/main.o: main.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/pgm.o: pgm.c pgm.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR):
	mkdir $@

