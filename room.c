#include "defs.h"

void initRoom(char* name, GhostType* ghost, RoomType* room){
    RoomListType* roomList = (RoomListType*)malloc(sizeof(RoomListType));
    EvidenceListType* evList = (EvidenceListType*)malloc(sizeof(EvidenceListType));

    strcpy(room->name, name);
    initRoomList(roomList);
    initEvidenceList(evList);
    room->evidence = evList;
    room->next = roomList;
    room->ghost = ghost;
    room->hunterListSize = 0;
}

void initRoomList(RoomListType* list){
    list->head = NULL;
    list->tail = NULL;
}

void addListRoom(RoomListType *list, RoomType *room){
    RoomNodeType* newNode = (RoomNodeType*) malloc(sizeof(RoomNodeType));
    newNode->data = room;

    //Empty
    if(list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void printHunterList(RoomType* room) {
    int length = room->hunterListSize;
    if(length != 0) {
        printf("\n");
        for(int i = 0; i < length; ++i) {
            printf("Hunter id: %d ", room->hunters[i]->id);
        }
        printf("\n");
    } else {
        printf("\nList is empty.\n");
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

