#ifndef __TM_SLL__H
#define __TM_SLL__H 123
#include<tm_common.h>
typedef struct __tm_sll_node
{
void *ptr;
struct __tm_sll_node *next;
}SinglyLinkedListNode;
typedef struct __tm_sll
{
struct __tm_sll_node *start;
struct __tm_sll_node *end;
int size;
}SinglyLinkedList;
typedef struct __$_tm_sll_iterator
{
SinglyLinkedListNode *node;
}SinglyLinkedListIterator;
SinglyLinkedList * createSinglyLinkedList(bool *success);
void addToSinglyLinkedList(SinglyLinkedList *singlyLinkedList,void *ptr,bool *success);
void insertIntoSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,void *ptr,bool *success);
void * removeFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool *success);
void clearSinglyLinkedList(SinglyLinkedList *singlyLinkedList);
void appendToSinglyLinkedList(SinglyLinkedList *targetSinglyLinkedList,SinglyLinkedList *sourceSinglyLinkedList,bool *success);
void * getFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool *success);
void destroySinglyLinkedList(SinglyLinkedList *singlyLinkedList);
int getSizeOfSinglyLinkedList(SinglyLinkedList *singlyLinkedList);
SinglyLinkedListIterator getSinglyLinkedListIterator(SinglyLinkedListIterator *singlyLinkedListIterator,bool *success);
bool hasNextInSinglyLinkedList(SinglyLinkedListIterator *singlyLinkedListIterator);
void *getNextElementFromSinglyLinkedList(SinglyLinkedListIterator *singlyLinkedListIterator,bool *success);
#endif