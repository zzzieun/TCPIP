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
	int server_sock = 0;	//server socket 다리 넘버
	int client_sock = 0;	//client socket 다리 넘버
	char message[BUFSIZ] ={'\0'};	//최대 저장가능한 문자열 : 512
	socklen_t client_addr_size = 0ul;

	if(argc != 2)
	{
		puts("./ECHO_SERVER 9999\r\n");
		exit(1); // return 0;
	}
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	memset(&server_addr,0,sizeof server_addr);
	memset(&client_addr,0,sizeof client_addr);
	//socket함수
	server_sock = socket(PF_INET,SOCK_STREAM,0);//(IPv4,TCP,IPPROTO)
	if(server_sock == -1)
	{
		return 0;
	}
	server_addr.sin_family = AF_INET;	//PF_INET = IPv4
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //내 서버의 IP
	server_addr.sin_port = htons(atol(argv[1]));
	
	if(bind(server_sock, (const struct sockaddr*)&server_addr,sizeof server_addr) == -1)
	{
		fprintf(stderr,"%s\r\n","bind() error");
		exit(1);
	}

	if(listen(server_sock, 5) ==1)
	{
		fprintf(stderr,"%s\r\n","listen() error");
		exit(1);
	}
	//accept 5번 호출 되게
	for(int i = 0 ; i < 5 ; ++i)
	{
		client_sock = accept(server_sock,(struct sockaddr*)&client_addr,(socklen_t*)&client_addr_size);
		if(client_sock == -1)
		{
			fprintf(stderr,"%s\r\n","accept() error");
			exit(1);
		}
		fprintf(stdout,"%d  %s\r\n",client_sock," is connected..");

		while((str_length = read(client_sock, message, BUFSIZ)) != 0)	//읽어온 글자가 1 이상이면 문자를 보냈다는 의미
		{//클라이언트 한테 다시 보내줘야 함
			write(client_sock, message, str_length);	//sending to client
		}
		close(client_sock);
	}
	close(server_sock);

	return 0;
}
