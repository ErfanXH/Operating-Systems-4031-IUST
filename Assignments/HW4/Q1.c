#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PRODUCTS  4
#define NUM_ASSEMBLY_MACHINES 4
#define NUM_QUALITY_CHECK_MACHINES 3
#define NUM_PACKAGING_MACHINES 2

#define BUFFER_SIZE_1 5
#define BUFFER_SIZE_2 3


/*
  use additional mutex if you need.
  explain what is the reason, which part became thread safe after
*/

sem_t assembly_machines;
sem_t quality_machines;
sem_t packaging_machines;

sem_t buffer1;
sem_t buffer2;


void assembly(int product_id) {
    /*
        simulate the process of assembling a product : 
        1- wait till one of machines in assembling stage get freed.product_id
        2- acquire machine, print suitable message shows which product is assembling . 
        3- wait for acquire one place in the queue between stage 1 and 2 . 
    */
    
}


void quality_check(int product_id) {
    /*
        simulate the process of quality checking for a product : 
        1- wait till one of machines in quality checking stage get freed.product_id
        2- dequeue from buffer1, acquire one machine, print suitable message shows which product is under quality checking. 
        3- wait for acquire one place in the queue between stage 2 and 3. 
    */
}


void packaging(int product_id) {
    /*
        simulate the process of packaging a product : 
        1- wait till one of machines in packaging stage get freed.product_id
        2- dequeue from buffer2, acquire one machine, print suitable message shows which product is packaging. 
        3- exit the pipeline. 
    */
}


void *product(void*arg){
    int product_id = *(int *)arg;
    assembly(product_id);
    quality_check(product_id);
    packaging(product_id);
    printf(" end of pipeline %d" , product_id ) ; 
    return NULL ; 
}


int main() {
    pthread_t products[NUM_PRODUCTS];
    int product_ids[NUM_PRODUCTS];

    // TODO 
    /*
        initialize semaphores 
        create threads 
    */
    
    printf("All products have been processed.\n");
    return 0;
}

