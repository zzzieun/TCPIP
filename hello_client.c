#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, const char* argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0 , sizeof serv_addr);//serv_addr 0 으로 초기화
	char msg_buffer[BUFSIZ];	//BUFSIZ = 512
	//실행파일 ./HELLO_CLIENT 127.0.0.1 or 10.10.20.108 9999  => IP,port,9999 => 3개가 필요
	if(argc != 3)
	{
		printf("%s\r\n","사용방법 ./HELLO_CLIENT 127.0.0.1 9999");
		return 0;
	}

 	sock  = socket(PF_INET, SOCK_STREAM,0);
	if(sock == -1)
	{
		fputs("socket() error\r\n",stderr);
		return 0;
	}

	serv_addr.sin_family = AF_INET;	//IPv4
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);//서버 IP번호127.0.0.1 -> 문자를 숫자로 바꿔줘야함 : inet()->HEX
	serv_addr.sin_port = htons(atol(argv[2]));//"9999" => 9999 :문자가 숫자로 바뀜

	int con_state =connect(sock,(const struct sockaddr*)&serv_addr, sizeof serv_addr);
	if(con_state == -1)
	{
		fputs("commect() error\r\n",stderr);
		return 0;
	}
	int string_length = read(sock,msg_buffer ,sizeof msg_buffer -1);
	if(string_length == -1)
	{
		fputs("read() error\r\n",stderr);
		return 0;
	}

	fprintf(stderr,"서버에서 보낸 문자열: %s",msg_buffer);
	printf("\r\n");
	close(sock);

	return 0;
}
