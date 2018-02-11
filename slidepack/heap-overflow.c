#include <stdio.h>
#include <stdlib.h>

struct auth{
    char name[32];
    int admin;
};

int main()
{  
    int admin = 0;
    char temp_buffer[128] = "\x00";

    struct auth *unpriv_user;

    unpriv_user = malloc(sizeof(struct auth));
    unpriv_user->admin = 0;

    fgets(temp_buffer, 128, stdin);
    memcpy(unpriv_user->name, temp_buffer, sizeof(temp_buffer));

    if(unpriv_user->admin == 0){
        printf("admin = %x\n", unpriv_user->admin);
        printf("You are not the admin - go away!\n");
        exit(0);
    }else{
        printf("admin = %x\n", unpriv_user->admin);
        printf("Welcome Admin!\n");
    }

    return 0;
}


