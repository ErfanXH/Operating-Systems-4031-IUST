#include<stdio.h>
#include<dirent.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#define MAX_PATH_LENGTH 10
#define TRUE 1
#define FALSE 0

int MAP_SIZE, NUM_AGENTS;
pthread_mutex_t maplock;
char** map;

typedef struct {
    int initialPosition_x;
    int initialPosition_y;
    char* path;
}AgentArgs;

pthread_t* tids;


void* agent(void* args){
    int current_x = ((AgentArgs*)args)->initialPosition_x;
    int current_y = ((AgentArgs*)args)->initialPosition_y;
    char* path = ((AgentArgs*)args)->path;
    // initialize what you need  
    while(TRUE){
        // Your Code Here
        sleep(1);
    }
    return NULL;
}

int areEqual(char** a, char** b){
    for(int i = 0; i < MAP_SIZE; i++)
        for (int j = 0; j < MAP_SIZE; j++)
            if(a[i][j] != b[i][j])
                return FALSE;
    return TRUE;
}

void* renderer(void* args){
    char** prev_map = malloc(MAP_SIZE * sizeof(char*));
    for(int i = 0; i < MAP_SIZE; i++)
        prev_map[i] = malloc(MAP_SIZE * sizeof(char));
    while(TRUE){
        pthread_mutex_lock(&maplock);
        if(areEqual(map, prev_map) == FALSE){
            system("clear");
            for(int i = 0; i < MAP_SIZE; i++){
                for(int j = 0; j < MAP_SIZE; j++)
                    printf("%c ", map[i][j]);
                printf("\n");
            }
            for(int i = 0; i < MAP_SIZE; i++){
                for (int j = 0; j < MAP_SIZE; j++)
                    prev_map[i][j] = map[i][j];
            }
        }
        pthread_mutex_unlock(&maplock);
    }
    return NULL;
}
int main(int argc, const char * argv[]) {
    //Initialize what you need
    scanf(" %d", &MAP_SIZE);
    scanf(" %d", &NUM_AGENTS);
    pthread_mutex_init(&maplock, NULL);

    map = malloc(MAP_SIZE * sizeof(char*));
    for(int i = 0; i < MAP_SIZE; i++){
        map[i] = malloc(MAP_SIZE * sizeof(char));
        for(int j = 0; j < MAP_SIZE; j++)
            scanf(" %c", &map[i][j]); 
    }

    AgentArgs* agents = malloc(NUM_AGENTS * sizeof(AgentArgs));
    for(int i = 0; i < NUM_AGENTS; i++){
        int path_length;
        scanf(" %d", &agents[i].initialPosition_x);
        scanf(" %d", &agents[i].initialPosition_y);
        scanf(" %d", &path_length);
        agents[i].path = malloc(path_length * sizeof(char));
        for(int j = 0; j < path_length; j++)
            scanf(" %c", &agents[i].path[j]);  
    }

    tids = malloc((NUM_AGENTS + 1) * sizeof(pthread_t));
    pthread_create(&(tids[0]), NULL, &renderer, NULL);
    for(int i = 0; i < NUM_AGENTS; i++)
        pthread_create(&(tids[i + 1]), NULL, &agent, (void*)&agents[i]);

    for(int i = 1; i <= NUM_AGENTS; i++)
        pthread_join(tids[i], NULL);
    
    return 0;
}
