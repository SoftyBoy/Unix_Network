#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>


#define LISTENQ 15
#define MAX_LINE 200
#define bzero(ptr, size) memset(ptr, 0, size)

int main(int argc, char const *argv[])
{
	int ret = 0;
    int listenfd, connfd;
	struct sockaddr_in servaddr;
	struct sockaddr connaddr;
	char buff[MAX_LINE];
	time_t ticks;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (listenfd < 0) {
		/* code */
		printf("[Socket Error]==errno:%d, reason:%s\n", errno, strerror(errno));
		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(11300);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(listenfd, (struct sockaddr_in *)&servaddr, sizeof(servaddr));
	if (ret < 0) {
		/* code */
		printf("[Bind Error]==errno:%d, reason:%s\n", errno, strerror(errno));
		return -1;
	}
	
	ret = listen(listenfd, LISTENQ);
	if (ret < 0) {
		/* code */
		printf("[Listen Error]==errno:%d, reason:%s\n", errno, strerror(errno));
		return -1;
	}
	
	int size = sizeof(connaddr);
	for( ; ; )
	{
		/* code */
		printf("connecting...\n");
		connfd = accept(listenfd, (struct sockaddr *)&connaddr, &size);
		if (connfd < 0) {
			/* code */
			printf("[Accept Error]==errno:%d, reason:%s\n", errno, strerror(errno));
			return -1;
		}

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%24s\r\n", ctime(&ticks));
		printf("time: %s\n", buff);

		ret = write(connfd, buff, sizeof(buff));
		if (ret < 0) {
			/* code */
			printf("[Write Error]:==errno:%d, reason:%s\n", errno, strerror(errno));
			return -1;
		}
		
		ret = close(connfd);
		if (ret < 0) {
			/* code */
			printf("[Close Error]==errno:%d, reason:%s\n", errno, strerror(errno));
			return -1;
		}
	}
	

    return 0;
}
