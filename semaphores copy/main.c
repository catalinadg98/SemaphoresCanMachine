#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h> 
#include "utils.h"
#include "sem.h"

typedef struct {
    Semaphore *menuPermit;
    Semaphore *coinPermit;
    Semaphore *selectionPermit;
    Semaphore *alarmPermit;
    Semaphore *mutex;
    double *current;
    double *coke_price;
    double *dietcoke_price;
    double *fanta_price;
    double *sprite_price;
    int *coke_cans;
    int *dietcoke_cans;
    int *fanta_cans;
    int *sprite_cans;
    int *beeps;
  } args_struct;

void *acceptCoins(void *args) {
  double inserted = 0;
  args_struct *real_args = args;
  while(7>5){
    semaphore_wait(real_args->coinPermit);
    semaphore_wait(real_args->mutex);
    sleep(1);
    printf("Enter money\n");
    scanf("%lf", &inserted);
    if(inserted>0){
      *real_args->current = *real_args->current + inserted;
    //printf("Current money: %f \n", *real_args->current);
    } else {
      printf("Money cannot be less than or equal to $0\n\n");
    }
    semaphore_signal(real_args->menuPermit);
    semaphore_signal(real_args->mutex);
    
  }
  return NULL;
}

void *selectionMenu(void *args){
  args_struct *real_args = args;
  int number;
  while(true){
    semaphore_wait(real_args->selectionPermit);
    semaphore_wait(real_args->mutex); //takes print permit
    printf("Select the operation you want: \n"
           "1.- Coca Cola Price: %f\n"
           "2.- Diet Coca Cola Price: %f\n"
           "3.- Fanta Price: %f\n"
           "4.- Sprite Price: %f\n"
           "0.- Back\n",*real_args->coke_price, *real_args->dietcoke_price, *real_args->fanta_price, *real_args->sprite_price);
    scanf("%i", &number);
    switch(number){
      case 1:
        if(*real_args->coke_cans > 0){
          if(*real_args->current >= *real_args->coke_price){
            printf("%i\n",*real_args->coke_cans);
            *real_args->coke_cans = *real_args->coke_cans-1;
            printf("%i\n",*real_args->coke_cans);
            double change = *real_args->current-*real_args->coke_price;
            if(change > 0){
              *real_args->beeps = 2;
              semaphore_signal(real_args->alarmPermit);
              semaphore_wait(real_args->mutex);
              printf("Here's your Coca Cola, your change is $%lf\n\n", change);
            }
            *real_args->current = 0;
          } else {
            printf("Not enough money, keep entering more until you have %lf or more\n", *real_args->coke_price);

          }
        } else {
          *real_args->beeps = 3;
          semaphore_signal(real_args->alarmPermit);
          semaphore_wait(real_args->mutex);
          printf("WE'RE OUT OF COCA COLA\n\n");
        }
        break;
      case 2:
        if(*real_args->dietcoke_cans > 0){
          if(*real_args->current >= *real_args->dietcoke_price){
            printf("%i\n",*real_args->dietcoke_cans);
            *real_args->dietcoke_cans = *real_args->dietcoke_cans-1;
            printf("%i\n",*real_args->dietcoke_cans);
            double change = *real_args->current-*real_args->dietcoke_price;
            if(change > 0){
              *real_args->beeps = 2;
              semaphore_signal(real_args->alarmPermit);
              semaphore_wait(real_args->mutex);
              printf("Here's your Diet Coca Cola, your change is $%lf\n\n", change);
            }
            *real_args->current = 0;
          } else {
            printf("Not enough money, keep entering more until you have %lf or more\n", *real_args->dietcoke_price);

          }
        } else {
          *real_args->beeps = 3;
          semaphore_signal(real_args->alarmPermit);
          semaphore_wait(real_args->mutex);
          printf("WE'RE OUT OF DIET COCA COLA\n\n");
        }
        break;
      case 3:
        if(*real_args->fanta_cans > 0){
          if(*real_args->current >= *real_args->fanta_price){
            printf("%i\n",*real_args->dietcoke_cans);
            *real_args->fanta_cans = *real_args->fanta_cans-1;
            printf("%i\n",*real_args->fanta_cans);
            double change = *real_args->current-*real_args->fanta_price;
            if(change > 0){
              *real_args->beeps = 2;
              semaphore_signal(real_args->alarmPermit);
              semaphore_wait(real_args->mutex);
              printf("Here's your Fanta, your change is $%lf\n\n", change);
            }
            *real_args->current = 0;
          } else {
            printf("Not enough money, keep entering more until you have %lf or more\n", *real_args->fanta_price);

          }
        } else {
          *real_args->beeps = 3;
          semaphore_signal(real_args->alarmPermit);
          semaphore_wait(real_args->mutex);
          printf("WE'RE OUT OF FANTA\n\n");
        }
        break;
      case 4:
        if(*real_args->sprite_cans > 0){
          if(*real_args->current >= *real_args->sprite_price){
            printf("%i\n",*real_args->sprite_cans);
            *real_args->sprite_cans = *real_args->sprite_cans-1;
            printf("%i\n",*real_args->sprite_cans);
            double change = *real_args->current-*real_args->sprite_price;
            if(change > 0){
              *real_args->beeps = 2;
              semaphore_signal(real_args->alarmPermit);
              semaphore_wait(real_args->mutex);
              printf("Here's your Sprite, your change is $%lf\n\n", change);
            }
            *real_args->current = 0;
          } else {
            printf("Not enough money, keep entering more until you have %lf or more\n", *real_args->dietcoke_price);

          }
        } else {
          *real_args->beeps = 3;
          semaphore_signal(real_args->alarmPermit);
          semaphore_wait(real_args->mutex);
          printf("WE'RE OUT OF SPRITE\n\n");
        }
        break;
      default:
        break;

    }
    semaphore_signal(real_args->menuPermit);
    semaphore_signal(real_args->mutex);//releases print permit
  }
  return NULL;
}

