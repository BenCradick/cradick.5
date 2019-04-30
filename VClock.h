//
// Created by Ben Cradick on 2019-04-09.
//

#ifndef CRADICK_4_VCLOCK_H
#define CRADICK_4_VCLOCK_H


#include <sys/types.h>
#include "ClockSemaphore.h"

#define BILLION 1000000000
struct VClock;

typedef struct VClock {
    // sec short for second, nano is nano second
    key_t nano_key;
    key_t sec_key;

    int nano_shmid;
    int sec_shmid;

    int* nano;
    int* sec;

    Semaphore clock_semaphore;

    void(*increment)(struct VClock*);
    void(*messageIncrement)(struct VClock*);
    void(*detach)(struct VClock*);
    void(*clean)(struct VClock*);

    int(*total)(struct VClock*);

}VClock;

VClock* vClock();
#endif //CRADICK_4_VCLOCK_H
