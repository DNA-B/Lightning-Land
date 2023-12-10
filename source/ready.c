#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ready.h"
#include "data_init.h"
// #include "trade.h" 형이 만들고나면 // 없애주시면 되요

void send_msg(int nsd, char* msg) {	
	strcpy(buf, msg);
	
	if(send(nsd, buf, strlen(buf) + 1, 0) == -1) {
		perror("send");
		exit(1);
	}
	
	sleep(1);
}

char* receive_msg(int nsd) {
	if(recv(nsd, buf, sizeof(buf), 0) == -1) {
		perror("recv");
		exit(1);
	}
	
	return buf;
}

void select_item(int nsd) {
	send_msg(nsd, "번개나라에 오신 것을 환영합니다.");
	send_msg(nsd, "구매하실 물건을 선택해주세요.");
	send_msg(nsd, "[ 0.카메라 | 1.자켓 | 2.이어폰 | 3.안경 | 4.책 | 5.가방 | 6.머리끈 ]");
	send_msg(nsd, "1"); // 1번은 입력 요청
	strcpy(buf, receive_msg(nsd)); // client 선택 받기
	
	item_idx = atoi(buf); // 물건 번호 저장
	printf("사용자(%d)가 %s번을 선택하였습니다.\n", getpid(), buf);
}

int re_trade(int nsd) {
	send_msg(nsd, "해당 물건이 이미 판매되었습니다.\n다른 물건을 선택하시겠습니까? [Y/N]");
	send_msg(nsd, "1"); // 1번은 입력 요청
	strcpy(buf, receive_msg(nsd)); // client 선택 받기
	
	if(strcmp(buf, "y") == 0 || strcmp(buf, "Y")) { // 다시 입력하겠다고 했다면 item 재선택
		select_item(nsd);
		return 1;
	}
	else if(strcmp(buf, "n") == 0 || strcmp(buf, "N")) { // 입력하지 않겠다면 프로그램 종료
		send_msg(nsd, "프로그램을 종료합니다. 이용해주셔서 감사합니다.\n");
		send_msg(nsd, "2"); // 2번은 프로그램 종료
		return 0;
	}
}

void trade_or_exit(int nsd) {
	struct Data* item = data_init();
	
	if(item[item_idx].cur_ppid == -1) { // 거래 중이지 않고, 팔리지도 않았음
		item[item_idx].cur_ppid = getpid(); // ppid 변수를 현재 거래를 시작한 자식 프로세스의 pid로 갱신
		item[item_idx].is_trading = 1; // 거래중 여부 변수를 true(1)로 갱신
		printf("----- start trade -----\n");
		// trade(); ------>> 여기서 거래함수 들어가요 trade.c에 trade 함수가 만들어져 있어야겠죠
	}	
	else if(item[item_idx].is_selled) { // 물건이 이미 팔렸다면 거래 종료
		send_msg(nsd, "----- this item already selled -----\n");
		exit(1);
	}
	else if(item[item_idx].is_trading) {
		while(item[item_idx].is_trading) // 거래가 끝날때까지 sleep
			sleep(1);
					
		if(item[item_idx].is_selled) { // 만약 팔렸다면 아이템 다시 선택 or 프로그램 종료
				re_trade(nsd) ? item_idx = atoi(buf) : exit(1);
		}
		else {
			send_msg(nsd, "----- start trade -----\n");
			item[item_idx].is_trading = 1; // 거래중 여부 변수를 true(1)로 갱신
			// trade();
		}
	}
}
