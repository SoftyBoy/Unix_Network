#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#undef CPU_VENDOR_OS
#define CPU_VENDOR_OS "$host"


int main(const int argc, const char *argv[])
{
    union {
		short s;
		char c[sizeof(short)];
	}un;

	un.s = 0x0102;
	printf("%s: ", CPU_VENDOR_OS);
    
	if(2 == sizeof(short)) 
	{	
		if (un.c[0] == 1 && un.c[1] == 2) {
			printf("big-endian\n");
		}
		else if (un.c[0]==2 && un.c[1] == 1) {
			printf("little-endian\n");
		}
		else {
			printf("unknown\n");
		}
	}
	else
	{
		printf("sizeof(short)=%lu\n", sizeof(short));
	}
	printf("sizeof(short)=%lu\n", sizeof(short));
    return 0;
}
