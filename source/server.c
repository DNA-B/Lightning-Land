#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "data_init.h"
#include "sem.h"

#define SOCKET_NAME "trade"

int exit_cnt = 0, item_idx, semid;
char buf[BUFSIZ];

void send_msg(int nsd, char* msg) {	
	strcpy(buf, msg);
	
	if(send(nsd, buf, strlen(buf) + 1, 0) == -1) {
		perror("send");
		exit(1);
	}
	
	sleep(1);
}

void receive_msg(int nsd) {
	if(recv(nsd, buf, sizeof(buf), 0) == -1) {
		perror("recv");
		exit(1);
	}
}

void select_item(int nsd) {
	send_msg(nsd, "번개나라에 오신 것을 환영합니다.");
	send_msg(nsd, "구매하실 물건을 선택해주세요.");
	send_msg(nsd, "[ 0.카메라 | 1.자켓 | 2.이어폰 | 3.안경 | 4.책 | 5.가방 | 6.머리끈 ]");
	send_msg(nsd, "1"); // 1번은 입력 받기
	receive_msg(nsd); // client 선택 받기
	
	item_idx = atoi(buf); // 물건 번호 저장
	printf("사용자가 %s번을 선택하였습니다.\n", buf);
}

int re_trade(int nsd) {
	send_msg(nsd, "해당 물건이 이미 판매되었습니다.\n다른 물건을 선택하시겠습니까? [Y/N]");
	send_msg(nsd, "1");
	receive_msg(nsd);
	sleep(0.5);
	
	if(strcmp(buf, "y") == 0 || strcmp(buf, "Y")) {
		select_item(nsd);
		return 1;
	}
	else if(strcmp(buf, "n") == 0 || strcmp(buf, "N")) {
		send_msg(nsd, "프로그램을 종료합니다. 이용해주셔서 감사합니다.\n");
		send_msg(nsd, "2"); // 2번은 프로그램 종료
		return 0;
	}
}


int main() 
{
	struct Data* item = data_init();
	struct sockaddr_un ser, cli;
	int sd, nsd, len, clen, item_idx;

	printf("** Data Init Complete **\n");
	 
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
		if(exit_cnt == 10) // all item selled
			break;
		
		if ((nsd = accept(sd, (struct sockaddr *)&cli, &clen)) == -1) {
			perror("accept");
			exit(1);
		}
	
	
		/* 세마포어 초기화 (일단 사용 X)
  		if((semid = initsem(1)) < 0)
			exit(1);
		*/
		
		select_item(nsd);
		
		switch (fork()) {
			case 0:	
				if(item[item_idx].cur_ppid == -1) { // 거래 중이지 않고, 팔리지도 않았음
					item[item_idx].cur_ppid = getpid(); // ppid 변수를 현재 거래를 시작한 자식 프로세스의 pid로 갱신
					item[item_idx].is_trading = 1; // 거래중 여부 변수를 true(1)로 갱신
					// trade();
				}	
				else if(item[item_idx].is_selled) {
					exit(1);
				}
				else if(item[item_idx].is_trading) {
					wait(&item[item_idx].cur_ppid);
					
					if(item[item_idx].is_selled) { // 만약 팔렸다면 아이템 다시 선택 or 프로그램 종료
						re_trade(nsd) ? item_idx = atoi(buf) : exit(1);
					}
					else {
						item[item_idx].is_trading = 1; // 거래중 여부 변수를 true(1)로 갱신
						// trade();
					}
				}

				break;
		}
	}
	
	close(nsd);
}
