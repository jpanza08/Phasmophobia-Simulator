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


void switchRoomsHunter(HunterType *hunter){
    removeHunterFromRoom(hunter->room, hunter);
    RoomListType* list = hunter->room->next;
    int stop = randInt(0,list->size);
    RoomNodeType *curr = list->head;
    for(int i = 0; i < list->size; ++i){
        if(i == stop){
            hunter->room = curr->data;
            addHunterToRoom(curr->data, hunter);
            return;
        }
        curr = curr->next;
    }
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
		EvNodeType* temp = current;
        while(current != NULL) {
            if(current->data->type == hunter->reads){
                addEvidenceToHunter(hunter, current->data);
                switch(current->data->type){
                    case(EMF):
                        if(current->data->value >= 4.70 && current->data->value <= 5.00)
                            hunter->ghostlyEvidence++;
                            hunter->boredom = BOREDOM_MAX;
                        break;
                    case(TEMPERATURE):
                        if(current->data->value >= -10.0 && current->data->value <= 1.00)
                            hunter->ghostlyEvidence++;
                            hunter->boredom = BOREDOM_MAX;
                        break;
                    case(FINGERPRINTS):
                        if(current->data->value == 1.00)
                            hunter->ghostlyEvidence++;
                            hunter->boredom = BOREDOM_MAX;
                        break;
                    case(SOUND):
                        if(current->data->value >= 65.00 && current->data->value <= 75.00)
                            hunter->ghostlyEvidence++;
							hunter->boredom = BOREDOM_MAX;
                        break;
                }
                current = current->next;
				removeEvidenceRoom(hunter->room, temp);
				temp = current;
            }
        }
    } else {
		EvidenceType ev;
		float evRange;
		EvidenceEnumType evType = hunter->reads;
		switch(evType) {
			case EMF:
				evRange = randFloat(0, 5);
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
		initEvidence(evRange, evType, &ev);
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
        int random = randInt(0, hunter->room->hunterListSize + 1);
        if(strcmp(hunter->name, hunter->room->hunters[random]->name) != 0) {
            EvNodeType* current = hunter->room->evidence->head;
            while(current != NULL) {
                switch (current->data->type) {
                    case EMF:
                        if(current->data->value >= 4.7) {
                            addEvidenceToHunter(hunter->room->hunters[random], current->data);
                            hunter->room->hunters[random]->ghostlyEvidence++;
                        }
                        break;
                    case TEMPERATURE:
                        if(-10 <= current->data->value && current->data->value <= 1.0) {
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
                        if(65 <= current->data->value && current->data->value <= 75) {
                            addEvidenceToHunter(hunter->room->hunters[random], current->data);
                            hunter->room->hunters[random]->ghostlyEvidence++;
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
		}
		random = randInt(1, 4);
		switch(random){
			case(1): 
				collectEvidence(hunter);
				break;
			case(2):
				switchRoomsHunter(hunter);
				hunter->boredom--;
				break;
			case 3:
				if(hunter->room->hunterListSize > 1) {
					shareEvidence(hunter);
				}
				break;
		}

        if(hunter->ghostlyEvidence >= 3){
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


