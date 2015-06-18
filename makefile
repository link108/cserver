all: client server
client: client.c
	gcc client.c
server: server.c
	gcc server.c
