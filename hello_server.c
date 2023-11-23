#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>			//linux system file
#include <sys/socket.h>		//socket file
#include <arpa/inet.h>		//IP
						
int main(int argc, const char* argv[])
{
	int serv_sock = 0;
	int client_sock = 0;

	struct sockaddr_in serv_addr;	//store server address
	struct sockaddr_in client_addr;	//store client address	
	socklen_t client_addr_size=0ul;	

	const char message[] = {"Welcome my server."};

	if(argc !=2)
	{
		fprintf(stderr, "%s \r\n","USE - ./HELLO_WORLD 9999");
		return 0;
	}
					//IPv4 => PF_INET
	serv_sock = socket(PF_INET, SOCK_STREAM,0);	//(IPv4, TCP, IP-PROTO)
								//TCP	//IP = 0
	if(serv_sock == -1)
	{
		fputs("socket() error\r\n",stderr);
		return 0;
	}

	printf("Bridge = %d\r\n",serv_sock);
	if(serv_sock == -1)
	{
		fprintf(stderr,"%s \r\n","socket() error!!");
		return 0;
	}

	memset(&serv_addr, 0, sizeof serv_addr);	//모두 0으로 초기화
	memset(&client_addr, 0 , sizeof client_addr);

	serv_addr.sin_family = AF_INET;	//PF_INET => IPv4
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	//127.0.0.1 or 10.10.2.102
	serv_addr.sin_port = htons(atoi(argv[1]));	//'9999' => 9999
							
			//3
	int bind_status = bind(serv_sock, (const struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(bind_status == -1)
	{
		fputs("bind() error\r\n",stderr);
		return 0;
	}
						// 5 = queue
	int listen_status = listen(serv_sock,5);
	if(listen_status == -1)
	{
		fputs("listen() error\r\n",stderr);
		return 0;
	}

	client_sock = accept(serv_sock,(struct sockaddr*)&client_sock,(socklen_t*)&client_addr);	//클라이언트 번호만들기

	fprintf(stdout, "%s : %d\r\n","Client Bridge",client_sock);
	if(client_sock == -1)
	{
		fputs("accept() error\r\n", stderr);
		return 0;
	}

	client_addr_size = sizeof client_addr; // accept() 실행 후 값듷이 바뀜
	
	write(client_sock, message, sizeof message);
	close(client_sock);
	close(serv_sock);

	return 0;
}
