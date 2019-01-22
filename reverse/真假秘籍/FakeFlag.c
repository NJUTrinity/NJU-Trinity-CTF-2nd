#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

unsigned char t=0xe7;
unsigned char password[37]={0xb3,0x26,0x1b,0x07,0x07,0x1d,0x0d,0x02,0x23,0x31,0x08,0x0f,0x09,0x2b,0x7c,0x5e,0x09,0x38,0x33,0x54,0x67,0x25,0x12,0x09,0x0f,0x09,0x38,0x13,0x29,0x13,0x13,0x54,0x6e,0x2a,0x05,0x0d,0};
unsigned char key[60]={0};

int check(unsigned char *str) {
	int i=0;
	if (strlen(str)<strlen(password)) return -1;
	if ((str[0]^0x11)!=password[0]) return -1;
	for (i=1;str[i];i++)
	{
		if ( (str[i]^str[i-1]) != password[i] ) return -1;
	}
	return 1;
}

void NormalFunction() {
	void *addr=(void *)check;
	int page_size = getpagesize();
	addr -= (unsigned long)addr % page_size;
	if(mprotect(addr, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) == -1) {
		exit(-1);
	}
	memcpy(check+69,&t,1);
}

int main() {
    NormalFunction();

    puts("Please input your flag and I'll check it.");
	int n=read(0,key,60);
	if (key[n-1]=='\n')
		key[n-1]=0;
	if (check(key)==1)
		puts("Correct!");
	else
		puts("Invalid!");

    return 0;
}


