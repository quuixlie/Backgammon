#pragma once

typedef struct LinkedListNode {
    short data;
    struct LinkedListNode* nextNode;
    struct LinkedListNode* prevNode;
} LinkedListNode;

typedef struct LinkedList {
    LinkedListNode* head;
    LinkedListNode* tail;
} LinkedList;

LinkedList* createLinkedList();
void appendToLinkedList(LinkedList* linkedList, short data);
short getLengthOfLinkedList(LinkedList* linkedList);
void removeAllElementsFromLinkedList(LinkedList* linkedList);
void destroyLinkedList(LinkedList* linkedList);