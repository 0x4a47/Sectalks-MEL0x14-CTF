#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

static char *binsh = "/bin/sh";
//TURN OFF ASLR : echo 0 | sudo tee / proc / sys / kernel / randomize_va_space
//Compiled with : gcc - m32 - fno - stack - protector - no - pie rop.c - o rop
void create_resume(char *name, char *job, int years)
{
    char resume_name[32] = "\x00";
    char resume_job[32] = "\x00";
    int resume_years = 1;

    strncpy(resume_name, name, 31);

    if(years > 0)
        resume_years = years;

    strncpy(resume_job, job, resume_years);

    printf("--------- Resume ---------\n");
    printf("Hello %s\n", resume_name);
    printf("You have been working as a %s for %d years\n", resume_job, resume_years);
    printf("--------- ###### ---------\n");
    fflush(stdin);
    
}
int main(int argc, char **argv)
{
    char job_buffer[100] = "\x00";
    char name_buffer[100] = "\x00";
    int number_years = 0;
    
    void (*systemadd)(int) = dlsym(RTLD_NEXT, "system");
    printf("system is @: %p\n", systemadd);

    puts("Welcome to our resume creator!\n");
    puts("Firstly, Please enter your name:");
    fgets(name_buffer, 100, stdin);

    puts("Next, Please enter your job title for a summary:");
    fgets(job_buffer, 100, stdin);

    puts("Finally, Enter the number of years you have been in the role:");
    scanf("%d", &number_years);

    puts("Creating resume item...\n");

    create_resume(name_buffer, job_buffer, number_years);

    puts("Thanks for creating with us :)\n");
    return 0;
}