#include "defs.h"


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
