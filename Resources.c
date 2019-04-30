//
// Created by Ben Cradick on 2019-04-29.
//

#include "Resources.h"
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/time.h>

int requestResource(Resources* this, pid_t pid);
/* These two functions make the rest of the code more readable */
int __remove(List*, pid_t pid);
int __append(List*, pid_t);

Resources* getResource(int index, int sem_size){
    Resources* this = malloc(sizeof(Resources));
    key_t needs_key = ftok(".", index + 1);
    key_t  has_key = ftok(".", index + 100);

    int needs_shmid = shmget(needs_key, sizeof(List), 0666 | IPC_CREAT);
    int has_shmid = shmget(has_key, sizeof(List), 0666 | IPC_CREAT);

    if((this->needs_resource = (List*) shmat(needs_shmid, NULL, 0)) == (void*)-1){
        perror("Failed to attach needs_resource to shared memory");
        exit(EXIT_FAILURE);
    }
    if((this->has_resource = (List*) shmat(has_shmid, NULL, 0)) == (void*)-1){
        perror("Failed to attach has_resource to shared memory");
        exit(EXIT_FAILURE);
    }
    this->resource_semaphore = sem_open(&letter[index], O_CREAT, 0666, sem_size);

    this->remove = &__remove;
    this->append = &__append;

    return this;
}
int requestResource(Resources* this, pid_t pid){
    if(this->append(this->needs_resource, pid)){
        fprintf(stderr, "Failed to add process %d to queue needs_resource\n", pid);
        return APPEND_ERR;
    }
    if(sem_wait(this->resource_semaphore)){
        fprintf(stderr, "failed to add process %d to semaphore wait queue\n", pid);
        if(this->remove(this->needs_resource, pid)){
            fprintf(stderr, "Failed to remove process %d from needs_resource", pid);
            return REMOVE_ERR;
        }
        return 1;
    }

    if(sem_post(this->resource_semaphore)){
        perror("Resources.c requestResource: Failed to post process to resource semaphore");
        return 1;
    }
    if(this->append(this->has_resource, pid)){
        fprintf(stderr, "Failed to append process %d from list has_resource", pid);
        return APPEND_ERR;
    }
    if(this->remove(this->needs_resource, pid)){
        fprintf(stderr, "Failed to remove process %d from list needs_resource", pid);
        return REMOVE_ERR;
    }
    return 0;
}
Resources** generateResources(){
    srand(time(0));
    Resources** resources = malloc(sizeof(Resources*)*20);
    int number_consumers = 1;
    for(int i = 0; i < 20; i++){
        if(i < 3){
            number_consumers = rand()%10 + 1;
        }
        else if(i > 2 && i < 6){
            if(rand()%2){
                number_consumers = rand()%10 + 1;
            }
        }
        else{
            number_consumers = 1;
        }

        resources[i] = getResource(i, number_consumers);
    }
    return resources;
}
int __remove(List* this, pid_t pid){
    return this->remove(this, pid);
}
int __append(List* this, pid_t pid){
    return this->append(this, pid);
}