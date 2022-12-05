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
    printf("\n%d\n", length);
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


void switchRoomsHunter(HunterType *hunter){ // you must use try wait gl
    RoomType* roomToGo = hunter->room;
    // if(sem_trywait(&(roomToGo->mutex)) == 0) { //0 is when its not locked
        removeHunterFromRoom(hunter->room, hunter);
        // printf("\n%d size of %s\n", hunter->roomx->hunterListSize, hunter->room->name);
        RoomListType* list = hunter->room->next;
        int stop = randInt(0,list->size);
        RoomNodeType *curr = list->head;
        for(int i = 0; i < list->size; ++i){
            if(i == stop){
                hunter->room = curr->data;
                addHunterToRoom(curr->data, hunter);
                printf("%s moved into %s.\n", hunter->name, curr->data->name);
                return;
            }
            curr = curr->next;
        }
    // }
}

/*
 Function:   collectEvidence
  Purpose:   hunter collects evidence from their current room
       in:   hunter
      out:   updated hunter evidence
*/
void collectEvidence(HunterType *hunter){
    if(hunter->room->evidence->size != 0) { //Is there even evidence to collect?
        EvNodeType* current = hunter->room->evidence->head;
		EvNodeType* temp = current;
        while(current != NULL) {
            if(current->data->type == hunter->reads){
                addEvidenceToHunter(hunter, current->data);
                printf("Added %s to Hunter\n", getEvidenceName(current->data->type));
                hunter->ghostlyEvidence++;
                hunter->boredom = BOREDOM_MAX;
                current = current->next;
                removeEvidenceRoom(hunter->room, temp->data);
                temp = current;
            } else {
                current = current->next;
            }
        }
    } else {
		EvidenceType ev;
		float evRange;
		EvidenceEnumType evType = hunter->reads;
		switch(evType) {
			case EMF:
				evRange = randFloat(0, 4.9);
				break;
			case TEMPERATURE:
				evRange = randFloat(0, 27);
				break;
			case FINGERPRINTS:
				evRange = randFloat(0, 1);
				break;
			case SOUND:
				evRange = randFloat(40, 70);
				break;
    	}
		initEvidence(evRange, evType, 0, &ev);
		addEvidenceToHunter(hunter, &ev);
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
        sem_wait(&(currentRoom->mutex));
        if(hunter->room->ghost != NULL){
            hunter->fear++;
            hunter->boredom = BOREDOM_MAX;
		}
		random = randInt(1, 4);
		switch(random){
			case(1):
                printf("\n%s is collecting evidence in %s\n", hunter->name, hunter->room->name);
				// collectEvidence(hunter);
				break;
			case(2):
                printf("\n%s is switching rooms in %s\n", hunter->name, hunter->room->name);
				switchRoomsHunter(hunter);
				hunter->boredom--;
				break;
			case 3:
				if(hunter->room->hunterListSize > 1) {
                    printf("\n%s is sharing evidence in %s\n", hunter->name, hunter->room->name);
					shareEvidence(hunter);
				}
				break;
		}
        sem_post(&(currentRoom->mutex));

        if(hunter->ghostlyEvidence >= 3){
            printf("%s got enough evidence to leave.\n", hunter->name);
            break;
        } 
        if(hunter->fear >= 100){
            printf("%s got too scared and left!\n", hunter->name);
            break;
        }
        if(hunter->boredom <= 0){
            printf("%s got bored and left\n", hunter->name);
            break;
        }
        usleep(USLEEP_TIME);
    }

    return 0;
}