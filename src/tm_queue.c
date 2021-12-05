#ifndef __TM_QUEUE__C
#define __TM_QUEUE__C 123
#include<stdio.h>
#include<stdlib.h>
#include<tm_sll.h>
#include<tm_common.h>
#include<tm_queue.h>
Queue *createQueue(bool *success)
{
Queue *queue;
SinglyLinkedList *singlyLinkedList;
singlyLinkedList=createSinglyLinkedList(success);
if(success==false) return NULL;
queue=(Queue *)malloc(sizeof(Queue));
if(queue==NULL)
{
destroySinglyLinkedList(singlyLinkedList);
if(success) *success=false;
return NULL;
}
queue->singlyLinkedList=singlyLinkedList;
if(success) *success=true;
return queue;
}
void addToQueue(Queue *queue,void *ptr,bool *success)
{
if(success) *success=false;
if(queue==NULL || queue->singlyLinkedList==NULL) return;
addToSinglyLinkedList(queue->singlyLinkedList,ptr,success);
}
void *removeFromQueue(Queue *queue,bool *success)
{
void *ptr;
if(success) *success=false;
if(isQueueEmpty(queue)) return NULL;
ptr=removeFromSinglyLinkedList(queue->singlyLinkedList,0,success);
if(success) *success=true;
return ptr;
}
bool getSizeOfQueue(Queue *queue)
{
return queue->singlyLinkedList->size;
}
bool isQueueEmpty(Queue *queue)
{
if(queue==NULL) return true;
else if(queue->singlyLinkedList==NULL) return true;
else if(queue->singlyLinkedList->size==0) return true;
else return false;
}
void *elementAtFrontOfQueue(Queue *queue,bool *success)
{
void *ptr;
if(success) *success=false;
if(queue==NULL || queue->singlyLinkedList==NULL) return NULL;
ptr=getFromSinglyLinkedList(queue->singlyLinkedList,0,success);
if(success) *success=true;
return ptr;
}
void destroyQueue(Queue *queue)
{
if(queue==NULL) return;
if(queue->singlyLinkedList==NULL) return;
destroySinglyLinkedList(queue->singlyLinkedList);
free(queue);
}
void clearQueue(Queue *queue)
{
if(queue==NULL) return;
if(queue->singlyLinkedList==NULL) return;
clearSinglyLinkedList(queue->singlyLinkedList);
}
#endif