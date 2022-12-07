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

void initEvidence(float value, EvidenceEnumType reading, int ghostly, EvidenceType* ev) {
    ev->type = reading;
    ev->value = value;
    ev->ghostly = ghostly;
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
    EvNodeType* newNode = (EvNodeType*) calloc(1, sizeof(EvNodeType));
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
    EvNodeType* newNode = (EvNodeType*) calloc(1, sizeof(EvNodeType));
    newNode->data = ev;
    if(room->evidence->head == NULL){
        printf("Ghost left evidence in %s.\n", room->name);
        room->evidence->head = newNode;
        room->evidence->tail = newNode;
        room->evidence->size++;
        // free(newNode);

    }else{
        printf("Ghost left evidence in %s.\n", room->name);
        room->evidence->tail->next = newNode;
        room->evidence->tail = newNode;
        room->evidence->size++;
        free(newNode);

    }
}

/*
 Function:   removeEvidenceRoom
  Purpose:   removes evidence from room
   in/out:   room
       in:   evidence to be removed from room 
*/
void removeEvidenceRoom(RoomType *room, EvidenceType *ev) {
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
}

/*
 Function:   printEvidenceList
  Purpose:   prints out evidence list
       in:   evidence list
      out:   printed evidence list
*/
void printEvidenceList(EvidenceListType* list) {
    EvNodeType* current = list->head;
    while(current != NULL) {
        // printf("\ntype: %d ", getEvidenceName(current->data->type));
        // printf("\ntype: %d ", current->data->type);
        current = current->next;
    }
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
        free(list->head->data);
        free(list->head);
        return;
    }
    curr = list->head;
    next = curr->next;
    while(curr->next != NULL){
        free(curr->data);
        free(curr);
        curr = next;
        next = curr->next;
    }
    free(curr->data);
    free(curr);
}