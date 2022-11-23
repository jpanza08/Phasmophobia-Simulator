#include "defs.h"

void initHunter(RoomType* room, EvidenceEnumType reads, int id, HunterType* h){
    EvidenceListType* evFound = (EvidenceListType*)malloc(sizeof(EvidenceListType));
    
    h->evList = evFound;
    h->room = room;
    h->reads = reads;
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

void addHunterToRoom(RoomType* room, HunterType* h) {
    int length = room->hunterListSize;
    if(length >= 4) {
        printf("\nlist is full\n");
    } else {
        room->hunters[length] = h;
        room->hunterListSize++;
    }
}

void removeHunterFromRoom(RoomType* room, HunterType* h) {
    int length = sizeof(room->hunters) / sizeof(HunterType*);
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

// void printHunter(HunterType* hunter) {
//     printf("room: %s, fear: %d, boredom: %d, id: %d", hunter->room->name, hunter->fear, hunter->boredom, hunter->id);
// }