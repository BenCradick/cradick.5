//
// Created by Ben Cradick on 2019-04-29.
//

#include "List.h"
#include <stdlib.h>
int append(List *this, pid_t pid);
int remove(struct List *this, pid_t val);
List* list(){
    List* this = malloc(sizeof(struct List));
    this->head = NULL;
    this->size = 0;
    this->append = &append;
    this->remove = &remove;

    return this;
}

int append(List *this, pid_t pid) {


    if(this->head == NULL){
      Node* new = malloc(sizeof(Node));
      new->pid = pid;
      this->head = new;
    }
    else{
        Node* runner = this->head;
        //this is ugly but essentially, I'm just checking to see if the value is already on the list and reporting 1 for error
        for(int i = 0; i < this->size; i++){
            if(runner->pid == pid){
                return 1;
            }
            runner = runner->next;
        }
        Node* new = malloc(sizeof(Node));
        new->next = this->head;
        this->head->last = new;
        this->head = new;

    }
    this->size++;
    return 0;
}
int remove(List *this, pid_t val){
    Node* temp;
    if(this->head->pid == val){
        temp = this->head;
        this->head = this->head->next;
        this->head->last = NULL;
        free(temp);
        this->size--;
        return 0;
    }
    temp = this->head->next;
    for(int i = 1; i < this->size; i++){
        if(temp->pid == val){
            temp->last->next = temp->next;
            temp->next->last = temp->last;
            free(temp);
            this->size--;
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}
