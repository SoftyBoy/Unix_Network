#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <netinet/sctp.h>

#define MAXLINE 20
#define bzero(ptr, n) memset(ptr, 0, n)

int main(const int argc, const char *argv[])
{
	int ret = 0;
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;


	if(2!=argc)
	{
		printf("usage: a.out <IPaddress>\n");
		return -1;
	}
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket errors, ret: %d\n", sockfd);
		return -1;
	}
	
	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htonl(8000);
	#if 0
	if((ret = inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) < 0)
	{
		printf("connect error, ret: %d\n", ret);
		return -1;
	}
	#endif
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);

	if((ret = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
	{
		printf("connect error, ret: %d\n", ret);
		//return -1;
	}

	while ((n = read(sockfd, recvline, MAXLINE)) > 0)
	{
		recvline[0] = 0;
		if (fputs(recvline, stdout) == EOF)
		{
			printf("fputs error!");
			return -1;
		}
	}

	if (n < 0)
	{
		printf("read error");
	}

	
	return 0;
}
