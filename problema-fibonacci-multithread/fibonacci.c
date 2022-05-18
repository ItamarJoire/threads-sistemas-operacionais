#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int numbers[0];
 
void *threadBody (void *id){
	int inputSize = (long) id;
	numbers[inputSize];
   
	int a, b, c, cont, position = 0;
   
	if(inputSize <= 1){
 		printf("Inválido\n");
	}else{
		a = 1;
		b = 1;
		cont = 0;
		while(cont < inputSize){
			c = a + b;
			numbers[position] = c;
			a = b;
			b = c;
			cont++;
			position++;
		}    
	}
   
	sleep(3);
	pthread_exit (NULL) ;
}
   
int main (int argc, char *argv[]){
   long inputSize, status;
   
   printf("Quantos números de Fibonacci deve aparecer? ");
   scanf("%ld", &inputSize);
   
   pthread_t thread [inputSize];
   pthread_attr_t attr;
   pthread_attr_init (&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   
   numbers[inputSize];
   
   printf ("Main: criando uma thread para gerar o Fibonacci\n");
 
   status = pthread_create (&thread[inputSize], &attr, threadBody, (void *) inputSize) ;
   if (status){
  	perror ("pthread_create") ;
  	exit (1) ;
   }
   
	status = pthread_join(thread[inputSize], NULL); // A partir daqui o código só será executado depois que a thread morrer.
	for(int i = 0; i < inputSize; i++){
		printf("%d ", numbers[i]);
		
		if (status){
			perror ("pthread_join") ;
			exit (1) ;
		}
  }
   
  printf ("\n");
   
	pthread_attr_destroy (&attr);
	pthread_exit (NULL) ;
}
 
 
 
 



