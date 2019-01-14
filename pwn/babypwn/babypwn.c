#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void initialize(){
    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);
    setvbuf(stderr,0,2,0);
}

int main()
{
    printf("杨过找不到小龙女，非常伤心，你能帮他找到小龙女吗\n");

    char secret[0x20]="Why_are_u_so_Dick";

    char s[0x10];
    while(1){
        printf("要找到小龙女，你必须输入九阴真经第八章的第一百零七句口诀:");
        read(0,s,0x100);
        if(memcmp(s,secret,strlen(secret))==0){
            printf("答对了，你是王重阳吗\n");
            system("/bin/sh");
        }else{
            printf("你说的什么鬼啊?");
            printf(s);
            printf("?");
        }
    }
    return 0;
}
