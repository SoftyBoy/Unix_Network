#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
//#include <arpa/inet.h>

#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46


int inet_pton(int family, const char *strptr, void *addrptr)
{
	
	if (family == AF_INET) 
	{
		struct in_addr in_val;	
		if (inet_aton(strptr, &in_val))
		{
			memcpy(addrptr, &in_val, sizeof(struct in_addr));
			return (1);
		}
		return(0);
	}
	errno = EAFNOSUPPORT;
	return (-1);
}

const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
	const u_char *p = (const u_char *)addrptr;
	if (family == AF_INET)
	{
		char temp[INET_ADDRSTRLEN];
		snprintf(temp, sizeof(temp), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
		if (strlen(temp) >= len)
		{
			errno = ENOSPC;
			return strptr;
		} 
	}
	errno = EAFNOSUPPORT;
	return (NULL);
}


int main(const int argc, char const *argv[])
{
	
	return 0;
}
