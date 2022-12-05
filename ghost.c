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
    EvidenceEnumType et; //case for ghost type

    switch(ghost->type) {
        case POLTERGEIST:
            et = randInt(0, 3);
            break;
        case BULLIES:
            et = randInt(1, 4);
            if(et == 1) et--;
            break;
        case BANSHEE:
            et = randInt(0, 3);
            if(et == 2) et++;
            break;
        case PHANTOM:
            et = randInt(1, 4);
            break;
    }

    switch(et) {
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
    initEvidence(evRange, et, 1, &evLeft);
    addEvidenceToRoom(room, &evLeft);
}

void* chooseGhostAction(void* ghostArg){
    GhostType* ghost = (GhostType*) ghostArg;
    int random;
    while(1){
        RoomType* currentRoom = ghost->currRoom;
        sem_wait(&(currentRoom->mutex));
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
        sem_post(&(currentRoom->mutex));
        if(ghost->boredom <= 0) {
            printf("The ghost got bored and left");            
            break;
        }
        usleep(USLEEP_TIME);
    }

    return 0;
}


void switchGhostRooms(GhostType* ghost){ // try wait bs gl
    RoomType* roomToGo;
    ghost->currRoom->ghost = NULL;
    if(ghost->currRoom->next->size == 1) {
        roomToGo = ghost->currRoom->next->head->data;
    }

	int stop = randInt(0, ghost->currRoom->next->size);
	RoomNodeType *curr = ghost->currRoom->next->head;

	for(int i = 0; i < ghost->currRoom->next->size; ++i){
		if(i == stop) {
			roomToGo = curr->data;
			break;
		}
		curr = curr->next;
	}
    if(sem_trywait(&(roomToGo->mutex)) == 0) { //0 is when its not locked
        ghost->currRoom = roomToGo;
        ghost->currRoom->ghost = ghost;
        sem_post(&(roomToGo->mutex));
    }
    // ghost->currRoom = roomToGo;
    // ghost->currRoom->ghost = ghost;
    printf("Ghost moved into %s.\n", ghost->currRoom->name);

}