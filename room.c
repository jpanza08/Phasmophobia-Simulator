#include "defs.h"

void initRoom(RoomType* room, char* name){
    RoomListType* roomList = (RoomListType*)malloc(sizeof(RoomListType));
    EvidenceListType* evList = (EvidenceListType*)malloc(sizeof(EvidenceListType));

    strcpy(room->name, name);
    initRoomList(roomList);
    initEvidenceList(evList);
    room->evidence = evList;
    room->next = roomList;
    room->ghost = NULL;
    room->hunterListSize = 0;
}

void initRoomList(RoomListType* list){
    list->head = NULL;
    list->tail = NULL;
}

void appendRoom(RoomListType *list, RoomType *room){
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

void connectRooms(RoomType *r1, RoomType* r2){
    appendRoom(r1->next, r2);
    appendRoom(r2->next, r1);

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

//Frees neighbor lists of rooms first
void cleanupRoomData(RoomListType* list){
    RoomNodeType *curr, *next;

    curr = list->head;
    next = curr->next;

    while(curr->next != NULL){
        free(curr);
        curr = next;
        next = curr->next;

    }

    //TODO: Fix memory leaks
}

void cleanupRoomList(RoomListType *list){
    RoomNodeType *curr, *next;
    curr = list->head;
    next = curr->next;

    while(curr->next != NULL){
        cleanupRoomData(curr->data->next);
        //TODO: Seg fault in trying to cleanup a room's neighbors linked list. Just the nodes
        free(curr);
        curr = next;
        next = curr->next;
        
    }
    
    
    
}

