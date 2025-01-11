#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SOCKET_NAME "trade"

char buf[BUFSIZ];

void send_msg(int sd, char* msg) { // client에 메세지 전달 		
	strcpy(buf, msg);
	if(send(sd, buf, strlen(buf) + 1, 0) == -1) {
		perror("send");
		exit(1);
	}	
}

int receive_msg(int sd) { // client로부터 메세지 수신
	if(recv(sd, buf, sizeof(buf), 0) == -1) {
		perror("recv");
		exit(1);
	}
}

int main() {
	int sd, len;
	struct sockaddr_un ser;

	if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) { // 소켓 파일 기술자 생성
		perror("socket");
		exit(1);
	}
	
	memset((char *)&ser, '\0', sizeof(ser)); // 소켓 주소 구조체를 초기화
	ser.sun_family = AF_UNIX;
	strcpy(ser.sun_path, SOCKET_NAME);
	len = sizeof(ser.sun_family) + strlen(ser.sun_path);

	if (connect(sd, (struct sockaddr *)&ser, len) < 0) { // 클라이언트가 서버에 접속 요청
		perror("bind");
		exit(1);
	}
	
	while(1) {
		receive_msg(sd);
		
		if(strcmp(buf, "1") == 0) { // "1"을 받으면 표준 입력 후 전달
			printf(">> Select item : ");
			scanf("%s", buf);
			send_msg(sd, buf);
		}
		else if(strcmp(buf, "2") == 0) { // "2"를 받으면 프로그램 종료
			break;
		}
		else {
			printf("%s", buf); // 나머지 메세지는 client에 출력
		}
	}
	
	close(sd);
}
