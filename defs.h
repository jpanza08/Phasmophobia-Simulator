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

typedef enum { EMF, TEMPERATURE, FINGERPRINTS, SOUND } EvidenceEnumType;
typedef enum { POLTERGEIST, BANSHEE, BULLIES, PHANTOM } GhostClassType;


typedef struct {
  char name[MAX_STR]; // good
  GhostType* ghost;
  RoomListType* neighbours
  EvidenceListType
} RoomType;

typedef struct {
  int id;
  GhostClassType ghostType;
  RoomType *room;
  float likelihood;
} GhostType;

typedef struct RoomArray {
  // RoomType *elements[MAX_ARR];
  int size;
  int capacity;

} RoomArrayType;

typedef struct Node{
    struct Node *next;
    // Room *data;
} RoomNodeType;

typedef struct{
    RoomNodeType *head;
    RoomNodeType *tail;
} RoomListType;

typedef struct{
   struct Room *current;
    EvidenceEnumType readable;
    EvidenceType ada; //Maybe dynamic array? 
    int fear;
    int interest;

} HunterType;

typedef struct{
    float value;
    EvidenceEnumType type;
} EvidenceType;

typedef struct EvidenceNode {
  struct EvidenceNode *next;
  EvidenceType* data;
} EvidenceNodeType;

typedef struct {
  EvidenceNodeType* head;
  EvidenceNodeType* tail;
} EvidenceListType;

// You may rename these types if you wish

int randInt(int, int);          // Generates a pseudorandom integer between the parameters
float randFloat(float, float);  // Generates a pseudorandom float between the parameters

// void populateRooms(BuildingType*);   // Populates the building with sample data for rooms
void initGhost();
void initHunter();
void initRoom(char[]);
void initEvidence(float, EvidenceEnumType, EvidenceType*);
void initEvidenceList(EvidenceListType*);