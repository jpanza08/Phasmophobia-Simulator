#include "defs.h"

/*
 Function:   getGhostName
  Purpose:   gets ghostname in string
       in:   ghost enum type
      out:   string of enum
*/
const char* getGhostName(GhostEnumType name) {
    switch(name) {
        case POLTERGEIST: return "POLTERGEIST";
        case BANSHEE: return "BANSHEE";
        case PHANTOM: return "PHANTOM";
        case BULLIES: return "BULLIES";
    }
}

void initGhost(RoomType* startRoom, GhostEnumType type, GhostType* ghost){
    ghost->boredom = BOREDOM_MAX;
    ghost->currRoom = startRoom;
    ghost->type = type;
}

void leaveEvidence(RoomType* room, GhostType* ghost) {
    EvidenceType evLeft;
    float evRange;
    int randomInt = randInt(1, 3);
    EvidenceEnumType gt = randomInt;
    switch(gt) {
        case EMF:
            evRange = randFloat(0, 5.01);
            break;
        case TEMPERATURE:
            evRange = randFloat(-10, 27.01);
            break;
        case FINGERPRINTS:
            evRange = randFloat(0, 1.01);
            break;
        case SOUND:
            evRange = randFloat(40, 75.01);
            break;
    }
    initEvidence(evRange, gt, &evLeft);
    addEvidenceToRoom(room, &evLeft);
}

void* chooseGhostAction(void* ghostArg){
    GhostType* ghost = (GhostType*) ghostArg;
    int random;

    while(1){
        sleep(1);
        if(ghost->currRoom->hunterListSize != 0){
            ghost->boredom = BOREDOM_MAX;            
            random = randInt(1, 3);
            if(random == 1) {
                leaveEvidence(ghost->currRoom, ghost);
            }
        } else {
            ghost->boredom--;
            random = randInt(1, 4);
            switch(random) {
                case 1:
                    leaveEvidence(ghost->currRoom, ghost);
                    break;
                case 2:
                    switchGhostRooms(ghost);
                    break;
            }
        }
        if(ghost->boredom <= 0)
            printf("The ghost got bored and left");            
            break;
    }
    return NULL;
}


void switchGhostRooms(GhostType* ghost){
    ghost->currRoom->ghost = NULL;
	int stop = randInt(0, ghost->currRoom->next->size);
	RoomNodeType *curr = ghost->currRoom->next->head;
	for(int i = 0; i < ghost->currRoom->next->size; ++i){
		if(i == stop) {
			ghost->currRoom = curr->data;
			curr->data->ghost = ghost;
            // printf("Ghost moved into %s.\n", curr->data->name);
			break;
		}
		curr = curr->next;
	}
}