#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SOCKET_NAME "trade"

char buf[BUFSIZ];

void send_msg(int sd, char* msg) {		
	strcpy(buf, msg);
	if(send(sd, buf, strlen(buf) + 1, 0) == -1) {
		perror("send");
		exit(1);
	}	
}

int receive_msg(int sd) {
	if(recv(sd, buf, sizeof(buf), 0) == -1) {
		perror("recv");
		exit(1);
	}
}

int main() {
	int sd, len;
	struct sockaddr_un ser;

	if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	
	memset((char *)&ser, '\0', sizeof(ser));
	ser.sun_family = AF_UNIX;
	strcpy(ser.sun_path, SOCKET_NAME);
	len = sizeof(ser.sun_family) + strlen(ser.sun_path);

	if (connect(sd, (struct sockaddr *)&ser, len) < 0) { 
		perror("bind");
		exit(1);
	}
	
	while(1) {
		receive_msg(sd);
		
		if(strcmp(buf, "1") == 0) {
			printf(">> Select item : ");
			scanf("%s", buf);
			send_msg(sd, buf);
		}
		else if(strcmp(buf, "2") == 0) {
			break;
		}
		else {
			printf("%s", buf);
		}
	}
	
	close(sd);
}
