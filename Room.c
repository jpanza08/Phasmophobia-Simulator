#include "defs.h"

void initRoom(char* name, GhostType* ghost, RoomType* room){

    strcpy(room->name, name);
    initRoomList(room->next);
    initEvidenceList(room->evidence);
    initHunterArray(room->hunters);

    room->ghost = ghost;

}

void initRoomList(RoomListType* list){
    list->head = NULL;
    list->tail = NULL;


}

void addRoom(RoomListType *list, RoomType *room){
    RoomNodeType* newNode = (RoomNodeType*) malloc(sizeof(RoomNodeType));
    newNode->data = room;

    //Empty
    if(list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
    }else{
        list->tail->next = newNode;
        list->tail = newNode;

    }

}


void cleanupRoomList(RoomListType *list){
    RoomNodeType *curr, *next;
    
    if(list->head == NULL)
        return;
    if(list->head == list->tail){
        free(list->head);
        return;
    }

    curr = list->head;
    next = curr;
    
    while(curr->next != NULL){
        next = curr->next;
        free(curr);
        curr = next;

    }

    free(curr);
}

