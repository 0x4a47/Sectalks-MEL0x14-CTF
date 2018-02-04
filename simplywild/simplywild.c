#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

// UTILITIES
//OPAQUE PREDICATE, compile using -masm=intel
#define positive_sp_predicate_A     \
    __asm__("  push     eax      \n" \
            "  xor      eax, eax \n" \
            "  jz       AAAA  \n" \
            "  add      esp, 4   \n" \
            "AAAA:             \n" \
            "  pop      eax      ");

#define positive_sp_predicate_B   \
    __asm__("  push     eax      \n" \
            "  xor      eax, eax \n" \
            "  jz       BBBB  \n" \
            "  add      esp, 4   \n" \
            "BBBB:             \n" \
            "  pop      eax      ");
            
#define positive_sp_predicate_C   \
    __asm__("  push     eax      \n" \
            "  xor      eax, eax \n" \
            "  jz       CCCC  \n" \
            "  add      esp, 4   \n" \
            "CCCC:             \n" \
            "  pop      eax     ");

unsigned long long bigrandom()
{
    unsigned long long n = 0;
    do
    {
        n *= RAND_MAX;
        n += rand();
    } while (n < 1000000000);
    return n % 10000000000;
}

struct data
{
    char forkbombname[128];
};

struct fp
{
    int (*fp)();
};

void whatsthis()
{
    char *cmd = "/bin/bash";
    system(cmd);
}

void clean_input_stream()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//This challenge is going to combine multiple bugs into one interesting RCE case.
//bug 1: integer division resulting in a SIGFPE handler to be called. This handler will then use an opaque predicate to shield from f5 and do a couple other funky things.
//bug 2: the SIGFPE handler will launch into an 'admin' mode where a 1-time password will need to be 'guessed'. The user will need to enter the admin name (format string bug) and password. The password will be a random value that one needs to leak!
//bug 2a: Once you have the 1-time password, you will need to enter it into the admin password field to access the panel!
//bug 2b: Once you enter admin mode - you will only have 3 options: create fork-bomb , detonate & exit.
//bug 3 Options 2: When creating the fork-bomb, a heap-overflow will overwrite the function pointer to the 'detonate' function. Allowing us to provide our 'shell'.

void detonate(){
    puts("3...\n");
    sleep(1);
    puts("2...\n");
    sleep(1);
    puts("1...\n");
    sleep(1);
    puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    puts("           _ ._  _ , _ ._           ");
    puts("         (_ ' ( `  )_  .__)         ");
    puts("       ( (  (    )   `)  ) _)       ");
    puts("      (__ (_   (_ . _) _) ,__)      ");
    puts("         `~~`\\ ' . /`~~`           ");
    puts("                ; ;                 ");
    puts("               /   \\               ");
    puts("_____________ / _ __ \\_____________");
    puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    exit(1);
}


void thebomb(){
    positive_sp_predicate_C;
    
    puts("Well well well...\n");
    puts("You have made it this far, now there's only one final challenge!\n");
    puts("....... The Forkbomb .......\n");

    struct data *d;
    struct fp *f;

    char forkbombname[sizeof(d->forkbombname)*2];

    d = malloc(sizeof(struct data));
    f = malloc(sizeof(struct fp));
    f->fp = detonate;

    while(1){
        clean_input_stream();
        puts("You have 3 options...\n");
        puts("\t1.Create Fork-bomb\n");
        puts("\t2.Detonate Fork-bomb\n");
        puts("\t3.Exit\n");

        int choice = 0;
        puts("Choose wisely:");
        scanf("%d", &choice);
        clean_input_stream();
        switch (choice){
            case 1:
                puts("Create your fork bomb :D\n");
                puts("All you need to do is name it:");
                fgets(forkbombname, sizeof(d->forkbombname) * 2, stdin);
                memcpy(d->forkbombname, forkbombname, sizeof(d->forkbombname) * 2);
                break;
            case 2:
                puts("Detonating Fork Bomb...\n");
                sleep(3);
                f->fp();
                break;
            case 3:
                puts("See you later :D\n");
                exit(1);
                break;
            default:
                puts("Invalid selection.\n");
        }
    }

}

//bug 2: at this point, the user will be placed into the final stage - the bomb
void admin_mode(){
    positive_sp_predicate_B;

    char admin_name[1024] = "\x00";
    char admin_password[17] = "\x00";
    
    int numattempts = 0;
    while(numattempts < 5){
        puts("--### ADMIN MODE ###--\n");
        puts("Welcome to the admin console.\n");
        
        //generate our OTP and store it on the stack!
        unsigned long long tmppass = bigrandom();

        printf("Random password is: %llu\n", tmppass);

        puts("Please enter your name:");
        fgets(admin_name, 64, stdin);

        //bug 2: our format string bug to leak the password!
        //bug 2: Requires offset 8 to leak: %8$p
        printf(admin_name);

        puts("Please enter the password:");
        unsigned long long thepassword = 0; 
        scanf("%llu", &thepassword);

        if(thepassword == tmppass){
            puts("Congratz m4n, you've solved part 2!\n");
            sleep(3);
            thebomb();
        }
        //increase the number of attempts!
        numattempts++;
    }

    puts("~ Bad luck Neo ~\n");
    exit(1);

}

//bug 1: at this point, the user will now be launched into admin_mode. 
void launchpad(int a)
{
    //ensure our predicate works :)
    positive_sp_predicate_A;

    puts("Well done Neo, you have solved the first part. But this isn't over, this is just the beginning...\n");
    sleep(3);
    admin_mode();
}

int main(int argc, char **argv){
    //bug 1: Register the SIGFPE handler !
    signal(SIGFPE, launchpad);

    puts("===Welcome to the CryptoConverter 5000===\n");

    puts("Enter the value of currency 1:");
    char c1[24];
    char c2[24];
    fgets(c1, 23, stdin);
    puts("Enter the value of currency 2:");
    fgets(c2, 23, stdin);
    puts("Conversion by division...\n");

    //bug 1: Trigger the integer overflow !
    float result = abs(atoi(c1)) / atoi(c2);

    printf("Result is: %0.5f\n", result);

    puts("Thanks for using the converter!\n");
    return 0;
}