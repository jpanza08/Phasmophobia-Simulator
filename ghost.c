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
    int randomint = randInt(1, 4);
    EvidenceEnumType gt = randomint;

    switch(gt) {
        case EMF:
            evRange = randFloat(0, 5);
            break;
        case TEMPERATURE:
            evRange = randFloat(-10, 27);
            break;
        case FINGERPRINTS:
            evRange = randFloat(0, 1);
            break;
        case SOUND:
            evRange = randFloat(40, 75);
            break;
    }
    initEvidence(evRange, gt, &evLeft);
    addEvidence(room->evidence, &evLeft);
}

void* chooseGhostAction(void* ghostArg){
    GhostType* ghost = (GhostType*) ghostArg;
    int random;

    while(1){
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
                    //josh add moveRoom function
            }
            //Randomly choose to leave, drop evi, or do nothing.
                //If moving rooms, update ghost room pointer and room ghost pointer.
                //If leaving evidence, make new evi structure and add it to room's evidence
                    //Randomly select evidence type based on ghost type.
                    //Randomly generate value within evidence range


        }
        if(ghost->boredom <= 0)
            break; //How to break a thread?
    }
    pthread_exit(NULL);
}