#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_STR            64
#define FEAR_RATE           1
#define MAX_FEAR          100
#define MAX_HUNTERS         4
#define USLEEP_TIME     50000
#define BOREDOM_MAX        99

typedef struct {
  int id;
  char name[MAX_STR];
  struct GhostList *ghosts;

} RoomType;

typedef struct {
  int id;
  GhostEnumType ghostType;
  RoomType *room;
  float likelihood;

} GhostType;

typedef struct RoomArray {
  RoomType *elements[MAX_ARR];
  int size;
  int capacity;

} RoomArrayType;

typedef struct Node{
    struct Node *next;
    Room *data;

}RoomNode;

typedef struct{
    RoomNode *head;
    RoomNode *tail;

}RoomList;

typedef struct{
   struct Room *current;
    EvidenceClassType readable;
    EvidenceType //Maybe dynamic array?
    int fear;
    int interest;

}HunterType;

typedef struct{
    float value;
    EvidenceClassType type;

}EvidenceType

// You may rename these types if you wish
typedef enum { EMF, TEMPERATURE, FINGERPRINTS, SOUND } EvidenceClassType;
typedef enum { POLTERGEIST, BANSHEE, BULLIES, PHANTOM } GhostClassType;

int randInt(int, int);          // Generates a pseudorandom integer between the parameters
float randFloat(float, float);  // Generates a pseudorandom float between the parameters

void populateRooms(BuildingType*);   // Populates the building with sample data for rooms
void initGhost();
void initHunter();
void initRoom();