//Created by
//Duje Perisin and Vito Strahinjic

//We have used a mutex for locking the counter variable and semaphores for making sure our output is always
//printed in the right order. We could have used a semaphore for locking the counter variable, but we couldnt have
//used mutexes in place of semaphores because a mutex has to be locked and unlocked in the same thread.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/wait.h>
#define NUM_OF_THREADS 4

int counter=0;
sem_t s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13;
pthread_mutex_t counterMutex;

void *thread0(void *arg){
    int id= *(int*)arg;
    int i;

    sem_wait(&s2);  //waiting for thread1 ID to be printed

    printf("ID = %d\n", id);
    
    sem_post(&s3);  //allows I to be printed

    sem_wait(&s6);  //waiting for F to be printed

    printf("A\n");
    
    sem_post(&s7);  //allows G to be printed

    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counterMutex);
        counter++;
        pthread_mutex_unlock(&counterMutex);
    }
    
    sem_wait(&s10); //waiting for J to be printed

    printf("B\n");

    sem_post(&s11); //allows E to be printed

    sem_wait(&s12); //waiting for E to be printed 

    printf("C\n");
    
    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counterMutex);
        counter++;
        pthread_mutex_unlock(&counterMutex);
    }

    sem_post(&s13); //allows H to be printed

    return(NULL);
}

void *thread1(void *arg){
    int id= *(int*)arg;
    int i;

    sem_wait(&s1);  //waiting for thread2 ID to be printed

    printf("ID = %d\n", id);

    sem_post(&s2);  //allows thread0 ID to be printed

    sem_wait(&s4);  //waiting for I to be printed

    printf("D\n");

    sem_post(&s5);  //allows F to be printed
    
    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counterMutex);
        counter++;
        pthread_mutex_unlock(&counterMutex);
    }

    sem_wait(&s11); //waiting for B to be printed
    
    printf("E\n");

    sem_post(&s12); //allows C to be printed
    
    return 0;
    
}

void *thread2(void *arg){
    int id= *(int*)arg;
    int i;

    sem_wait(&s0);  //waiting for thread3 ID to be printed

    printf("ID = %d\n", id);
        
    sem_post(&s1);  //allows thread1 ID to be printed
    
    sem_wait(&s5);  //waiting for D to be printed
    
    printf("F\n");

    sem_post(&s6);  //allows A to be printed
    
    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counterMutex);
        counter++;
        pthread_mutex_unlock(&counterMutex);
    }
    
    sem_wait(&s7);   //waiting for A to be printed

    printf("G\n");

    sem_post(&s9);  //allows J to be printed
    
    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counterMutex);
        counter++;
        pthread_mutex_unlock(&counterMutex);
    }

    sem_wait(&s13); //waiting for C to be printed

    printf("H\n");
    
    return(NULL);
}

void *thread3(void *arg){
    int id= *(int*)arg;
    int i;

    printf("ID = %d\n", id);

    sem_post(&s0);  //allows thread2 ID to be printed

    for (i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&counterMutex);
        counter++;
        pthread_mutex_unlock(&counterMutex);
    }
    
    sem_wait(&s3);  //waiting for thread0 ID to be printed

    printf("I\n");  

    sem_post(&s4);  //allows D to be printed

    sem_wait(&s9);  //waiting for G to be printed

    printf("J\n");

    sem_post(&s10); //allows B to be printed

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
    sem_init(&s10, 0, 0);
    sem_init(&s11, 0, 0);
    sem_init(&s12, 0, 0);
    sem_init(&s13, 0, 0);
	pthread_mutex_init(&counterMutex, NULL);

	pthread_create(&th[3], NULL, &thread3, &id[3]);
	pthread_create(&th[2], NULL, &thread2, &id[2]);
	pthread_create(&th[1], NULL, &thread1, &id[1]);
	pthread_create(&th[0], NULL, &thread0, &id[0]);
	
	for(int i=0; i<NUM_OF_THREADS; i++){
		pthread_join(th[i], NULL);
	}

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
    sem_destroy(&s10);
    sem_destroy(&s11);
    sem_destroy(&s12);
    sem_destroy(&s13);

    printf("Counter value:  %d\n", counter);

    return 0;
}
