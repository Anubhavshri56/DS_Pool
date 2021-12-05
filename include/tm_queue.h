#ifndef __TM_QUEUE__H
#define __TM_QUEUE__H 123
#include<stdio.h>
#include<tm_sll.h>
#include<tm_common.h>
typedef struct __$_tm_queue
{
SinglyLinkedList *singlyLinkedList;
}Queue;
Queue *createQueue(bool *success);
void addToQueue(Queue *queue,void *ptr,bool *success);
void *removeFromQueue(Queue *queue,bool *success);
bool getSizeOfQueue(Queue *queue);
bool isQueueEmpty(Queue *queue);
void *elementAtFrontOfQueue(Queue *queue,bool *success);
void destroyQueue(Queue *queue);
void clearQueue(Queue *queue);
#endif