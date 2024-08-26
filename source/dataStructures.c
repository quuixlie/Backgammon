#include "../headers/dataStructures.h"
#include <stdlib.h>


void initializeLinkedList(LinkedList* linkedList);
LinkedListNode* createLinkedListNode(short data);


LinkedList* createLinkedList() {
    LinkedList* linkedList = (LinkedList *) malloc(sizeof(LinkedList));
    initializeLinkedList(linkedList);

    return linkedList;
}

void initializeLinkedList(LinkedList* linkedList) {
    linkedList->head = NULL;
    linkedList->tail = NULL;
}

void appendToLinkedList(LinkedList* linkedList, short data) {
    LinkedListNode* newNode = createLinkedListNode(data);

    if (linkedList->head == NULL) {
        linkedList->head = newNode;
        linkedList->tail = newNode;
    }
    else {
        linkedList->tail->nextNode = newNode;
        newNode->prevNode = linkedList->tail;
        linkedList->tail = newNode;
    }
}

LinkedListNode* createLinkedListNode(short data) {
    LinkedListNode* newNode = (LinkedListNode*) malloc(sizeof(LinkedListNode));

    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->prevNode = NULL;
    newNode->nextNode = NULL;

    return newNode;
}

short getLengthOfLinkedList(LinkedList* linkedList) {
    short count = 0;
    LinkedListNode* currentNode = linkedList->head;

    while (currentNode != NULL) {
        count += 1;
        currentNode = currentNode->nextNode;
    }

    return count;
}

void removeAllElementsFromLinkedList(LinkedList* linkedList) {
    LinkedListNode* currentNode = linkedList->head;

    while (currentNode != NULL) {
        LinkedListNode* tempNode = currentNode;
        currentNode = currentNode->nextNode;
        free(tempNode);
    }

    linkedList->head = NULL;
    linkedList->tail = NULL;
}

void destroyLinkedList(LinkedList* linkedList) {
    LinkedListNode* currentNode = linkedList->head;
    LinkedListNode* nextNode;

    while (currentNode != NULL) {
        nextNode = currentNode->nextNode;
        free(currentNode);
        currentNode = nextNode;
    }

    free(linkedList);
}