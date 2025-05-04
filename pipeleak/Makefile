# Makefile for pipeleak project

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = pipeleak

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)
