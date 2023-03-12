#include "defs.h"

void initRoom(RoomType* room, char* name){
    EvidenceListType* evList = (EvidenceListType*)calloc(1,sizeof(EvidenceListType));
    room->next = (RoomListType*)calloc(1,sizeof(RoomListType));
    strcpy(room->name, name);
    initRoomList(room->next);
    initEvidenceList(evList);
    room->evidence = evList;
    room->ghost = NULL;
    room->hunterListSize = 0;
    //room->building = building;
    sem_init(&(room->mutex), 0, 1);
    
}


void initRoomList(RoomListType* list){
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/*
 Function:   appendRoom
  Purpose:   adds a room to a roomlist
       in:   room
       in:   roomlist
      out:   updated roomlist for room
*/
void appendRoom(RoomListType *list, RoomType *room){
    RoomNodeType* newNode = (RoomNodeType*) calloc(1, sizeof(RoomNodeType));
    newNode->data = room;

    //Empty
    if(list->size == 0){
        list->head = newNode;
        list->tail = newNode;
    }else{
        list->tail->next = newNode;
        list->tail = newNode;
    }
   list->size++;
}

/*
 Function:   connectRooms
  Purpose:   connects two rooms together
       in:   room 1
       in:   room 2
      out:   updated roomList for room1 and room2
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
    RoomNodeType *curr = list->head;
    RoomNodeType *next = curr->next;
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
        cleanupEvidenceList(curr->data->evidence);
        free(curr->data->evidence);
        free(curr->data);
        free(curr);
        curr = next;
        next = curr->next;
    }
    free(curr->data->next);
    cleanupEvidenceList(curr->data->evidence);
    free(curr->data->evidence);
    free(curr->data);
    free(curr);
    
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
  Purpose:   picks a random room for the ghost to spawn in (excludes van if the van parameter is set to 0)
   in/out:   room list to traverse, where one room is change to have ghost in it
   in/out:   ghost to be added to room and have room added to it
       in:   flag for whether or not the van is included in the rooms (0 if not, 1 if yes) 
*/
void randomRoom(RoomListType *list, GhostType *ghost, int van){
    if(!van){
        int stop = randInt(1, list->size);
        RoomNodeType *curr = list->head->next;
        for(int i = 1; i < list->size; ++i){
            if(i == stop){
                ghost->currRoom = curr->data;
                curr->data->ghost = ghost;
                break;
            }
            curr = curr->next;
        }
    }else{
        while(1){    
            int stop = randInt(0,list->size);
            RoomNodeType *curr = list->head;
            for(int i = 0; i < list->size; ++i){
                if(i == stop){
                    if(!(curr->data == ghost->currRoom)){
                        ghost->currRoom = curr->data;
                        curr->data->ghost = ghost;
                        return;
                    }
                    continue;
                }
                curr = curr->next;
            }
        }
    }
}


/*
 Function:   cleanupRoomList
  Purpose:   deallocates memory used by RoomList
       in:   roomlist
      out:   updated roomlist
*/
void cleanupMasterRoomList(RoomListType *list){
    RoomNodeType *curr = list->head;
    RoomNodeType *next = curr->next;
    while(curr->next != NULL){
        cleanupEvidenceList(curr->data->evidence);
        free(curr->data->evidence);
        free(curr->data->next);
        free(curr->data);
        free(curr);
        curr = next;
        next = curr->next;
    }
    cleanupEvidenceList(curr->data->evidence);
    free(curr->data->evidence);
    cleanupRoomList(curr->data->next);
    free(curr->data->next);
    free(curr->data);
    free(curr);
    
}