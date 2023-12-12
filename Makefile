server: server.o data_init.o
	gcc -o server server.o data_init.o
	
client: client.o
	gcc -o client client.o

data_init.o: data_init.c
	gcc -c data_init.c
	
server.o: server.c
	gcc -c server.c 
	
client.o: client.c
	gcc -c client.c

all: server client

clean:
	rm -f *.o | ipcrm --all=shm
