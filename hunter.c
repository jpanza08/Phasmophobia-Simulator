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

void randomRoomHunter(RoomListType *list, HunterType *hunter){
    while(1){    
            int stop = randInt(0,list->size);
            RoomNodeType *curr = list->head;
            for(int i = 0; i < list->size; ++i){
                if(i == stop){
                    if(!(curr->data == hunter->room)){
                        hunter->room = curr->data;
                        addHunterToRoom(curr->data, hunter);
                        return;
                    }
                    continue;
                }
                curr = curr->next;
            }
        }

}


void switchRoomsHunter(HunterType *hunter){
    removeHunterFromRoom(hunter->room, hunter);
    randomRoomHunter(hunter->room->next, hunter);
}

/*
 Function:   collectEvidence
  Purpose:   hunter collects evidence from their current room
       in:   hunter
      out:   updated hunter evidence
*/
void collectEvidence(HunterType *hunter){
    if(hunter->room->evidence->size != 0) {
        EvNodeType* current = hunter->room->evidence->head;
        while(current != NULL) {
            addEvidenceToHunter(hunter, current->data);
            current = current->next;
        }
    }
}

/*
 Function:   shareEvidence
  Purpose:   hunter shares evidence to other hunter in the same room
       in:   hunter
      out:   updated hunter evidence
*/
void shareEvidence(HunterType *hunter) {
    if(hunter->room->hunterListSize > 1) {
        int random = randInt(0, hunter->room->hunterListSize + 1);
        if(strcmp(hunter->name, hunter->room->hunters[random]) != 0) {
            EvNodeType* current = hunter->room->evidence->head;
            while(current != NULL) {
                switch (current->data->type) {
                    case EMF:
                        if(current->data->value >= 4.7) {
                            addEvidenceToHunter(hunter->room->hunters[random], current->data);
                        }
                        break;
                    case TEMPERATURE:
                        if(-10 <= current->data->value && current->data->value <= 1.0) {
                            addEvidenceToHunter(hunter->room->hunters[random], current->data);
                        }
                        break;
                    case FINGERPRINTS:
                        if(current->data->value == 1) {
                            addEvidenceToHunter(hunter->room->hunters[random], current->data);
                        }
                        break;
                    case SOUND:
                        if(65 <= current->data->value && current->data->value <= 75) {
                            addEvidenceToHunter(hunter->room->hunters[random], current->data);
                        }
                        break;
                }
                current = current->next;
            }
        }
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
    int random;
    //Make share evi function

    while(1){

        if(hunter->room->ghost != NULL){
            hunter->fear++;
            hunter->boredom = BOREDOM_MAX;

            if(hunter->room->hunterListSize > 1){
                shareEvidence(hunter);
            }else{
                random = randInt(1, 3);
                
                switch(random){
                    case(1): 
                        collectEvidence(hunter);
                    case(2):
                        switchRoomsHunter(hunter);
                        hunter->boredom--;
                }
            }
        }

        if(hunter->evList->size >= 3){
            break;
        } 
        if(hunter->fear >= 100){
            break;
        }
        if(hunter->boredom <= 0){
            break;
        }
    }
   pthread_exit(NULL);

}
