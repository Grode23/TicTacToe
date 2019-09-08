CC=gcc
CFLAGS=-I.
 
server: server.c game.c game.h
	$(CC) -o server server.c game.c $(CFLAGS)

client: client.c game.c game.h
	$(CC) -o client client.c game.c $(CFLAGS)

clean: server client 
	rm server client
