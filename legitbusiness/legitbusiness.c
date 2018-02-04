#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

#define BUSINESS_NAME_LENGTH 64
struct data{
  char business_name[BUSINESS_NAME_LENGTH];
  int year;
};

struct fp
{
  int (*fp)();
};

void clean_input_stream()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void whatsthis(char *cmd)
{
  system(cmd);
}

void generate_abn(char *name)
{
  printf("Thanks %s!\n");
}

int main(int argc, char **argv)
{
  struct data *d;
  struct fp *f;

  d = malloc(sizeof(struct data));
  f = malloc(sizeof(struct fp));
  f->fp = generate_abn;

  char business_name[BUSINESS_NAME_LENGTH];
  unsigned int business_year = 0;
  puts("Please enter a business name:");
  fgets(business_name, BUSINESS_NAME_LENGTH, stdin);
  puts("Please enter the year it begun:");
  scanf("%d", &business_year);

  memcpy(d->business_name, business_name, BUSINESS_NAME_LENGTH);
  d->year = business_year;

  char new_business_name[BUSINESS_NAME_LENGTH * 2] = "1337-Bizness";
  int new_business_year = 13;

  while(1){
    int menu_choice = 0;
    printf("1. Change business details.\n");
    printf("2. Show business details.\n");
    printf("3. Generate ABN\n");
    printf("4. Exit.\n");
    puts("Choice:");
    scanf("%d", &menu_choice);
    clean_input_stream();

    switch (menu_choice){

    case 1:
      puts("Please enter a new business name:");
      fgets(new_business_name, BUSINESS_NAME_LENGTH * 2, stdin);

      puts("Please enter the year it begun:");
      scanf("%d", &new_business_year);
      break;

    case 2:
      printf("Business details:\n");
      printf("Business Name: %s", d->business_name);
      printf("Business Year: %d\n", d->year);
      break;

    case 3:
      printf("Generating ABN...\n");
      sleep(5);

      printf("Your old business ABN is: [ %s - %d ]\n", d->business_name, d->year);

      memcpy(d->business_name, new_business_name, new_business_year);
      d->year = new_business_year;

      printf("Your new business ABN is: [ %s - %d ]\n", d->business_name, d->year);

      f->fp(business_name);

      break;

    case 4:
      printf("Adios!\n");
      exit(1);
    }

  }

}