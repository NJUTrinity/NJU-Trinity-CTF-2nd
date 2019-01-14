#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>


int main(void)
{   char buffer[0x20];
    int i;
    puts("Xiaobao Wei wants to find out the secret of 42 zhangjing, but he has to figure out the password first:");
    read(0,buffer,0x20);
    for(i=0;i<0x10;i++){
        if(buffer[i]!=(char)((i*i+0x66)&0xFF)){
            break;
        }
    }

    if(i!=0x10){
        puts("Stupid:(");
    }else{
        puts("Congradulation!");
        puts("Here is your flag:Trinity{This is a fake flag. The real one is on the server!}");
    }
    return 0;
}

static void __attribute__((constructor)) sub_123(void)
{
    char *addr=(char*)main;
    mprotect((void*)((unsigned long)addr&(0xFFFFFFFFFFFF000)),0x1000,PROT_READ|PROT_WRITE|PROT_EXEC);
    for(int i=0;i<0xA7;i++){
        addr[i]^=0x33;
    }
    mprotect((void*)((unsigned long)addr&(0xFFFFFFFFFFFF000)),0x1000,PROT_READ|PROT_EXEC);
    //mprotect((void*)addr,0x1000,PROT_READ|PROT_EXEC);
}
