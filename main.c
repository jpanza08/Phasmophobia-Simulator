#include "defs.h"

int main(int argc, char *argv[])
{
    // Initialize a random seed for the random number generators
    srand(time(NULL));
   
   
    GhostType gh;
    HunterType hunter1, hunter2, hunter3, hunter4;
    BuildingType building;
    char name1[MAX_STR], name2[MAX_STR], name3[MAX_STR], name4[MAX_STR];
    pthread_t hunter1, hunter2, hunter3, hunter4, ghost;
    
    //Building initialization
    initBuilding(&gh, &building);
    populateRooms(&building);
    
    //Creating ghost
    initGhost(NULL, randInt(0,4), &gh);
    randomRoom(building.rooms, &gh); //Giving ghost random room

    

    //Initializing hunters
    printf("Enter the first Hunter's name: ");
    scanf("%s", name1);
    initHunter(building.rooms->head->data, FINGERPRINTS, name1, 1, &hunter1);
    printf("Enter the second Hunter's name: ");
    scanf("%s", name2);
    initHunter(building.rooms->head->data, EMF, name2, 2, &hunter2);
    printf("Enter the third Hunter's name: ");
    scanf("%s", name3);
    initHunter(building.rooms->head->data, TEMPERATURE, name3, 3, &hunter3);
    printf("Enter the fourth Hunter's name: ");
    scanf("%s", name4);
    initHunter(building.rooms->head->data, SOUND, name4, 4, &hunter4);

    addHunterToRoom(building.rooms->head->data, &hunter1);
    addHunterToRoom(building.rooms->head->data, &hunter2);
    addHunterToRoom(building.rooms->head->data, &hunter3);
    addHunterToRoom(building.rooms->head->data, &hunter4);

    


    
    cleanupBuilding(&building);

    
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