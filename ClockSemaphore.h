//
// Created by Ben Cradick on 2019-03-17.
//

#ifndef CRADICK_3_CLOCKSEMAPHORE_H
#define CRADICK_3_CLOCKSEMAPHORE_H

#include <stdio.h>
#include <semaphore.h>


struct Semaphore;

typedef struct Semaphore {
    sem_t *semaphore;

}Semaphore;

Semaphore semaphore(Semaphore *this);
#endif //CRADICK_3_CLOCKSEMAPHORE_H
