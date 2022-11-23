#include "defs.h"

int main(int argc, char *argv[])
{
    // Initialize a random seed for the random number generators
    // srand(time(NULL));
    // You may change this code; this is for demonstration purposes
    // HunterType bill;

    RoomType ro;
    RoomListType roomList;
    GhostType gh;
    HunterType hunter;
    EvidenceType ev;
    
    initEvidence(13.23, EMF, &ev);

    initGhost(&ro, POLTERGEIST, &gh);
    printf("%s", getGhostName(gh.type));
    initRoom("Kitchen", &gh, &ro);
    printf("\n%s", getGhostName(ro.ghost->type));
    
    initHunter(&ro, EMF, 1, &hunter);
    addHunterToRoom(&ro, &hunter);
    printHunterList(&ro);
    addEvidenceToHunter(&hunter, &ev);
    printHunterEvidence(&hunter);
    // printf("\n%f", hunter.evList->head->data->value);
    printf("\n%f", hunter.evList->tail->data->value);


    return 0;
}


/*
  Function:  randInt
  Purpose:   returns a pseudo randomly generated number, 
             in the range min to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [min, max-1) 
*/
int randInt(int min, int max)
{
    return rand() % (max - min) + min;
}

/*
  Function:  randFloat
  Purpose:   returns a pseudo randomly generated number, 
             in the range min to max, inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1) 
*/
float randFloat(float a, float b) {
    // Get a percentage between rand() and the maximum
    float random = ((float) rand()) / (float) RAND_MAX;
    // Scale it to the range we want, and shift it
    return random * (b - a) + a;
}