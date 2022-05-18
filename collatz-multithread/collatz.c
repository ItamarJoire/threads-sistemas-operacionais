#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#define NUM_THREADS 1
 
// Thread que faz o cálculo de collatz  
void *threadBody (void *id){
    int tid = (long) id;
    
    while(tid > 1){
      printf("%2d ", tid);
      if(( tid % 2 ) == 0){
        tid = tid/2;
      }
      else{
        tid = (3 * tid) + 1;
      }
    }

    printf("%2d ", tid);
    printf("\n");
    
    printf("Aguardando a finalização da thread...\n");
    sleep(3);
    pthread_exit (NULL) ;
}
   
int main (int argc, char *argv[]){
  pthread_t thread [NUM_THREADS]; // Vetor de threads
  pthread_attr_t attr;

  pthread_attr_init (&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); // As threads usarão a flag attr.
  
  long i, status ;
  printf("Qual o valor: ");
  scanf("%ld", &i);

  printf ("Main: criando uma thread que faz o cálculo de Collatz e o mostra em tela.\n");

  status = pthread_create (&thread[i], &attr, threadBody, (void *) i) ;
  if (status){
    perror ("pthread_create") ;
    exit (1) ;
  }

  status = pthread_join(thread[i], NULL);   // Vou esperar aqui até que a thread se encerre.
  if (status){
    perror ("pthread_join") ;
    exit (1) ;
  }

  pthread_attr_destroy (&attr);
  pthread_exit (NULL) ;
}


