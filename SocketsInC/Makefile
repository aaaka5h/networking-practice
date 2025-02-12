CFLAGS = -g 

all:	client server

client:	client.o
	gcc $(CFLAGS) -o client client.o

server:	server.o
	gcc $(CFLAGS) -o server server.o

clean:
	rm -f *.o client server *~
