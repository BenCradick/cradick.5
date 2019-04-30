//
// Created by Ben Cradick on 2019-03-17.
//
#include "ClockSemaphore.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

Semaphore semaphore(Semaphore *this)
{
    this->semaphore = sem_open("clock", O_CREAT, 0666, 1);
    if(errno != 0){
        perror("Unable to initialize semaphore");
        exit(EXIT_FAILURE);
    }

    return *this;
}
