server: server.o data_init.o sem.o
	gcc -o server server.o data_init.o sem.o

client: client.o
	gcc -o client client.o
	
sem.o: sem.c
	gcc -c sem.c
	
data_init.o: data_init.c
	gcc -c data_init.c
	
server.o: server.c
	gcc -c server.c 
	