void *alarmProcess(void *args){
  args_struct *real_args = args;
  while(true){
    semaphore_wait(real_args->alarmPermit);
    //printf("%i",*real_args->beeps);
    while(*real_args->beeps>0){
      printf("*BEEP*");
      *real_args->beeps = *real_args->beeps-1;
    }
    printf("\n");
    semaphore_signal(real_args->mutex);
  }
  return NULL;
}

void *mainProcess(void *args){
  args_struct *real_args = args;
  bool cont = true;
  int number = 0;
  while(cont){
    semaphore_wait(real_args->menuPermit);
    semaphore_wait(real_args->mutex); //takes print permit
    printf("Select the operation you want: \n"
        "1.- Insert Money\n"
        "2.- Buy Soda\n"
        "3.- Return Money\n"
        "0.- Exit Program\n");
    printf("Current money: %f \n", *real_args->current);
    scanf("%i", &number);
    switch (number){
      case 0:
        cont = false;
        break;
      case 1:
        semaphore_signal(real_args->coinPermit);
        semaphore_signal(real_args->mutex);//releases print permit
        break;
      case 2:
        semaphore_signal(real_args->selectionPermit);
        semaphore_signal(real_args->mutex);//releases print permit
        break;
      case 3:
        printf("Returned $%lf\n\n",*real_args->current);
        *real_args->current=0;
        semaphore_signal(real_args->menuPermit);
        semaphore_signal(real_args->mutex);//releases print permit
        break;
      default:
        printf("Incorrect operation. Try again\n\n");
        semaphore_signal(real_args->menuPermit);
        semaphore_signal(real_args->mutex);//releases print permit
        break;
    }
  }
  return NULL;
}

int main(void) {

  double coke_price = 15;
  double dietcoke_price = 12;
  double fanta_price = 10;
  double sprite_price = 11;
  int coke_cans = 15;
  int dietcoke_cans = 15;
  int fanta_cans = 15;
  int sprite_cans = 15;
  double payment = 0;
  int beeps = 0;
  
  pthread_t p_coins, p_main, p_selection, p_alarm;
  Semaphore *menu = make_semaphore(0);    //semaforo para mostrar el menu
  Semaphore *coin = make_semaphore(0);    //semaforo para recibir monedas
  Semaphore *select = make_semaphore(0);  //semaforo para seleccionar bebida
  Semaphore *alarm = make_semaphore(0);   //semaforo para activar alarma
  Semaphore *mutex = make_semaphore(0);   //semaforo de escribir a pantalla
  
  args_struct *shared_args = malloc(sizeof *shared_args);
  shared_args->menuPermit = menu;
  shared_args->coinPermit = coin;
  shared_args->selectionPermit = select;
  shared_args->alarmPermit = alarm;
  shared_args->mutex = mutex;
  shared_args->current = &payment;
  shared_args->coke_price = &coke_price;
  shared_args->dietcoke_price = &dietcoke_price;
  shared_args->fanta_price = &fanta_price;
  shared_args->sprite_price = &sprite_price;
  shared_args->coke_cans = &coke_cans;
  shared_args->dietcoke_cans = &dietcoke_cans;
  shared_args->fanta_cans = &fanta_cans;
  shared_args->sprite_cans = &sprite_cans;
  shared_args->beeps = &beeps;

  pthread_create(&p_main, NULL, mainProcess, (void*)shared_args);
  pthread_create(&p_coins, NULL, acceptCoins, (void*)shared_args);
  pthread_create(&p_selection, NULL, selectionMenu, (void*)shared_args);
  pthread_create(&p_alarm, NULL, alarmProcess, (void*)shared_args);

  semaphore_signal(menu);
  semaphore_signal(mutex);
  
  pthread_join(p_main, NULL);  //falta un proceso que solo termine al terminar de usar el 
                                //programa
  printf("Good Bye!\n");
  return 0;
}