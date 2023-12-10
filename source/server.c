#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ready.h"

#define SOCKET_NAME "trade"

int main() 
{
	struct sockaddr_un ser, cli;
	int sd, nsd, len, clen, exit_cnt = 0;
	
	unlink(SOCKET_NAME); // 서버 재실행시 오류를 방지하기 위해 만들어둔 소켓 삭제	
		
	if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
 	}

 	printf("** Server Start - Create Socket ** \n");

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
		if(exit_cnt == 10) // trade에서is_selled가 1로 바뀔때마다 exit_cnt++ 해주면되요 exit_cnt도 메모리 매핑 필요해요
			break;
		
		if ((nsd = accept(sd, (struct sockaddr *)&cli, &clen)) == -1) {
			perror("accept");
			exit(1);
		}
		
		switch (fork()) { // accept 받고 거래는 자식 프로세스에서 처리
			case 0:	
				select_item(nsd); // 사용자 물건 입력 받기
				trade_or_exit(nsd); // 거래 or 대기 or 종료
				break;
		}
	}
	
	close(nsd);
}
