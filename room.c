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

/*
 Function:   appendRoom
  Purpose:   adds a room to a roomlist
       in:   room
       in:   roomlist
      out:   updated roomlist for room
*/
void appendRoom(RoomListType *list, RoomType *room){
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

// void addNeighbour(RoomListType *list, RoomType *r2){
//     if(list->head == NULL){
//         list->head = r2;
//         list->tail = r2;
//     } else {
//         list->tail->next = r2;
//         list->tail = r2;
//     }
// }

/*
 Function:   connectRooms
  Purpose:   connects two rooms together
       in:   room 1
       in:   room 2
      out:   updated roomlist for room1 and room2
*/
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

/*
 Function:   cleanupRoomData
  Purpose:   deallocates memory used by each data in each room
       in:   roomData
      out:   updated roomData
*/
void cleanupRoomData(RoomListType* list){
    RoomNodeType *curr, *next;

    curr = list->head;
    next = curr->next;

    while(curr->next != NULL){
        
        free(curr);
        curr = next;
        next = curr->next;

    }
    free(curr);
}

/*
 Function:   cleanupRoomList
  Purpose:   deallocates memory used by RoomList
       in:   roomlist
      out:   updated roomlist
*/
void cleanupRoomList(RoomListType *list){
    RoomNodeType *curr, *next;
    curr = list->head;
    next = curr->next;
    while(curr->next != NULL){
        cleanupRoomData(curr->data->next);
        curr = next;
        next = curr->next;
    }
    cleanupRoomData(curr->data->next);
    curr = list->head;
    next = curr->next;
    while(curr->next != NULL){
        free(curr->data->next);
        free(curr->data->evidence);
        free(curr->data);
        free(curr);
        curr = next;
        next = curr->next;

    }
    free(curr->data->next);
    free(curr->data->evidence);
    free(curr->data);
    free(curr);
    free(list);
}

void printRooms(RoomListType *list){
    RoomNodeType *curr, *next;
    curr = list->head;
    next = curr->next;
    while(curr->next != NULL){
        printf("\n%s", curr->data->name);
        curr = next;
        next = curr->next;
    }
    printf("\n%s", curr->data->name);
}

/*
 Function:   randomRoom
  Purpose:   picks a random room for the ghost to spawn in (excluding van)
       in:   room list
       in:   ghost
      out:   updated random room with ghost in it
*/
void randomRoom(RoomListType *list, GhostType *ghost){
    int stop = randInt(1,13);
    RoomNodeType *curr = list->head;
    for(int i = 1; i < 13; ++i){
        if(i == stop){
            ghost->currRoom = curr->data;
            return;
        }
        curr = curr->next;
    }
}
