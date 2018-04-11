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
	int i;
	int serv_sock;
	int client_sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;
	int client_addr_size;
	char message[256];
	int ending=0;
	
	if(argc != 2)
	{
		printf("Usage : %s <Port>\n", argv[0]);
		exit(1);
	}
	serv_sock = socket(PF_INET, SOCK_STREAM, 0); // 서버 소켓 생성
	
	if(serv_sock == -1)
		error_handling("socket() error");
		
	memset(&serv_addr, 0, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET; // Internet Protocol
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // IP Address
	serv_addr.sin_port = htons(atoi(argv[1])); // Port
	
	if(bind(serv_sock, (struct socketaddr*) &serv_addr, sizeof(serv_addr)) == -1) // 소켓에 주소 할당
		error_handling("bind() error");
	
	if(listen(serv_sock, 5) == -1) // listen stat 돌입
		error_handling("listen() error");
		 
	client_addr_size = sizeof(client_addr);
	
	while(!=ending)
	{
		client_sock=accept(serv_sock, (struct sockaddr*) &client_addr, &client_addr_size); // 연결 요청이 들어오면 수락
		
		if(client_sock == -1)
			error_handling("accept() error");
			
			scanf("%s", message);
			write(clnt_sock, message, sizeof(message)); // 전송할 데이터 쓰기
			
			if(message[0] == 0x1b) ending = 1; 
	}
	close(client_sock);
	
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
