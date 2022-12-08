#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_STR                 64
#define FEAR_RATE                1
#define MAX_FEAR               100
#define MAX_HUNTERS              4
#define USLEEP_TIME          50000
#define BOREDOM_MAX             99
#define C_NOK                    0
#define C_OK                     1

#define EMF_MIN_STANDARD         0
#define EMF_MAX_STANDARD      4.90
#define EMF_MIN_GHOST         4.70
#define EMF_MAX_GHOST         5.00
#define TEMP_MIN_STANDARD        0
#define TEMP_MAX_STANDARD    27.00
#define TEMP_MIN_GHOST      -10.00
#define TEMP_MAX_GHOST        1.00
#define FINGERPRINT_STANDARD     0
#define FINGERPRINT_GHOST        1
#define SOUND_MIN_STANDARD   40.00
#define SOUND_MAX_STANDARD   70.00
#define SOUND_MIN_GHOST      65.00
#define SOUND_MAX_GHOST      75.00



typedef enum { EMF, TEMPERATURE, FINGERPRINTS, SOUND } EvidenceEnumType;
typedef enum { POLTERGEIST, BANSHEE, BULLIES, PHANTOM } GhostEnumType;

//Types

typedef struct {
  GhostEnumType type;
  struct RoomType *currRoom;
   struct BuildingType *building;
  int boredom;
} GhostType;

typedef struct RoomType {
  char name[MAX_STR];
  GhostType* ghost;
  struct RoomListType* next;
  struct EvidenceListType* evidence;
  struct HunterType* hunters[4];
  int hunterListSize;
  sem_t mutex;
} RoomType;

typedef struct HunterType {
  RoomType *room;
  EvidenceEnumType reads;
  struct BuildingType *building;
  struct EvidenceListType* evList;
  int fear;
  int boredom;
  char name[MAX_STR];
  int id;
  int ghostlyEvidence;

} HunterType;

typedef struct BuildingType {
  GhostType *ghost;
  HunterType* hunters[4];
  struct RoomListType* rooms;
  struct EvidenceListType* masterEvList;
  int hunterListSize;
  sem_t mutex;
}BuildingType;

typedef struct EvidenceType{
  float value;
  EvidenceEnumType type;
  int ghostly;
} EvidenceType;

// Nodes
typedef struct RoomNodeType{
  struct RoomNodeType *next;
  RoomType *data;
} RoomNodeType;

typedef struct EvidenceNode {
  struct EvidenceNode *next;
  EvidenceType* data;
} EvNodeType;

// Lists
typedef struct RoomListType{
  RoomNodeType *head;
  RoomNodeType *tail;
  int size;
} RoomListType;

typedef struct EvidenceListType{
  EvNodeType *head;
  EvNodeType *tail;
  int size;
} EvidenceListType;




// You may rename these types if you wish

int randInt(int, int);          // Generates a pseudorandom integer between the parameters
float randFloat(float, float);  // Generates a pseudorandom float between the parameters

void populateRooms(BuildingType*);   // Populates the building with sample data for rooms

void initEvidence(float, EvidenceEnumType, int, EvidenceType*);
void initEvidenceList(EvidenceListType*);
void addEvidence(EvidenceListType*, EvidenceType*);
void cleanupEvidenceList(EvidenceListType*);
void printEvidenceList(EvidenceListType*);
const char* getEvidenceName(EvidenceEnumType);


void initRoom(RoomType*, char*);
void initRoomList(RoomListType*);
void appendRoom(RoomListType*, RoomType*);
void addNieghbour(RoomListType*, RoomType*);
void printRooms(RoomListType*);
void connectRooms(RoomType*, RoomType*);
void cleanupRoomList(RoomListType*);
void cleanupRoomData(RoomListType*);
void printHunterList(RoomType*);
void randomRoom(RoomListType*, GhostType*, int);
void randomRoomHunter(RoomListType*, HunterType*);
void addEvidenceToRoom(RoomType*, EvidenceType*);
void copyEvidence(EvidenceType*, EvidenceType*);

void initGhost(RoomType*, GhostEnumType, GhostType*);
const char* getGhostName(GhostEnumType);
void leaveEvidence(RoomType*, GhostType*);
void* chooseGhostAction(void*);
void switchGhostRooms(GhostType*);

void initHunter(RoomType*, EvidenceEnumType, char*, int, HunterType*);
void addHunterToRoom(RoomType*, HunterType*);
void addEvidenceToHunter(HunterType*, EvidenceType*);
void removeHunterFromRoom(RoomType*, HunterType*);
void printHunterEvidence(HunterType*);
void cleanupHunters(HunterType*);
void switchRoomsHunter(HunterType*);
void collectEvidence(HunterType*);
void shareEvidence(HunterType*);
void removeEvidenceRoom(RoomType*, EvidenceType*);
void findGhost(HunterType*, int*);

void initBuilding(GhostType*, BuildingType*);
void addHunterToBuilding(HunterType*, BuildingType*);
void populateRooms(BuildingType*);
void cleanupBuilding(BuildingType*);
void* chooseAction(void*);
void scaredHunters(BuildingType*, int*);