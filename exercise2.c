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
sem_t s0, s1, s2, s3, s4, s5, s6, s7, s8, s9;
pthread_mutex_t counterMutex;

void *thread0(void *arg){
    int id= *(int*)arg;
    int i;

    printf("ID = %d\n", id);

    sem_wait(&s7);  //waiting for F to be printed
    
    printf("A\n");
    
    sem_post(&s6);

    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counterMutex);
        counter++;
        pthread_mutex_unlock(&counterMutex);
    }
    
    sem_wait(&s4);  //waiting for J to be printed 

    printf("B\n");

    sem_post(&s3);

    sem_wait(&s2);  //waiting for E to be printed

    printf("C\n");

    sem_post(&s1);
    
    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counterMutex);
        counter++;
        pthread_mutex_unlock(&counterMutex);
    }
    
    return(NULL);
}

void *thread1(void *arg){
    int id= *(int*)arg;
    int i;

    printf("ID = %d\n", id);

    sem_post(&s0);

    sem_wait(&s9);  //waiting for I to be printed

    printf("D\n");

    sem_post(&s8);
    
    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counterMutex);
        counter++;
        pthread_mutex_unlock(&counterMutex);
    }
    
    sem_wait(&s3);  //waiting for B to be printed

    printf("E\n");

    sem_post(&s2);
    
    return 0;
    
}

void *thread2(void *arg){
    int id= *(int*)arg;
    int i;

    printf("ID = %d\n", id);

    sem_post(&s0);

    sem_wait(&s8);  //waiting for D to be printed

    printf("F\n");

    sem_post(&s7);
    
    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counterMutex);
        counter++;
        pthread_mutex_unlock(&counterMutex);
    }

    sem_wait(&s6);  //waiting for A to be printed
    
    printf("G\n");

    sem_post(&s5);
    
    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counterMutex);
        counter++;
        pthread_mutex_unlock(&counterMutex);
    }

    sem_wait(&s1); //waiting for C to be printed

    printf("H\n");
    
    return(NULL);
}

void *thread3(void *arg){
    int id= *(int*)arg;
    int i;
    printf("ID = %d\n", id);

    sem_post(&s0);

    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counterMutex);
        counter++;
        pthread_mutex_unlock(&counterMutex);
    }
    
    printf("I\n");

    sem_post(&s9);

    sem_wait(&s5);  //waiting for G to be printed

    printf("J\n");

    sem_post(&s4);
    
    return 0;
    
}

int main(){
	pthread_t th[NUM_OF_THREADS];
    int id[4]={0,1,2,3};
    
    sem_init(&s0, 0, 0);
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);
    sem_init(&s3, 0, 0);
    sem_init(&s4, 0, 0);
    sem_init(&s5, 0, 0);
    sem_init(&s6, 0, 0);
    sem_init(&s7, 0, 0);
    sem_init(&s8, 0, 0);
    sem_init(&s9, 0, 0);

    
	pthread_mutex_init(&counterMutex, NULL);

	pthread_create(&th[3], NULL, &thread3, &id[3]);
    sem_wait(&s0);
	pthread_create(&th[2], NULL, &thread2, &id[2]);
    sem_wait(&s0);
	pthread_create(&th[1], NULL, &thread1, &id[1]);
    sem_wait(&s0);
	pthread_create(&th[0], NULL, &thread0, &id[0]);
	
	for(int i=0; i<NUM_OF_THREADS; i++){
		pthread_join(th[i], NULL);
	}

    printf("%d\n", counter);
    
    sem_destroy(&s0);
    sem_destroy(&s1);
    sem_destroy(&s2);
    sem_destroy(&s3);
    sem_destroy(&s4);
    sem_destroy(&s5);
    sem_destroy(&s6);
    sem_destroy(&s7);
    sem_destroy(&s8);
    sem_destroy(&s9);


    return 0;
}
