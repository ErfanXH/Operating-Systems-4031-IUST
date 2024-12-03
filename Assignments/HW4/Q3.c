#include<stdio.h>
#include<dirent.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include <time.h>

#define CAR_COUNT_PER_SPAWNER 20
#define MAX_SLEEP 3

enum Direction{
    NORTH,
    SOUTH,
    EAST,
    WEST
};

pthread_mutex_t Intersection_lock;

// For handling right turn logic
void turn_right(int id, int direction){    
    // Improve this Function
    pthread_mutex_lock(&Intersection_lock);
    switch (direction){
        case NORTH:
            printf("car with id %d with source %d is turning right from North to West\n", id, direction);
            sleep(rand() % MAX_SLEEP);
            break;
        case SOUTH:
            printf("car with id %d with source %d is turning right from South to East\n", id, direction);
            sleep(rand() % MAX_SLEEP);
            break;
        case EAST:
            printf("car with id %d with source %d is turning right from East to North\n", id, direction);
            sleep(rand() % MAX_SLEEP);
            break;
        case WEST:
            printf("car with id %d with source %d is turning right from West to South\n", id, direction);
            sleep(rand() % MAX_SLEEP);
            break;
        default:
            break;
    }
    pthread_mutex_unlock(&Intersection_lock);
}


// For handling straight logic
void go_straight(int id, int direction){ 
    // Improve this function
    pthread_mutex_lock(&Intersection_lock);   
    switch (direction){
        case NORTH:
            printf("car with id %d with source %d is going straight from North to South\n", id, direction);
            sleep(rand() % MAX_SLEEP);
            break;
        case SOUTH:
            printf("car with id %d with source %d is going straight from South to Norh\n", id, direction);
            sleep(rand() % MAX_SLEEP);
            break;
        case EAST:
            printf("car with id %d with source %d is going straight East to West\n", id, direction);
            sleep(rand() % MAX_SLEEP);
            break;
        case WEST:
            printf("car with id %d with source %d is going straight West to East\n", id, direction);
            sleep(rand() % MAX_SLEEP);
            break;
        default:
            break;
    }
    pthread_mutex_unlock(&Intersection_lock);
}

// For handling left turn logic
void turn_left(int id, int direction){ 
    // Improve this function
    pthread_mutex_lock(&Intersection_lock);   
    switch (direction){
        case NORTH:
            printf("car with id %d with source %d is turning left from North to East\n", id, direction);
            sleep(rand() % MAX_SLEEP);
            break;
        case SOUTH:
            printf("car with id %d with source %d is turning left from South to West\n", id, direction);
            sleep(rand() % MAX_SLEEP);
            break;
        case EAST:
            printf("car with id %d with source %d is turning left East to South\n", id, direction);
            sleep(rand() % MAX_SLEEP);
            break;
        case WEST:
            printf("car with id %d with source %d is turning left West to North\n", id, direction);
            sleep(rand() % MAX_SLEEP);
            break;
        default:
            break;
    }
    pthread_mutex_unlock(&Intersection_lock);
}

typedef struct{
    int source; 
    int count;
} SpawnerArgs;

// DO NOT CHANGE - Spawns cars from a given direction in the intersection
void* car_spawner(void* args){  
    SpawnerArgs* spawner_args = (SpawnerArgs*)args;
    int source = spawner_args->source;
    int count = spawner_args->count;
    for(int i = 0; i < count; i++){
        int move = rand() % 3;

        switch (move){
            case 0:
                turn_right(i, source);
                break;
            case 1:
                go_straight(i, source);
                break;
            case 2:
                turn_left(i, source);
                break;
            default:
                break;
        }
    }
}

// DO NOT CHANGE - Simulation Logic
int main (){
    pthread_t spawner_tid[4];
    SpawnerArgs args[4];
    clock_t time;
    time = clock();
    for(int i = 0; i < 4; i++){
        args[i].source = i;
        args[i].count = CAR_COUNT_PER_SPAWNER;
        pthread_create(&spawner_tid[i], NULL, car_spawner, (void*)&args[i]);
    }
    for(int i = 0; i < 4; i++)
        pthread_join(spawner_tid[i], NULL);
    time = clock() - time;
    double runtime = ((double)time);
    printf("the simulation took %f seconds\n", runtime);
    return 0;
}
