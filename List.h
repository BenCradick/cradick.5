//
// Created by Ben Cradick on 2019-04-29.
//

#ifndef CRADICK_5_LIST_H
#define CRADICK_5_LIST_H

#include <ntsid.h>
struct Node;

typedef struct Node{
    pid_t pid;
    struct Node* next;
    struct Node* last;

}Node;

typedef struct List{

    int size;
    Node* head;
    int(*append)(struct List*, pid_t);
    int(*remove)(struct List*, int);

    struct List* this;

}List;

List* list();
#endif //CRADICK_5_LIST_H
