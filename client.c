#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SOCKET_NAME "trade"

extern int initsem(key_t semkey);
extern int semlock(int semid);
extern int semunlock(int semid);

int main() {
	int sd, len, semid;
	char buf[BUFSIZ];
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


	if (recv(sd, buf, sizeof(buf), 0) == -1) {
		perror("recv");
		exit(1);
	}
	
	printf("%s", buf);
	
	if(strcmp(buf, "번개나라에 오신 것을 환영합니다.\n구매하실 물건을 선택해주세요.")) {
		printf("Select item : ");
		scanf("%s", buf);
	}
	
	if (send(sd, buf, sizeof(buf), 0) == -1) {
		perror("send");
		exit(1);
	}
	
	close(sd);
}


