#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 2

int array[] = {7, 12, 19, 3, 18, 4, 2, 6 ,15, 8};
int arrayOrdaneid[10];

void *threadSortOne (void *id){
    int index = (long) id;
    int i, j, min, aux;
  
    for (i = 0; i < (6 - 1); i++) {
        min = i;
    for (j = i+1; j < 5; j++) {
      if (array[j] < array[min]) {
        min = j;
      }
    }
    if (i != min) {
      aux = array[i];
      array[i] = array[min];
      array[min] = aux;
    }
  }
  printf ("Thread ordenador 1: ");
  // Imprime o array ordenado
  for (i = 0; i < 5; i++) {
    printf ("%d ",array[i]);
    arrayOrdaneid[i] = array[i];
  }
  printf ("\n");
        sleep(3);
    pthread_exit(NULL);

}

void *threadSortTwo (void *id){
    int index = (long) id;
    int i, j, min, aux;
  
    for (i = 5; i < (10 - 1); i++) {
        min = i;
    for (j = i+1; j < 10; j++) {
      if (array[j] < array[min]) {
        min = j;
      }
    }
    if (i != min) {
      aux = array[i];
      array[i] = array[min];
      array[min] = aux;
    }
  }
  // Imprime o array ordenado
  printf ("Thread ordenador 2: ");
  for (i = 5; i < 10; i++) {
    printf ("%d ",array[i]);
    arrayOrdaneid[i] = array[i];
  }
  printf ("\n");
        sleep(3);
    pthread_exit(NULL);

}

void *threadOrdaneit (void *id){
    int index = (long) id;
    int i, j, min, aux;
  
    for (i = 0; i < (10 - 1); i++) {
        min = i;
    for (j = i+1; j < 10; j++) {
      if (arrayOrdaneid[j] < arrayOrdaneid[min]) {
        min = j;
      }
    }
    if (i != min) {
      aux = arrayOrdaneid[i];
      arrayOrdaneid[i] = arrayOrdaneid[min];
      arrayOrdaneid[min] = aux;
    }
  }
  // Imprime o array ordenado
  printf ("Thread ordenador 3: ");
  for (i = 0; i < 10; i++) {
    printf ("%d ",arrayOrdaneid[i]);
  
  }
  printf ("\n\n");

    pthread_exit(NULL);

}

int main (int argc, char *argv[]){
    pthread_t thread [NUM_THREADS]; // array de threads
    pthread_attr_t attr; 
    long i = 0;
    long status;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);

    printf("Main: Criando THREAD %ld de ordenamento...\n", i+1);
    status = pthread_create (&thread[i], &attr, threadSortOne, (void *) i); 
    if(status){
        perror("pthread_create");
        exit(1);
    }

    printf("Main: Criando THREAD %ld de ordenamento...\n\n", i+2);
    status = pthread_create (&thread[i+1], &attr, threadSortTwo, (void *) i); 
    if(status){
        perror("pthread_create");
        exit(1);
    }


    printf("Aguardando as threds 1 e 2 concluirem.\n\n");
    sleep(3);
    for(int j = 0; j < NUM_THREADS-1; j++){
        status = pthread_join(thread[i], NULL);
        if(status){
            perror("pthread_join");
            exit(1);
        }
    }

    printf("\nMain: Criando THREAD %ld de ordenamento global...\n", i+3);
    status = pthread_create (&thread[i+2], &attr, threadOrdaneit, (void *) i); 
    if(status){
        perror("pthread_create");
        exit(1);
    }

    pthread_attr_destroy (&attr);
    pthread_exit(NULL);
}