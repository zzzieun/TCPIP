#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(int argc, const char* argv[])
{
	int sock_fd = 0;	//소켓에 file descriptor
	char message[BUFSIZ] = {'\0'}; //최대 문자수는 512
	int str_length = 0;
	int receive_length = 0;
	int receive_count = 0;

	struct sockaddr_in serv_addr;
	if(argc != 3)
	{
		puts("./ECHO_CLIENT 127.0.0.1 9999\r\n");
		exit(1);
	}
	
	memset(&serv_addr, 0, sizeof serv_addr); // 0으로 초기화
	sock_fd = socket(PF_INET,SOCK_STREAM , 0);
	if(sock_fd == -1)
	{
		fprintf(stderr,"sock() error\r\n");
		exit(1);
	}
	serv_addr.sin_family= AF_INET;//IPv4
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);//			
	serv_addr.sin_port = htons(atoi(argv[2]));//문자가 숫자로 바뀜 HEX	
	if(connect(sock_fd,(const struct sockaddr*)&serv_addr,sizeof serv_addr) == -1)
	{
		puts("connect() error\r\n");
		exit(1);
	}
	else
	{
		puts("server is connected. \r\n");
	}
	while(1)
	{
		fputs("input message (Q to quit)",stdout);
		fgets(message,BUFSIZ,stdin);	//문자열 입력 함수 -> scanf 쓰지 마세요
		if(!strcmp(message,"q\n") || !strcmp(message, "Q\n"))
		{
			puts("종료\r\n");
			break;
		}
		str_length = write(sock_fd,message,strlen(message));
		receive_length = 0;
		while(receive_length < str_length)
		{
			receive_count = read(sock_fd, &message[receive_length],BUFSIZ -1);
			if(receive_count == -1)
			{
				printf("read() error\r\n");
			}
			receive_length += receive_count;
		}
		message[receive_length]= '\0';
		fprintf(stdout,"message from the server : %s\r\n",message);
	}
	close(sock_fd);
	return 0;
}
