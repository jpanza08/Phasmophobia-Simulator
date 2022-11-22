#include "defs.h"

void initGhost(RoomType* startRoom, GhostEnumType type, GhostType *ghost){
    ghost->boredom = BOREDOM_MAX;
    ghost->currRoom = startRoom;
    ghost->type = type;

}

