#include <stdio.h>
#include <stdlib.h>

int main()
{  
    char *important_string = "SUPER SECRET PASSWORD!!!";
    char user_input[64] = "\x00"; 
    fgets(user_input, 64, stdin);
    printf("Hello %s\n", user_input);
    printf(user_input);                 
    return 0;
}


