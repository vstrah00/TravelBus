//Created by
//Duje Perisin and Vito Strahinjic

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/wait.h>
#define getName(var)  #var 
#define NUM_OF_THREADS 4

int counter=0;

void *thread0(void *arg){
    int id= *(int*)arg;
    int i;
    printf("ID = %d\n", id);
    printf("A\n");
    
    for (i = 0; i < 1000000; i++) {
       counter++;
    }
    
    printf("B\n");
    printf("C\n");
    
    for (i = 0; i < 1000000; i++) {
        counter++;
    }
    
    return(NULL);
}

void *thread1(void *arg){
    int id= *(int*)arg;
    int i;
    printf("ID = %d\n", id);
    printf("D\n");
    
    for (i = 0; i < 1000000; i++) {
       counter++;
    }
    
    printf("E\n");
    
    return 0;
    
}

void *thread2(void *arg){
    int id= *(int*)arg;
    int i;
    printf("ID = %d\n", id);
    printf("F\n");
    
    for (i = 0; i < 1000000; i++) {
       counter++;
    }
    
    printf("G\n");
    
    for (i = 0; i < 1000000; i++) {
        counter++;
    }

    printf("H\n");
    
    return(NULL);
}

void *thread3(void *arg){
    int id= *(int*)arg;
    int i;
    printf("ID = %d\n", id);

    for (i = 0; i < 1000000; i++) {
       counter++;
    }
    
    printf("I\n");
    printf("J\n");
    
    return 0;
    
}

int main(){
	pthread_t th[NUM_OF_THREADS];
	
	pthread_create(th[0], NULL, &thread0, 0);	
	pthread_create(th[1], NULL, &thread1, 0);	
	pthread_create(th[2], NULL, &thread2, 0);	
	pthread_create(th[3], NULL, &thread3, 0);	
	
	for(int i=0; i<NUM_OF_THREADS; i++){
		pthread_join(th[i], NULL);
	}
}