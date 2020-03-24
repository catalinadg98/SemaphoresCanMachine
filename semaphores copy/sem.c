#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "utils.h"
#include "sem.h"


Semaphore *make_semaphore(int value)
{
  //printf("%i \n",value);
  Semaphore *sem = check_malloc(sizeof(Semaphore));
  sem->value = value;
  //printf("%i - \n",sem->value);
  //printf("%p inmake\n",sem);
  return sem;
}

void semaphore_wait(Semaphore *sem)
{
  //printf("%p wait \n",sem);
  //printf("%i \n",sem->value);
  sem->value--;
  //printf("%i wait \n",sem->value);
  if (sem->value < 0) {
    do {
      //printf("waiting: %i \n",sem->value);
    } while (sem->value < 0);
  }
  //printf("pass \n");
}

void semaphore_signal(Semaphore *sem)
{
  //printf("inside signal \n");
  sem->value++;
  //printf("%i \n",sem->value);
}