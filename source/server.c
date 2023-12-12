#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data_init.h"

#define SOCKET_NAME "trade"
#define DELAY 1500000

void send_msg(int nsd, char* msg); // client에게 메세지 전송
void receive_msg(int nsd); // client의 입력 대기 
void select_item(int nsd); // client에게 아이템 선택 요청 
void trade_or_exit(int nsd); // 사용자가 물건을 선택하였을 때 거래를 시작할지, 말지 결정하는 함수
void wait_trade(int nsd); // 만약 다른 client가 거래중이라면 해당 함수에서 대기
int re_trade(int nsd); // 거래가 불가능할 때, 다시 선택할 것인지 client에게 물어보는 함수
void trade(int nsd); // 실제 거래가 이루어지는 함수


Data* item; // 판매 물건 정보를 담고있는 구조체 
int item_idx; // 사용자가 선택한 물건
char buf[BUFSIZ]; // send, receive에 사용하는 버퍼


void send_msg(int nsd, char* msg) {
	strcpy(buf, msg);
	
	if(send(nsd, buf, strlen(buf) + 1, 0) == -1) {
		perror("send");
		exit(1);
	}
	
	usleep(DELAY);
}


void receive_msg(int nsd) { 
	if(recv(nsd, buf, sizeof(buf), 0) == -1) {
		perror("recv");
		exit(1);
	}
}


void select_item(int nsd) {
	send_msg(nsd, "▶  구매하실 물건을 선택해주세요 ◀\n");
	send_msg(nsd, "[ 0.카메라 | 1.자켓 | 2.이어폰 | 3.안경 | 4.책 | 5.가방 | 6.머리끈 ]\n");
	send_msg(nsd, "1"); // 1번은 입력 받기
	receive_msg(nsd); // client 선택 받기
	
	item_idx = atoi(buf); // 물건 번호 저장
	printf("log : %d 사용자가 %s번을 선택하였습니다.\n", getpid(), buf);
}


void trade_or_exit(int nsd) {	
	if(item[item_idx].is_trading) // 다른 client가 물건을 거래중이라면
		wait_trade(nsd);	
	
	if(item[item_idx].is_selled) { // 물건이 이미 팔렸다면
		send_msg(nsd, "⚠  해당 물건이 이미 판매되었습니다 ⚠\n");
		sleep(2);
		
		if(re_trade(nsd)) // 다시 선택하거나 프로그램 종료
			trade_or_exit(nsd);
		else
			return;
	}	
	else { // 선택한 물건이 팔리지 않았으면		
		item[item_idx].is_trading = 1; // 거래중 여부 변수를 true로 갱신
		send_msg(nsd, "\n\n\n\n\n\n");
		trade(nsd); // 거래 함수 시작
	}	
}


void wait_trade(int nsd) {
	while(item[item_idx].is_trading) { // 선택한 물건이 거래중인 경우 대기
		send_msg(nsd, "다른 사용자가 거래중입니다\n");
		sleep(2);
		send_msg(nsd, ".......................\n");
		sleep(2);
	}			
}


int re_trade(int nsd) {
	send_msg(nsd, "\n\n\n\n\n\n"); 
	send_msg(nsd, "▶  다른 물건을 선택하시겠습니까? [Y / N] ◀\n");
	send_msg(nsd, "1"); // 1번은 입력 요청
	receive_msg(nsd); // client 선택 받기
	
	if(strcmp(buf, "y") == 0 || strcmp(buf, "Y") == 0) { // 다시 입력하겠다고 했다면 item 재선택
		send_msg(nsd, "\n\n\n\n\n\n"); 
		select_item(nsd); // 물건 재선택
		return 1;
	}
	else if(strcmp(buf, "n") == 0 || strcmp(buf, "N") == 0) { // 입력하지 않겠다면 프로그램 종료
		send_msg(nsd, "\n\n⚡  저희 번개나라를 이용해주셔서 감사합니다 ⚡\n\n");
		send_msg(nsd, "2"); // 2번은 프로그램 종료
		return 0;
	}
}


void trade(int nsd) {
	int given_price; // 사용자가 제시한 가격 저장 변수
	
	sprintf(buf, "💱  거래를 시작합니다 [ %s의 가격 : %s ] 💱", item[item_idx].name, item[item_idx].price);
	
	send_msg(nsd, buf);
	send_msg(nsd, "\n▶  희망하는 구매 가격을 제시해주세요 (물건 가격 이하의 금액 입력) ◀\n");
	send_msg(nsd, "1"); // 1은 입력 요청
	receive_msg(nsd);
	given_price = atoi(buf); // 입력값 저장

	// price : 고객에게 제시한 물건의 가격
	// min_price : 내부적으로 정해놓은 물건의 최소 가격
	if (atoi(item[item_idx].min_price) <= given_price && given_price <= atoi(item[item_idx].price)) { // 고객이 제시한 금액이 price와 min_price의 사이라면 물건 판매
		send_msg(nsd, "\n\n🤑  합리적인 가격인 것 같네요! 물건을 판매하겠습니다 🤑\n");
		sleep(2);
		send_msg(nsd, "\n\n⚡  저희 번개나라를 이용해주셔서 감사합니다 ⚡\n\n");
		send_msg(nsd, "2"); // client 프로그램 종료
		
		item[item_idx].is_selled = 1; // 해당 물건의 판매 여부를 true로 갱신
		item[item_idx].is_trading = 0; // 거래 중 여부 false로 갱신
		printf("log : %d 사용자가 물건을 구매하였습니다.\n", getpid());
		return;
	}
	else {
		send_msg(nsd, "\n\n😞  저희가 생각한 가격과 큰 차이가 있어 거래할 수 없을 것 같습니다 😞\n");
		sleep(2);
		
		if(re_trade(nsd)) // 다시 선택하거나 프로그램 종료
			trade_or_exit(nsd);
		else
			return;
	}
		
}


int main() { 
	struct sockaddr_un ser, cli;
	key_t key;
	int sd, nsd, len, clen, shmid;
	int exit_cnt = 0; // server 무한 반복 종료를 위한 count -> 물건이 다 팔리면 종료
	
	key = ftok("shmfile", 1); 
	shmid = shmget(key, sizeof(Data) * 10, IPC_CREAT | 0644);

	if (shmid == -1) {
		perror("shmget");
		exit(1);
	}

	item = (Data*) shmat(shmid, NULL, 0); // 구조체를 공유 메모리에 attach
	data_init(item); // 구조체 초기화
	shmdt(item); // 공유 메모리에서 detach
	
	unlink(SOCKET_NAME); // 서버 재실행시 오류를 방지하기 위해 만들어둔 소켓 삭제	
		
	if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
 	}

 	printf("***** Server Start - Create Socket ***** \n");

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
		if(exit_cnt == 10) // 종료 조건 처리 수요일에
			break;
		
		if ((nsd = accept(sd, (struct sockaddr *)&cli, &clen)) == -1) { // client의 접속 요청 대기
			perror("accept");
			exit(1);
		}
		
		switch (fork()) { // accept 받고 거래는 자식 프로세스에서 처리
			case -1:
				perror("fork");
				exit(1);
			case 0:
				send_msg(nsd, "⚡  번개나라에 오신 것을 환영합니다. ⚡\n\n\n");
				item = (Data*) shmat(shmid, NULL, 0);
				select_item(nsd); // 사용자 물건 입력 받기
				trade_or_exit(nsd);
				shmdt(item);
				break;
		}
	}

	shmctl(shmid, IPC_RMID, (struct shmid_ds *) NULL);
	// data_save(); 수요일에 처리리
	close(nsd);
}
