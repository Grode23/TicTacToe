CC=gcc
CFLAGS=-I.
 
server: server.c game.c
	$(CC) -o server server.c game.c $(CFLAGS)

client: client.c
	$(CC) -o client client.c
	
clean: server client 
	rm server client
