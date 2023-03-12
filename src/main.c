#include "defs.h"

int main(int argc, char *argv[])
{
    // Initialize a random seed for the random number generators
    srand(time(NULL));
   
    GhostType gh;
    HunterType hunter1, hunter2, hunter3, hunter4;
    BuildingType building;
    char name1[MAX_STR], name2[MAX_STR], name3[MAX_STR], name4[MAX_STR];
    pthread_t hunter1Thread, hunter2Thread, hunter3Thread, hunter4Thread, ghostThread;
    int allScared = 0;
    //Building initialization
    initBuilding(&gh, &building);
    populateRooms(&building);
    //Creating ghost
    initGhost(NULL, randInt(0,4), &gh);
    

    randomRoom(building.rooms, &gh, 0); //Giving ghost random room
    printf("\nGhost is a: %s, and is in room: %s\n", getGhostName(gh.type, &gh), gh.currRoom->name);

    //Initializing hunters
    printf("\nEnter the first Hunter's name: ");
    scanf("%s", name1);
    initHunter(building.rooms->head->data, FINGERPRINTS, name1, 1, &hunter1);
    addHunterToBuilding(&hunter1, &building);
   
    printf("Enter the second Hunter's name: ");
    scanf("%s", name2);
    initHunter(building.rooms->head->data, EMF, name2, 2, &hunter2);
    addHunterToBuilding(&hunter2, &building);


    printf("Enter the third Hunter's name: ");
    scanf("%s", name3);
    initHunter(building.rooms->head->data, TEMPERATURE, name3, 3, &hunter3);
    addHunterToBuilding(&hunter3, &building);
    
    printf("Enter the fourth Hunter's name: ");
    scanf("%s", name4);
    initHunter(building.rooms->head->data, SOUND, name4, 4, &hunter4);
    addHunterToBuilding(&hunter4, &building);


    // //Adding hunters to rooms
    addHunterToRoom(building.rooms->head->data, &hunter1);
    addHunterToRoom(building.rooms->head->data, &hunter2);
    addHunterToRoom(building.rooms->head->data, &hunter3);
    addHunterToRoom(building.rooms->head->data, &hunter4);

    //Creating threads
    pthread_create(&ghostThread, NULL, chooseGhostAction, &gh);
    pthread_create(&hunter1Thread, NULL, chooseAction, &hunter1);
    pthread_create(&hunter2Thread, NULL, chooseAction, &hunter2);
    pthread_create(&hunter3Thread, NULL, chooseAction,  &hunter3);
    pthread_create(&hunter4Thread, NULL, chooseAction, &hunter4);
    
    //Cleanup stuff
    pthread_join(ghostThread, NULL);
    pthread_join(hunter1Thread, NULL);
    pthread_join(hunter2Thread, NULL);
    pthread_join(hunter3Thread, NULL);
    pthread_join(hunter4Thread, NULL);

    
    printf("\n-------");
    printf("\n%s has %d evidences, %d ghostly evidences, is %d scared, and %d bored.", hunter1.name, hunter1.evList->size, hunter1.ghostlyEvidence, hunter1.fear, hunter1.boredom);
    printf("\n%s has %d evidences, %d ghostly evidences, is %d scared, and %d bored.", hunter2.name, hunter2.evList->size, hunter2.ghostlyEvidence, hunter2.fear, hunter2.boredom);
    printf("\n%s has %d evidences, %d ghostly evidences, is %d scared, and %d bored.", hunter3.name, hunter3.evList->size, hunter3.ghostlyEvidence, hunter3.fear, hunter3.boredom);
    printf("\n%s has %d evidences, %d ghostly evidences, is %d scared, and %d bored.", hunter4.name, hunter4.evList->size, hunter4.ghostlyEvidence, hunter4.fear, hunter4.boredom);
    printf("\n-------");

    int ctr = 0;
    if(hunter1.fear >= 100) {
        printf("\n%s got scared with a %d fear", hunter1.name, hunter1.fear);
        ctr++;
    }
    if(hunter2.fear >= 100) {
        printf("\n%s got scared with a %d fear", hunter2.name, hunter2.fear);
        ctr++;
    }
    if(hunter3.fear >= 100) {
        printf("\n%s got scared with a %d fear", hunter3.name, hunter3.fear);
        ctr++;
    }
    if(hunter4.fear >= 100) {
        printf("\n%s got scared with a %d fear", hunter4.name, hunter4.fear);
        ctr++;
    }
    printf("\n-------");

    if(ctr == 4) {
        printf("\nGhost is a: %s, and has won the game.\n", getGhostName(gh.type, &gh));
    } else {
        int hunterFoundGhost;
        findGhost(*(building.hunters), &hunterFoundGhost);
        printf("\nGhost was a %s and the hunters guessed %s\nHunters have won", getGhostName(gh.type, &gh), getGhostName(hunterFoundGhost, &gh));
    } 
    
    cleanupHunters(&hunter1);
    cleanupHunters(&hunter2);
    cleanupHunters(&hunter3);
    cleanupHunters(&hunter4);

    cleanupBuilding(&building);
    printf("\nSimulation complete.\n");

    
    return C_OK;
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