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
  GhostEnumType type;
  struct RoomType *currRoom;
  int boredom;

} GhostType;

typedef struct RoomType {
  char name[MAX_STR]; // good
  GhostType* ghost;
  struct RoomListType* next;
  struct EvidenceListType* evidence;
  // HunterType hunters[4];
} RoomType;

// typedef struct{
//     RoomType *room;
//     EvidenceEnumType reads;
//     EvidenceListType *found;
//     int fear;
//     int boredom;
//     int id;

// } HunterType;

typedef struct EvidenceType{
    float value;
    EvidenceEnumType type;
} EvidenceType;

//Nodes
typedef struct RoomNodeType{
    struct RoomNodeType *next;
    RoomType *data;
} RoomNodeType;

typedef struct EvidenceNode {
  struct EvidenceNode *next;
  EvidenceType* data;
} EvNodeType;

// typedef struct HunterNode{
//   struct HunterNode *next;
//   HunterType *data;
// }HunterNodeType;

// //Lists
typedef struct RoomListType{
  RoomNodeType *head;
  RoomNodeType *tail;
} RoomListType;

typedef struct EvidenceListType{
    EvNodeType *head;
    EvNodeType *tail;
} EvidenceListType;

// typedef struct {
//     HunterNodeType *head;
//     HunterNodeType *tail;
// } HunterListType;






// You may rename these types if you wish

int randInt(int, int);          // Generates a pseudorandom integer between the parameters
float randFloat(float, float);  // Generates a pseudorandom float between the parameters

// void populateRooms(BuildingType*);   // Populates the building with sample data for rooms

void initEvidence(float, EvidenceEnumType, EvidenceType*);
void initEvidenceList(EvidenceListType*);
// void addEvidence(EvidenceListType*, EvidenceType*);
// void cleanupEvidenceList(EvidenceListType*);


void initRoom(char*, GhostType*, RoomType*);
void initRoomList(RoomListType* arr);
void addListRoom(RoomListType *list, RoomType *room);
void cleanupRoomList( RoomListType *list);


void initGhost(RoomType*,GhostEnumType,GhostType*);
const char* getGhostName(GhostEnumType);

// void initHunter(RoomType*, EvidenceEnumType, int,HunterType*);
// void initHunterList(HunterListType*);
// void addHunter(HunterListType*, HunterType*);
// void removeHunter(HunterListType*, HunterType*);
// void printHunter(HunterType*);