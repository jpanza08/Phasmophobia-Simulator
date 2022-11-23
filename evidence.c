#include "defs.h"

void initEvidence(float value, EvidenceEnumType reading, EvidenceType* ev) {
    ev->type = reading;
    ev->value = value;
}

void initEvidenceList(EvidenceListType *list){
    list->head = NULL;
    list->tail = NULL;
}

void addEvidence(EvidenceListType *list, EvidenceType *ev){
    EvNodeType* newNode = (EvNodeType*) malloc(sizeof(EvNodeType));
    newNode->data = ev;

    //Empty
    if(list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
    }else{
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void printEvidenceList(EvidenceListType* list) {
    EvNodeType* current = list->head;
    printf("\n");
    while(current != NULL) {
        printf("type: %s ", getGhostName(current->data->type));
        current = current->next;
    }
    printf("\n");
}

void cleanupEvidenceList(EvidenceListType *list){
    EvNodeType *curr;
    
    if(list->head == NULL)
        return;
    if(list->head == list->tail){
        free(list->head);
        return;
    }

    curr = list->head;
    
    while(curr->next != NULL){
        free(curr);
        curr = curr->next;

    }
    free(curr);

}