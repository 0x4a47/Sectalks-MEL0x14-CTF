#include <stdio.h>

//gcc -m32 -z execstack -fno-stack-protector -Wall format-string.c -o format-string
int main(int argc, char **argv){
    char padding[32] = "\x00"; 
    char flag[16];
    strncpy(flag, "FLAG=sectalks{l3ak_t1ll_y0u_fr3ak}", 36); 
    printf("Please enter the word which you would like to echo:");
    char word[500]; 
    fgets(word, 500, stdin);
    printf(word);
    printf("seeya.\n");
    return 0;
}