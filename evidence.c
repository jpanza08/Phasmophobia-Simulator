#include "defs.h"

/*
 Function:   getEvidenceName
  Purpose:   gets EvidenceName in string
       in:   Evidence enum type
      out:   string of enum
*/
const char* getEvidenceName(EvidenceEnumType name) {
    switch(name) {
        case EMF: return "EMF";
        case TEMPERATURE: return "TEMPERATURE";
        case FINGERPRINTS: return "FINGERPRINTS";
        case SOUND: return "SOUND";
    }
}

void initEvidence(float value, EvidenceEnumType reading, EvidenceType* ev) {
    ev->type = reading;
    ev->value = value;
}

void initEvidenceList(EvidenceListType *list){
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/*
 Function:   addEvidence
  Purpose:   adds a evidence to a evidencelist
       in:   evidencelist
       in:   evidence
      out:   updated evidencelist for evidence
*/
void addEvidence(EvidenceListType *list, EvidenceType *ev){
    EvNodeType* newNode = (EvNodeType*) malloc(sizeof(EvNodeType));
    newNode->data = ev;
    if(list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
        list->size++;
    }else{
        list->tail->next = newNode;
        list->tail = newNode;
        list->size++;
    }
}

/*
 Function:   addEvidenceToRoom
  Purpose:   adds the evidence to the room passed in, uses the rooms mutex to prevent syncronization errors.
   in/out:   room to add evidence to
       in:   evidence to be added to the room 
*/
void addEvidenceToRoom(RoomType *room, EvidenceType *ev){
   pthread_mutex_lock(&room->mutex);
   EvNodeType* newNode = (EvNodeType*) malloc(sizeof(EvNodeType));
    newNode->data = ev;
    if(room->evidence->head == NULL){
        printf("Ghost left evidence in %s.\n", room->name);
        room->evidence->head = newNode;
        room->evidence->tail = newNode;
        room->evidence->size++;
    }else{
        printf("Ghost left evidence in %s.\n", room->name);
        room->evidence->tail->next = newNode;
        room->evidence->tail = newNode;
        room->evidence->size++;
    }
    pthread_mutex_unlock(&room->mutex);
}

/*
 Function:   removeEvidenceRoom
  Purpose:   removes evidence from room
   in/out:   room
       in:   evidence to be removed from room 
*/
void removeEvidenceRoom(RoomType *room, EvidenceType *ev) {
    pthread_mutex_lock(&room->mutex);
    EvNodeType* current = room->evidence->head;
    if(current != NULL){

    while(current->next != NULL) {
        if(current->next->data == ev) {
            EvNodeType* temp = current->next->next;
            free(current->next->data);
            free(current->next);
            current->next = temp;
            break;
        }
        current = current->next;
    }
    }
    pthread_mutex_unlock(&room->mutex);
}

void printEvidenceList(EvidenceListType* list) {
    EvNodeType* current = list->head;
    printf("\n");
    while(current != NULL) {
        printf("type: %s ", getEvidenceName(current->data->type));
        current = current->next;
    }
    printf("\n");
}

/*
 Function:   cleanupEvidenceList
  Purpose:   deallocates memory used by EvidenceList
       in:   EvidenceList
      out:   updated EvidenceList
*/
void cleanupEvidenceList(EvidenceListType *list){
    EvNodeType *curr, *next;
    if(list->head == NULL)
        return;
    if(list->head == list->tail){
        free(list->head);
        return;
    }
    curr = list->head;
    next = curr->next;
    while(curr->next != NULL){
        free(curr);
        curr = next;
        next = curr->next;
    }
    free(curr);
}