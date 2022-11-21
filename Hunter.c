#include "defs.h"

void initHunter(RoomType* room, EvidenceEnumType reads, HunterType* h){
    h->room = room;
    h->reads = reads;
    h->fear = 0;
    h->boredom = BOREDOM_MAX;
    
}

void initHunterArray(HunterType* h){



}