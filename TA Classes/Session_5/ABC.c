#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
// semaphore declarations

// order    
/*
A
.
.
.
F
.
.
.
C
.
*/

sem_t sem1 ; 
sem_t sem2 ; 

void* p1(void* arg)
{ 
    
    sem_wait(&sem1) ; 
    printf("F\n") ; 
    sem_post(&sem2) ; 
    printf("E\n") ; 
    printf("G\n") ; 
    return arg;
}

void* p2(void* arg){
    printf("A\n") ; 
    sem_post(&sem1);
    sem_wait(&sem2) ; 
    printf("C\n") ; 
    printf("B\n") ; 
    return arg;
}



int main(){
    // semaphore initializations
    // thread creations
    
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    pthread_t th[2];
    pthread_create(&th[1], NULL, &p2, NULL);
    pthread_create(&th[0], NULL, &p1, NULL);

    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);
    return 0;
}

