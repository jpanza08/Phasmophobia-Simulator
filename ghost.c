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

void* chooseGhostAction(void* ghostArg){
    //Need to cast void pointer into something usable
    GhostType* ghost = (GhostType*) ghostArg;

    while(1){

        if(ghost->currRoom->hunterListSize != 0){

            ghost->boredom = BOREDOM_MAX;
            //Can't move
            
            //Leave evidence or do nothing


        }else{
            ghost->boredom--;

            //Randomly choose to leave, drop evi, or do nothing.
                //If moving rooms, update ghost room pointer and room ghost pointer.
                //If leaving evidence, make new evi structure and add it to room's evidence
                    //Randomly select evidence type based on ghost type.
                    //Randomly generate value within evidence range


        }

        if(ghost->boredom <= 0)
            break; //How to break a thread?
    
        

    }


}