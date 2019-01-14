#include <stdio.h>
#include <string.h>

int main()
{
    char s[0x100];
    char k[]="Tqgkeost:<YViFWP84M3*)I\\td[hdfD\\bi\x13n";
    printf("Yang Guo is going to kill Yin Zhiping, do you know why?\n");
    memset(s,0,0x100);
    s[read(0,s,0xFF)-1]='\0';
    int size=strlen(s); 
    if(size!=36){
        printf("You don't know a shit!");
        exit(0);
    }
    for(int i=0;i<size;i++){
        s[i]-=(i%20);
    }
    if(memcmp(s,k,size)==0){
        puts("OH correct! How do u know that? Did you see it happen?");
    }else{
        puts("You don't know a shit!");
    }
    return 0;
}

