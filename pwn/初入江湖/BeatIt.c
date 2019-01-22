#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void Init()
{
	setvbuf(stdin,0,_IONBF,0);
	setvbuf(stdout,0,_IONBF,0);
}

int main()
{
	Init();
	int turn=0,c=0;
	unsigned char Hp=160,Mp=0;
	unsigned char E_Hp=100;
	int E_attack=16,damage=0;
	int attack=0,armor=0;
	puts("Beat your enemy.");
	while (E_Hp>0 && Hp>0)
	{
		turn++;
		Mp+=10;
		printf("------Round %d------\n",turn);
		printf("Your Hp:%d Your Mp:%d\n",Hp,Mp);
		printf("Enemy Hp:%d Enemy Attack:%d\n",E_Hp,E_attack*turn);
		puts("Chose your action:");
		puts("1. Attack.");
		puts("2. Defend.");
		puts("3. Xiang Long 18 Zhang(cost 100MP)");
		puts("4. Ling Bo Wei Bu(cost 20MP)");
		scanf("%d",&c);
		attack=0; armor=0;
		if (c<1 || c>4 || c==3 && Mp<100 || c==4 && Mp<20)
		{
			puts("You just do nothing.");
			printf("Enemy deal %d damage to you.\n",E_attack*turn);
			Hp-=E_attack*turn;
		}
		else
		{
			switch(c)
			{
				case 1: attack=10; break;
				case 2: armor=16; break;
				case 3: attack=100; armor=10000; Mp-=100; break;
				case 4: armor=10000; Mp-=20; break;
			}
			if (attack>0)
			{
				printf("Your deal %d damage.\n",attack);
				E_Hp-=attack;
			}
			else
				puts("You deal no damge.");
				
			damage=E_attack*turn-armor;
			if (damage>0)
			{
				printf("Enemy deal %d damage to you.\n",damage);
				Hp-=damage;
			}
			else
				puts("Enemy deal no damage to you.");
		}
		
	}
	if (Hp==0)
	{
		puts("You Die!");
	}
	else
	{
		puts("You win!");
		system("/bin/sh");
	}
	return 0;
}
