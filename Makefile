CC=gcc
CFLAGS=-Wall -Wextra -g

all: hello

hello: hello.c
	$(CC) $(CFLAGS) hello.c -o hello

clean:
	rm -f hello

