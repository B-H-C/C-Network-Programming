#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char **argv)
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len;
	int ending = 0;
	
	if(argc!=3)
	{
		printf("Usage : %s <IP> <Port>\n",argv[0]);
		exit(1);
	}
	
	while(!ending)
	{
		sock = sockeet(PF_INEET, SOCK_STREEAM, 0); //create a socket for connection the server;
		if(sock == -1)
		{
			error_handling("socket() error");
		}
		
		memset(&serv_addr, 0, sizeof(serv_addr)); // 메모리 초기화;
		
		serv_addr.sin_family = AF_INET; // 인터넷 주소 체계 저장;
		serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
		serv_addr.sin_port = htons(atoi(argv[2]));
		
		if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) // 서버로 연결 요청
			error_handling("connect() error");
			
		str_len = read(sock, message, sizeof(message) -1); // 데이터 수신
		
		if(str_len == -1)
			error_handling("read() error");
			
		message[str_len] = 0;
		
		printf("Message from server : %s \n",message);
		if(message[0] == 0x1b) ending = 1;
		
		close(sock); //연결 종료
	}
	return 0; 
}
