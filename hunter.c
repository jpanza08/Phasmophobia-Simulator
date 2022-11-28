#include "defs.h"

void initHunter(RoomType* room, EvidenceEnumType reads, char* name, int id, HunterType* h){
    EvidenceListType* evFound = (EvidenceListType*)malloc(sizeof(EvidenceListType));
    
    h->evList = evFound;
    h->room = room;
    h->reads = reads;
    strcpy(h->name, name);
    h->fear = 0;
    h->boredom = BOREDOM_MAX;
    h->id = id;
}

void addEvidenceToHunter(HunterType* h, EvidenceType* ev) {
    addEvidence(h->evList, ev);
}

void printHunterEvidence(HunterType* h) {
    printEvidenceList(h->evList);
}

/*
 Function:   addHunterToRoom
  Purpose:   add hunter to a room
       in:   hunter
       in:   room
      out:   updated room with hunter
*/
void addHunterToRoom(RoomType* room, HunterType* h) {
    int length = room->hunterListSize;
    if(length >= 4) {
        printf("\nlist is full\n");
    } else {
        room->hunters[length] = h;
        room->hunterListSize++;
    }
}

/*
 Function:   removeHunterFromRoom
  Purpose:   remove hunter from a room
       in:   hunter
       in:   room
      out:   updated room without hunter
*/
void removeHunterFromRoom(RoomType* room, HunterType* h) {
    int length = room->hunterListSize;
    int index;
    if(length == 0) {
        printf("\nlist is empty\n");
    } else {
        for(int i = 0; i < length; ++i) {
            if(room->hunters[i]->id == h->id) {
                index = i;
                break;
            }
        }
        for(int i = index - 1; i < length; ++i) {
            room->hunters[i] = room->hunters[i + 1];
        }
        room->hunterListSize--;
    }
}

void cleanupHunters(HunterType* hunters){
    for(int i = 0; i < 4; ++i){
        free(hunters[i].evList);
    }

}


/*
 Function:   chooseAction
  Purpose:   functions for threads to decide what the hunter will do.
       in:   hunter
*/
void* chooseAction(void* hunterArg){
    //Need to cast void pointer into something usable
    HunterType* hunter = (HunterType*) hunterArg;  

    /* Get random number and choose action*/

}
