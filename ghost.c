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
    if(sem_trywait(&(room->mutex)) != 0){
        return;
    }
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
            evRange = randFloat(EMF_MIN_GHOST, EMF_MAX_GHOST);
            
            break;
        case TEMPERATURE:
            evRange = randFloat(TEMP_MIN_GHOST, TEMP_MAX_GHOST);
            break;
        case FINGERPRINTS:
            evRange = FINGERPRINT_GHOST;
            break;
        case SOUND:
            evRange = randFloat(SOUND_MIN_GHOST, SOUND_MAX_GHOST);
            break;
    }
    initEvidence(evRange, et, 1, &evLeft);
    addEvidenceToRoom(room, &evLeft);
    sem_post(&(room->mutex));
}

void* chooseGhostAction(void* ghostArg){
    GhostType* ghost = (GhostType*) ghostArg;
    int random;
    while(1){
        RoomType* currentRoom = ghost->currRoom;
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
        if(ghost->boredom <= 0) {
            printf("The ghost got bored and left.\n");            
            ghost->currRoom->ghost = NULL;
            break;
        }
        // usleep(USLEEP_TIME);
    }
    return 0;
}

/*
 Function:   switchGhostRooms
  Purpose:   switches room that the hunter is currently in
       in:   hunter
      out:   updated hunter room
*/
void switchGhostRooms(GhostType* ghost){
    RoomType* current = ghost->currRoom;
    RoomType* destination = NULL;
    RoomListType* list = ghost->currRoom->next;
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
        if (sem_trywait(&(ghost->currRoom->mutex)) == 0) {
            // If the new room is *not* available for modification, unlock the hunter's room and return nothing
            if(sem_trywait(&(destination->mutex)) != 0) {
                // We must remember to unlock the locked current room
                sem_post(&(ghost->currRoom->mutex));
                return;
            }
        }
        //If we make it here, the current and next rooms are locked
        ghost->currRoom->ghost = NULL;
        ghost->currRoom = destination;
        destination->ghost = ghost;
        printf("Ghost moved into %s.\n", destination->name);
        

        sem_post(&(current->mutex));
        sem_post(&(ghost->currRoom->mutex));

}