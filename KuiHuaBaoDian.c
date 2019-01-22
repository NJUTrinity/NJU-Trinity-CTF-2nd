#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

char Note[128][8];

void Init()
{
	setvbuf(stdin,0,_IONBF,0);
	setvbuf(stdout,0,_IONBF,0);
}


int ReadNum()
{
	char temp[8];
	bzero(temp,8);
	read(0,temp,8);
	return atoi(temp);
}

int menu()
{
	puts("1. Take Notes.");
	puts("2. Read Notes.");
	puts("3. DO IT whatever.");
	puts("4. Burn it.");
	puts("Your choice:");
	return 0;
}

void TakeNote()
{
	int num;
	puts("Which page?(0-127)");
	num=ReadNum();
	if (num>127)
	{
		puts("Out of range.");
		return;
	}
	puts("Write down your notes:");
	read(0,Note[num],8);
}

void ReadNote()
{
	int num;
	puts("Which page?(0-127)");
	num=ReadNum();
	fflush(stdin);
	if (num>127)
	{
		puts("Out of range.");
		return;
	}
	puts("Your notes:");
	write(1,Note[num],8);
}

void DoIt()
{
	puts("You have to do *IT* fist.");
	puts("Let me help you~~");
	if (close(1)==0)
		system("cat home/flag");
	exit(0);
}

int main()
{
	Init();
	puts("Now you have the <Kui Hua Bao Dian>.\nWhat do you want to do?");
	int i=0;
	while(1)
	{
		menu();
		i=ReadNum();
		switch(i)
		{
			case 1: TakeNote(); break;
			case 2: ReadNote(); break;
			case 3: DoIt(); break;
			case 4: goto EE;
			default: puts("Wrong choice!");
		}
	}
EE:
	puts("You burn it and learn nothing...");
	return 0;
}
