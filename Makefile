CFLAGS=-g -Wall -Wextra
CC=gcc

all: hexdump

hexdump: hexdump.c main.c
	$(CC) $(CFLAGS) main.c hexdump.c -o hexdump
    
clean:
	rm -f hexdump