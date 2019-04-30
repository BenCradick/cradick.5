//
// Created by Ben Cradick on 2019-04-09.
//

#include "VClock.h"
#include "ClockSemaphore.h"
#include <stdlib.h>
#include <memory.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>



//referencable function prototypes
void increment(VClock*);
void messageIncrement(VClock*);
void _detach(VClock*);
void _clean(VClock*);

int total(VClock*);
VClock* vClock(){
    VClock *clock = malloc(sizeof(VClock));

    clock->nano_key = ftok(".", 1);
    clock->sec_key = ftok(".", 2);

    clock->nano_shmid = shmget(clock->nano_key, sizeof(int), 0666 | IPC_CREAT);
    clock->sec_shmid = shmget(clock->sec_key, sizeof(int), 0666 | IPC_CREAT);

    clock->nano = (int*) shmat(clock->nano_shmid, NULL, 0);
    clock->sec = (int*) shmat(clock->sec_shmid, NULL, 0);

    clock->clock_semaphore = semaphore(&clock->clock_semaphore);

    clock->increment  = &increment;
    clock->messageIncrement = &messageIncrement;
    clock->detach = &_detach;
    clock->clean = &_clean;

    clock->total = &total;

    return clock;
}

//increments by 1 sec and [0,1000] nanoseconds as per instructions
void increment(VClock* clock){

    srand((unsigned int)time(0));

    sem_wait(clock->clock_semaphore.semaphore);

    *clock->sec += 1;
    *clock->nano += rand()%1001; //if modulo 1000 then range 0-999

    if(*clock->nano > BILLION){
        int temp = *clock->nano - BILLION;
        *clock->nano = temp;
        *clock->sec += 1;
    }

    sem_post(clock->clock_semaphore.semaphore);

}
void messageIncrement(VClock* clock){

    srand((unsigned int)time(0));

    *clock->nano += rand()%9900 + 100;

    if(*clock->nano > BILLION){
        int temp = *clock->nano - BILLION;
        *clock->nano = temp;
        *clock->sec += 1;
    }
}

int total(VClock* clock){
    return (*clock->sec * BILLION) + *clock->nano;
}
// detaches local clock from shared memory
void _detach(VClock* clock){
    shmdt(clock->nano);
    shmdt(clock->sec);
}
// erases the shared memory
void _clean(VClock* clock){
    shmctl(clock->nano_shmid, IPC_RMID, NULL);
    shmctl(clock->nano_shmid, IPC_RMID, NULL);
}