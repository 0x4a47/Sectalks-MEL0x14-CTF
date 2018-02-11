#include <stdio.h>
#include <stdlib.h>

void foo(int a, char *buffer){
    char small_buffer[64];
    strcpy(small_buffer, buffer);
}
int main(){
    int param1 = 5;
    char big_buffer[128];
    fgets(big_buffer, 128, stdin);
    foo(param1, big_buffer);                
    return 0;
}

void bar(){
    printf("Woo! You called bar()\n");
}

