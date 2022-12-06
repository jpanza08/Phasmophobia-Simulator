#include "defs.h"

void initHunter(RoomType* room, EvidenceEnumType reads, char* name, int id, HunterType* h){
    EvidenceListType* evFound = (EvidenceListType*)malloc(sizeof(EvidenceListType));
    
    h->evList = evFound;
    h->room = room;
    h->reads = reads;
    strcpy(h->name, name);
    h->fear = 0;
    h->boredom = 6;
    h->id = id;
    h->ghostlyEvidence = 0;
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
    } else if(length == 1) {
        room->hunters[0] = NULL;
        room->hunterListSize--;
    } else {
        for(int i = 0; i < length; ++i) {
            if(room->hunters[i]->id == h->id) {
                index = i;
                break;
            }
        }
        for(int i = index; i < length - 1; ++i) {
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


void switchRoomsHunter(HunterType *hunter){ 
    RoomType* current = hunter->room;
    RoomType* destination = NULL;
    RoomListType* list = hunter->room->next;
    RoomNodeType *curr = list->head;
   
    int stop = randInt(0,list->size);
   

    for(int i = 0; i < list->size; ++i){
            if(i == stop){
                destination = curr->data;
                break;
            }
            curr = curr->next;
    }

        // If the hunter's room is available for modification, lock it
        if (sem_trywait(&(hunter->room->mutex)) == 0) {
            // If the new room is *not* available for modification, unlock the hunter's room and return nothing
            if(sem_trywait(&(destination->mutex)) != 0) {
                // We must remember to unlock the locked current room
                sem_post(&(hunter->room->mutex));
                return;
            }
        }
        //If we make it here, the current and next rooms are locked
        removeHunterFromRoom(hunter->room, hunter);
        hunter->room = destination;
        addHunterToRoom(destination, hunter);
        printf("%s moved into %s.\n", hunter->name, destination->name);
        

        sem_post(&(current->mutex));
        sem_post(&(hunter->room->mutex));
}

/*
 Function:   collectEvidence
  Purpose:   hunter collects evidence from their current room
       in:   hunter
      out:   updated hunter evidence
*/
void collectEvidence(HunterType *hunter){
    if(sem_trywait(&(hunter->room->mutex)) != 0){
        return;
    }
    int evFlag = 0;   
    int evRange; 
    EvNodeType *curr =  hunter->room->evidence->head;
    EvNodeType *prev = curr; 
    EvidenceType leftEvidence;
    while(curr != NULL){
        if(curr->data->type == hunter->reads){
            addEvidenceToHunter(hunter, curr->data);
            printf("%s collected evidence from %s.\n", hunter->name, hunter->room->name);
            prev->next = curr->next;
            evFlag = 1;
            break;

        }

        prev = curr;
        curr = curr->next;


    }

    if(!evFlag){
        switch(hunter->reads) {
        case EMF:
            evRange = randFloat(4.7, 5);
            break;
        case TEMPERATURE:
            evRange = randFloat(-10, 27);
            break;
        case FINGERPRINTS:
            evRange = 1;
            break;
        case SOUND:
            evRange = randFloat(40, 75);
            break;
        }
        initEvidence(evRange, hunter->reads, 0, &leftEvidence);
        //Not sure what to do here. 
    
    }
    sem_post(&(hunter->room->mutex));
}

/*
 Function:   shareEvidence
  Purpose:   hunter shares evidence to other hunter in the same room
       in:   hunter
      out:   updated hunter evidence
*/
void shareEvidence(HunterType *hunter) {
    if(hunter->room->hunterListSize > 1) {
        int random = randInt(0, hunter->room->hunterListSize);
        if(strcmp(hunter->name, hunter->room->hunters[random]->name) != 0) {
            EvNodeType* current = hunter->room->evidence->head;
            while(current != NULL) {
                switch (current->data->type) {
                    case EMF:
                        if(current->data->value >= 4.9) {
                            addEvidenceToHunter(hunter->room->hunters[random], current->data);
                            hunter->room->hunters[random]->ghostlyEvidence++;
                        }
                        break;
                    case TEMPERATURE:
                        if(-10 <= current->data->value && current->data->value <= 0) {
                            addEvidenceToHunter(hunter->room->hunters[random], current->data);
                            hunter->room->hunters[random]->ghostlyEvidence++;
                        }
                        break;
                    case FINGERPRINTS:
                        if(current->data->value == 1) {
                            addEvidenceToHunter(hunter->room->hunters[random], current->data);
                            hunter->room->hunters[random]->ghostlyEvidence++;
                        }
                        break;
                    case SOUND:
                        if(70 <= current->data->value) {
                            addEvidenceToHunter(hunter->room->hunters[random], current->data);
                            hunter->room->hunters[random]->ghostlyEvidence++;
                        }
                        break;
                }
                current = current->next;
            }
            // printf("%s shared %s with %s.\n", hunter->room->hunters[random]->name, getEvidenceName(hunter->evList->tail->data->type), hunter->name);

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
        RoomType* currentRoom = hunter->room;
        if(hunter->room->ghost != NULL){
            hunter->fear++;
            hunter->boredom = BOREDOM_MAX;
		}
		random = randInt(1, 4);
		switch(random){
			case(1):
                printf("%s is collecting evidence in %s\n", hunter->name, hunter->room->name);
				collectEvidence(hunter);
				break;
			case(2):
                printf("%s is switching rooms in %s\n", hunter->name, hunter->room->name);
				switchRoomsHunter(hunter);
				hunter->boredom--;
				break;
			case 3:
				if(hunter->room->hunterListSize > 1) {
                    printf("%s is sharing evidence in %s\n", hunter->name, hunter->room->name);
					shareEvidence(hunter);
				}
				break;
		}
        

        if(hunter->ghostlyEvidence >= 3){
            printf("%s got enough evidence to leave.\n", hunter->name);
            removeHunterFromRoom(hunter->room, hunter);
            // sem_wait(&(hunter->building->mutex));
            // hunter->building->hunterListSize--;
            // sem_post(&(hunter->building->mutex));
            break;
        } 
        if(hunter->fear >= 100){
            printf("%s got too scared and left!\n", hunter->name);
            removeHunterFromRoom(hunter->room, hunter);
            // sem_wait(&(hunter->building->mutex));
            // hunter->building->hunterListSize--;
            // sem_post(&(hunter->building->mutex));
            break;
        }
        if(hunter->boredom <= 0){
            printf("%s got bored and left\n", hunter->name);
            removeHunterFromRoom(hunter->room, hunter);
            // sem_wait(&(hunter->building->mutex));
            // hunter->building->hunterListSize--;
            // sem_post(&(hunter->building->mutex));
            break;
        }
        usleep(USLEEP_TIME);
    }
    return 0;
}