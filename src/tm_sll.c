#ifndef __TM_SLL__C
#define __TM_SLL__C 123
#include<tm_sll.h>
#include<stdio.h>
#include<stdlib.h>
#include<tm_common.h>
SinglyLinkedList * createSinglyLinkedList(bool *success)
{
SinglyLinkedList *singlyLinkedList;
if(success) *success=false;
singlyLinkedList=(SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
if(singlyLinkedList==NULL) return NULL;
singlyLinkedList->start=NULL;
singlyLinkedList->end=NULL;
singlyLinkedList->size=0;
if(success) *success=true;
return singlyLinkedList;
}
void addToSinglyLinkedList(SinglyLinkedList *singlyLinkedList,void *ptr,bool *success)
{
SinglyLinkedListNode *singlyLinkedListNode;
if(success) *success=false;
singlyLinkedListNode=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(singlyLinkedListNode==NULL) return;
if(singlyLinkedList==NULL) return;
singlyLinkedListNode->ptr=ptr;
singlyLinkedListNode->next=NULL;
if(singlyLinkedList->start==NULL)
{
singlyLinkedList->start=singlyLinkedListNode;
singlyLinkedList->end=singlyLinkedListNode;
singlyLinkedList->size++;
if(success) *success=true;
return;
}
singlyLinkedList->end->next=singlyLinkedListNode;
singlyLinkedList->end=singlyLinkedListNode;
singlyLinkedList->size++;
if(success) *success=true;
}
void insertIntoSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,void *ptr,bool *success)
{
SinglyLinkedListNode *singlyLinkedListNode,*t,*j;
int finder;
if(success) *success=false;
singlyLinkedListNode=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(singlyLinkedListNode==NULL) return;
if(singlyLinkedList==NULL) return;
if(index<0 || index>singlyLinkedList->size) return;
t=singlyLinkedList->start;
for(finder=0;finder<index && t!=NULL;t=t->next,finder++) j=t;
if(finder<index && t==NULL) return;
singlyLinkedListNode->ptr=ptr;
singlyLinkedListNode->next=NULL;
if(t==singlyLinkedList->start)
{
singlyLinkedListNode->next=t;
singlyLinkedList->start=singlyLinkedListNode;
singlyLinkedList->size++;
if(singlyLinkedList->end==NULL) singlyLinkedList->end=singlyLinkedListNode;
}
else if(index==singlyLinkedList->size) addToSinglyLinkedList(singlyLinkedList,ptr,success);
else
{
j->next=singlyLinkedListNode;
singlyLinkedListNode->next=t;
singlyLinkedList->size++;
}
if(success) *success=true;
}
void * removeFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool *success)
{
void *ptr;
int finder;
SinglyLinkedListNode *p1,*p2;
if(success) *success=false;
if(singlyLinkedList==NULL) return NULL;
if(index<0 || index>singlyLinkedList->size) return NULL;
for(p1=singlyLinkedList->start,finder=0;finder<index;p1=p1->next,finder++) p2=p1;
ptr=p1->ptr;
if(singlyLinkedList->start==p1 && singlyLinkedList->end==p1)
{
singlyLinkedList->start=NULL;
singlyLinkedList->end=NULL;
}else if(singlyLinkedList->start==p1)
{
singlyLinkedList->start=p1->next;
}else if(singlyLinkedList->end==p1)
{
singlyLinkedList->end=p2;
p2->next=NULL;
}else
{
p2->next=p1->next;
}
singlyLinkedList->size--;
free(p1);
if(success) *success=true;
return ptr;
}
void clearSinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
SinglyLinkedListNode *singlyLinkedListNode;
while(singlyLinkedList->start!=NULL)
{
singlyLinkedListNode=singlyLinkedList->start;
singlyLinkedList->start=singlyLinkedList->start->next;
free(singlyLinkedListNode);
}
singlyLinkedList->size=0;
}
void appendToSinglyLinkedList(SinglyLinkedList *targetSinglyLinkedList,SinglyLinkedList *sourceSinglyLinkedList,bool *success)
{
SinglyLinkedListNode *s,*e,*t,*node;
bool done;
if(success) *success=false;
if(targetSinglyLinkedList==NULL) return;
if(sourceSinglyLinkedList==NULL || sourceSinglyLinkedList->size==0)
{
if(success) *success=true;
return;
}
s=NULL;
e=NULL;
t=sourceSinglyLinkedList->start;
done=true;
while(t!=NULL)
{
node=(SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
if(node==NULL)
{
done=false;
break;
}
node->ptr=t->ptr;
node->next=NULL;
if(s==NULL)
{
s=node;
e=node;
}
else
{
e->next=node;
e=node;
}
t=t->next;
}
if(done==false)
{
while(s!=NULL)
{
node=s;
s=s->next;
free(node);
}
return;
}
else
{
if(targetSinglyLinkedList->start==NULL)
{
targetSinglyLinkedList->start=s;
targetSinglyLinkedList->end=e;
targetSinglyLinkedList->size=sourceSinglyLinkedList->size;
}
else
{
targetSinglyLinkedList->end->next=s;
targetSinglyLinkedList->end=e;
targetSinglyLinkedList->size+=sourceSinglyLinkedList->size;
}
}
if(success) *success=true;
}
void * getFromSinglyLinkedList(SinglyLinkedList *singlyLinkedList,int index,bool *success)
{
int finder;
SinglyLinkedListNode * singlyLinkedListNode;
if(success) *success=false;
if(singlyLinkedList==NULL) return NULL;
if(index<0 || index>=singlyLinkedList->size) return NULL;
for(finder=0,singlyLinkedListNode=singlyLinkedList->start;finder<index;singlyLinkedListNode=singlyLinkedListNode->next,finder++);
return singlyLinkedListNode->ptr;
}
void destroySinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
if(singlyLinkedList==NULL) return;
clearSinglyLinkedList(singlyLinkedList);
free(singlyLinkedList);
}
int getSizeOfSinglyLinkedList(SinglyLinkedList *singlyLinkedList)
{
return singlyLinkedList->size;
}
SinglyLinkedListIterator getSinglyLinkedListIterator(SinglyLinkedList *singlyLinkedList,bool *success)
{
SinglyLinkedListIterator singlyLinkedListIterator;
if(success) *success=false;
singlyLinkedListIterator.node=NULL;
if(singlyLinkedList==NULL) return singlyLinkedListIterator;
if(singlyLinkedList->start==NULL)
{
if(success) *success=true;
return singlyLinkedListIterator;
}
if(success) *success=true;
singlyLinkedListIterator.node=singlyLinkedList->start;
return singlyLinkedListIterator;
}
bool hasNextInSinglyLinkedList(SinglyLinkedListIterator *singlyLinkedListIterator)
{
if(singlyLinkedListIterator==NULL) return false;
if(singlyLinkedListIterator->node==NULL) return false;
return true;
}
void *getNextElementFromSinglyLinkedList(SinglyLinkedListIterator *singlyLinkedListIterator,bool *success)
{
void *ptr=NULL;
if(success) *success=false;
if(singlyLinkedListIterator==NULL || singlyLinkedListIterator->node==NULL) return ptr;
ptr=singlyLinkedListIterator->node->ptr;
singlyLinkedListIterator->node=singlyLinkedListIterator->node->next;
if(success) *success=true;
return ptr;
}
#endif