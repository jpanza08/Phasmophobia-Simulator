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
typedef enum { POLTERGEIST, BANSHEE, BULLIES, PHANTOM } GhostEnumType;

//Types
typedef struct {
  char name[MAX_STR]; // good
  GhostType* ghost;
  RoomListType* next;
  EvidenceListType* evidence;
  HunterArray hunters[4];
} RoomType;

typedef struct {
  GhostEnumType type;
  RoomType *currRoom;
  int boredom;

} GhostType;

typedef struct{
    RoomType *room;
    EvidenceEnumType reads;
    EvidenceListType *found;
    int fear;
    int boredom;

} HunterType;

typedef struct{
    float value;
    EvidenceEnumType type;
} EvidenceType;


//Lists
typedef struct{
    RoomNodeType *head;
    RoomNodeType *tail;
} RoomListType;

typedef struct {
  EvNodeType *head;
  EvNodeType *tail;
} EvidenceListType;

typdef struct {
  int capacity;
  int size;
  HunterType **elements;
  
}HunterArray;



//Nodes
typedef struct Node{
    struct Node *next;
    RoomType *data;
} RoomNodeType;

typedef struct EvidenceNode {
  struct EvidenceNode *next;
  EvidenceType* data;
} EvNodeType;


// You may rename these types if you wish

int randInt(int, int);          // Generates a pseudorandom integer between the parameters
float randFloat(float, float);  // Generates a pseudorandom float between the parameters

// void populateRooms(BuildingType*);   // Populates the building with sample data for rooms
void initGhost();
void initHunter();
void initRoom(char[]);

void initEvidence(float, EvidenceEnumType, EvidenceType*);
void initEvidenceList(EvidenceListType*);
void addEvidence(EvidenceListType*, EvidenceType*);
void cleanupEvidenceList(EvidenceListType*);

void initRoom(char*, RoomListType*, EvidenceListType*, HunterArrayType*, GhostType*, RoomType*);
void initRoomList(RoomListType* arr);
void addRoom(RoomListType *list, RoomType *room);
void cleanupRoomList(RoomTypeList *list);

void initHunter(RoomType*, EvidenceEnumType, HunterType*);
void initHunterArray(HunterType*);