CC=gcc
CFLAGS=-Wall

all: client server
client: client.c utils.c
	$(CC) $(CFLAGS) -o client client.c utils.c
server: server.c utils.c
	$(CC) $(CFLAGS) -o server server.c utils.c

clean:
	rm -f *.o client server
