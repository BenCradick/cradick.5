//
// Created by Ben Cradick on 2019-04-29.
//

#ifndef CRADICK_5_RESOURCES_H
#define CRADICK_5_RESOURCES_H

#include <semaphore.h>
#include "List.h"

#define APPEND_ERR 2
#define REMOVE_ERR 3

typedef enum Letter{
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T
}Letter;

char letter[20] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T'};


struct Resources;

typedef struct Resources{
    List* has_resource;
    List* needs_resource;
    sem_t* resource_semaphore;

    int(*append)(List*, pid_t);
    int(*remove)(List*, pid_t);


}Resources;

Resources* getResource(int, int);
Resources** generateResources();

#endif //CRADICK_5_RESOURCES_H
