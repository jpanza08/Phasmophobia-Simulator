#include "defs.h"

void initHunter(RoomType* room, EvidenceEnumType reads, int id, HunterType* h){
    h->room = room;
    h->reads = reads;
    h->fear = 0;
    h->boredom = BOREDOM_MAX;
    h->id = id;
    
}

void initHunterList(HunterListType* list){
    list->head = NULL;
    list->tail = NULL;
}

void addHunter(HunterListType* list, HunterType* h){
    HunterNodeType *newNode = (HunterNodeType*) malloc(sizeof(HunterNodeType));
    newNode->data = h;

    if(list->head == NULL ){
        list->head = newNode;
        list->tail = newNode;
        return;
    }else{
        list->tail->next = newNode;
        list->tail = newNode;

    }

}

void removeHunter(HunterListType* list, HunterType* h){
    HunterNodeType *curr, *prev;

    //Maybe edge case, but not needed I don't think
    //We should be in control of everything
       if(list->head->next == NULL){
        list->head = list->tail = NULL;
        return;
        
       }

    curr = list->head;
    prev = curr;
    
 
    while(curr->next != NULL){
        if(curr->data->id == h->id){
            
            //Check for updating tail

            prev->next = curr->next;
            free(curr);
        }

        prev = curr;
        curr = curr->next;

    }
    
    

}