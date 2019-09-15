CC=gcc
CFLAGS=-I.
 
server: server.c game.c game.h communication.c communication.h
	$(CC) -o server server.c game.c communication.c $(CFLAGS)

client: client.c game.c game.h communication.c communication.h
	$(CC) -o client client.c game.c communication.c $(CFLAGS)

clean: server client 
	rm server client
