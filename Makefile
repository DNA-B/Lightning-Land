data_init.o: data_init.c
	gcc -c data_init.c

ready.o : ready.c 
	gcc -c ready.c
	
server.o: server.c
	gcc -c server.c 
	
client.o: client.c
	gcc -c client.c

server: server.o ready.o
	gcc -o server server.o ready.o data_init.o
	
client: client.o
	gcc -o client client.o
	
# sem.o: sem.c
#	gcc -c sem.c

all: server client

clean:
	rm -f *.o
