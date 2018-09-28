#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <netinet/sctp.h>

#define MAXLINE 200
#define bzero(ptr, n) memset(ptr, 0, n)

int main(const int argc, const char *argv[])
{
	int ret = 0;
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;


	if(2 != argc)
	{
		printf("Usage: a.out <IPaddress>\n");
		return -1;
	}
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("[Socket Error]==errno: %d, reason: %s\n", errno, strerror(errno));
		return -1;
	}
	//ret = argc, printf("hello\n");
	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(11300);
	printf("%s\n", argv[1]);
#if 1
	if((ret = inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) < 0)
	{
		printf("[Connect error]==errno: %d, reason: %s\n", errno, strerror(errno));
		return -1;
	}
#else
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
#endif
	if((ret = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
	{
		printf("[Connect error]==errno: %d, reason: %s\n", errno, strerror(errno));
		return -1;
	}
	
	recvline[0] = 0;
	while ((n = read(sockfd, recvline, MAXLINE)) >= 0)
	{
		if (fputs(recvline, stdout) == EOF)
		{
			printf("fputs error!\n");
			return -1;
		}
	}

	if (n < 0)
	{
		printf("[Read Error]:==errno: %d, reason: %s\n", errno, strerror(errno));
	}

	
	return 0;
}
