
#include "defs.h"

/*
    Note: While this function is provided, you will likely want
    to modify it to suit your solution. This has been provided
    to give you a starting point to lay out the room connectivity,
    but it is entirely possible that you will want to use different
    data structures to represent the rooms and their connectivity,
    or different function names.

    Not following this function's structure exactly will not result
    in a deduction of points.

    The map that this is recreating is visible in the assignment
    specification, and also available by the original creator here:
    https://steamcommunity.com/sharedfiles/filedetails/?id=2251267947
    
*/

void initBuilding(GhostType *ghost,BuildingType *b){
    RoomListType* roomList = (RoomListType*)malloc(sizeof(RoomListType));

    b->ghost = ghost;
    b->rooms = roomList;
    b->hunterListSize = 0;
}

void addHunterToBuilding(HunterType* hunter, BuildingType* b){
    b->hunters[b->hunterListSize] = hunter;
    b->hunterListSize++;
}

/*
 Function:   cleanupBuilding
  Purpose:   deallocates memory used by building
       in:   building
      out:   updated building
*/
void cleanupBuilding(BuildingType* building){
    cleanupRoomList(building->rooms);
}



void populateRooms(BuildingType* building) {
    // First, create each room. Perhaps you want to include more data 
    // in the init parameters?
    RoomType* van = calloc(1, sizeof(RoomType));
    initRoom(van, "Van");
    RoomType* hallway = calloc(1, sizeof(RoomType));
    initRoom(hallway, "Hallway");
    RoomType* master_bedroom = calloc(1, sizeof(RoomType));
    initRoom(master_bedroom, "Master Bedroom");
    RoomType* boys_bedroom = calloc(1, sizeof(RoomType));
    initRoom(boys_bedroom, "Boy's Bedroom");
    RoomType* bathroom = calloc(1, sizeof(RoomType));
    initRoom(bathroom, "Bathroom");
    RoomType* basement = calloc(1, sizeof(RoomType));
    initRoom(basement, "Basement");
    RoomType* basement_hallway = calloc(1, sizeof(RoomType));
    initRoom(basement_hallway, "Basement Hallway");
    RoomType* right_storage_room = calloc(1, sizeof(RoomType));
    initRoom(right_storage_room, "Right Storage Room");
    RoomType* left_storage_room = calloc(1, sizeof(RoomType));
    initRoom(left_storage_room, "Left Storage Room");
    RoomType* kitchen = calloc(1, sizeof(RoomType));
    initRoom(kitchen, "Kitchen");
    RoomType* living_room = calloc(1, sizeof(RoomType));
    initRoom(living_room, "Living Room");
    RoomType* garage = calloc(1, sizeof(RoomType));
    initRoom(garage, "Garage");
    RoomType* utility_room = calloc(1, sizeof(RoomType));
    initRoom(utility_room, "Utility Room");

//     // Now create a linked list of rooms using RoomNodeType in the Building
    
    appendRoom(building->rooms, van);
    appendRoom(building->rooms, hallway);
    appendRoom(building->rooms, master_bedroom);
    appendRoom(building->rooms,boys_bedroom);
    appendRoom(building->rooms, bathroom);
    appendRoom(building->rooms, basement);
    appendRoom(building->rooms,basement_hallway);
    appendRoom(building->rooms, right_storage_room);
    appendRoom(building->rooms, left_storage_room);
    appendRoom(building->rooms, kitchen);
    appendRoom(building->rooms, living_room);
    appendRoom(building->rooms, garage);
    appendRoom(building->rooms, utility_room);

//     // Building->rooms might be a linked list structre, or maybe just a node.

//     // Now connect the rooms. It is possible you do not need a separate
//     // function for this, but it is provided to give you a starting point.
   
   
    connectRooms(van, hallway);
    connectRooms(hallway, master_bedroom);
    connectRooms(hallway, boys_bedroom);
    connectRooms(hallway, bathroom);
    connectRooms(hallway, kitchen);
    connectRooms(hallway, basement);
    connectRooms(basement, basement_hallway);
    connectRooms(basement_hallway, right_storage_room);
    connectRooms(basement_hallway, left_storage_room);
    connectRooms(kitchen, living_room);
    connectRooms(kitchen, garage);
    connectRooms(garage, utility_room);
}