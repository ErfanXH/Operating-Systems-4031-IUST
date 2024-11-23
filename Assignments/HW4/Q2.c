#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define BUFFER_SIZE 5
#define NUM_SENDERS 3
#define NUM_CONSUMERS 2
#define ACK_TIMEOUT 5 
/////////////////////////////////////////
pthread_cond_t ack_conds[NUM_SENDERS]; 
pthread_mutex_t lock_conds[NUM_SENDERS]; 

typedef struct {
    int id;
    int pid; 
    int ack; 
    char message[256];
} Packet;

typedef struct {
    Packet buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
    pthread_mutex_t lock;
} CircularBuffer;

CircularBuffer cb;

void* sender(void* arg) {
    int sender_id = *(int*)arg;
    while (1) {
        Packet pkt;
        pkt.id = rand() % 1000;
        snprintf(pkt.message, sizeof(pkt.message), "Message from sender %d", sender_id);
        pkt.pid = sender_id;  

       
        // To Do
        /*
            check the circular buffer size. 
            insert the packet, if there is space in circular buffer. 
            ouput message lke : 
            "Sender 5 sent packet with id 3" 
            or if buffer is full drop the packet. output message: 
            "Buffer full. Dropping packet with id 4"
            update Circular Buffer in theadSafe mood--> use mutex_lock/unlock correctly

            if (cb.count == BUFFER_SIZE) {
                example message --> "Buffer full. Dropping packet with id 4"
            } else {
                insert the packet in circular buffer , change the pointers in thread safe mood . 
            }

        */
       

        // To Do 
        /*
        check condition (timeout or sender recieve ack )
            output messages: 
                "Sender 5 failed to receive ACK for packet with id 312 (timeout)"
                OR
                "Sender 5received ACK for packet with id 312"
            use pthread_cond_timedwait: 
                threads will wait till the timeout or recieve ack. 
                echeckout input args to findout how to use mutex_lock. 
        */    
        
        
        sleep(rand() % 3);
    }
}

void* consumer(void* arg) {
    while (1) {      
        /*
            check if there is any packet in buffer.
            update pointers --> head & tail in thread_safe manner.
            use suitable output message.
            output message like: 
                "Consumer consumed packet with id 35, message: Message from sender 3"
                "Consumer sending ACK for packet id 35 to sender 3"
            we assum out network use Piggybacking. concat ack message with packet it self.
            pkt.ack =1 
            now signal the waiting thread to wake up. use : pthread_cond_signal
        */ 
        sleep(rand() % 3);
    }
}

int main() {
    /*
        change amount of sleep time and number of threads. 
        try to simulate most of possible conditions between threads like : 
        1- thread timeout for acknowledgement.
        2- full buffer
        3- empty buffer
        feel free to change the numbers :)
    */

    cb.head = 0;
    cb.tail = 0;
    cb.count = 0;
    pthread_mutex_init(&cb.lock, NULL);

    pthread_t senders[NUM_SENDERS];
    pthread_t consumers[NUM_CONSUMERS];

    
    int sender_ids[NUM_SENDERS];
    for (int i = 0; i < NUM_SENDERS; i++) {
        sender_ids[i] = i;
        pthread_cond_init(&ack_conds[i], NULL);
        pthread_mutex_init(&lock_conds[i], NULL);
        pthread_create(&senders[i], NULL, sender, (void*)&sender_ids[i]);
    }

   
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

        for (int i = 0; i < NUM_SENDERS; i++) {
        pthread_join(senders[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    for (int i = 0; i < NUM_SENDERS; i++) {
        pthread_mutex_destroy(&lock_conds[i]);
        pthread_cond_destroy(&ack_conds[i]);
    }
    return 0;
}

