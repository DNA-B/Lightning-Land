#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data_init.h"
#include "sem.h"

#define SOCKET_NAME "trade"

int main() 
{
	struct sockaddr_un ser, cli;
	int sd, nsd, len, clen, semid;
	char buf[BUFSIZ];
	struct Data* item = data_init();

	printf("** Data Init Complete **\n");
	
	unlink(SOCKET_NAME); // 서버 재실행시 오류를 방지하기 위해 만들어둔 소켓 삭제	
		
	if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
 	}

 	printf("** Create Socket ** \n");

	memset((char *)&ser, '\0', sizeof(struct sockaddr_un));
	ser.sun_family = AF_UNIX;
	strcpy(ser.sun_path, SOCKET_NAME);
	len = sizeof(ser.sun_family) + strlen(ser.sun_path);

	if (bind(sd, (struct sockaddr *)&ser, len)) {
 		perror("bind");
		 exit(1);
	}
	
	if (listen(sd, 10) < 0) {
		perror("listen");
		exit(1);
	}

	while (1) {
		if ((nsd = accept(sd, (struct sockaddr *)&cli, &clen)) == -1) {
			perror("accept");
			exit(1);
		}
	
	
		if((semid = initsem(1)) < 0)
			exit(1);
			
		semlock(semid);
		strcpy(buf, "번개나라에 오신 것을 환영합니다.\n구매하실 물건을 선택해주세요.\n");
		if(send(nsd, buf, strlen(buf) + 1, 0) == -1) {
			perror("send");
			exit(1);
		}
		semunlock(semid);	
		
		if(recv(nsd, buf, sizeof(buf), 0) == -1) {
			perror("recv");
			exit(1);
		}
		
		printf("Cient's selection : %s\n", buf);
		return 0;
		
		switch (fork()) {
			case 0:
				/*
		
				if( it[item].is_selled )
					exit(1)
				else if( it[item].is_trading ) {
					wait(it[item].cur_ppid);
					
					if(it[item].is_selled)
						exit(1);
					else
						trade();
				}
				else {
					trade();
				}
		
				*/
				break;
		}
	}
	
	close(nsd);
}
