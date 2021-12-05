#ifndef __TM_STACK__C
#define __TM_STACK__C 123
#include<stdio.h>
#include<stdlib.h>
#include<tm_sll.h>
#include<tm_common.h>
#include<tm_stack.h>
Stack *createStack(bool *success)
{
Stack *stack;
SinglyLinkedList *singlyLinkedList;
singlyLinkedList=createSinglyLinkedList(success);
if(success==false) return NULL;
stack=(Stack *)malloc(sizeof(Stack));
if(stack==NULL)
{
destroySinglyLinkedList(singlyLinkedList);
if(success) *success=false;
return NULL;
}
stack->singlyLinkedList=singlyLinkedList;
if(success) *success=true;
return stack;
}
void pushOnStack(Stack *stack,void *ptr,bool *success)
{
if(success) *success=false;
if(stack==NULL || stack->singlyLinkedList==NULL) return;
insertIntoSinglyLinkedList(stack->singlyLinkedList,0,ptr,success);
}
void *popFromStack(Stack *stack,bool *success)
{
void *ptr;
if(success) *success=false;
if(isStackEmpty(stack)) return NULL;
ptr=removeFromSinglyLinkedList(stack->singlyLinkedList,0,success);
if(success) *success=true;
return ptr;
}
bool getSizeOfStack(Stack *stack)
{
return stack->singlyLinkedList->size;
}
bool isStackEmpty(Stack *stack)
{
if(stack==NULL) return true;
else if(stack->singlyLinkedList==NULL) return true;
else if(stack->singlyLinkedList->size==0) return true;
else return false;
}
void *elementAtTopOfStack(Stack *stack,bool *success)
{
void *ptr;
if(success) *success=false;
if(stack==NULL || stack->singlyLinkedList==NULL) return NULL;
ptr=getFromSinglyLinkedList(stack->singlyLinkedList,0,success);
if(success) *success=true;
return ptr;
}
void destroyStack(Stack *stack)
{
if(stack==NULL) return;
if(stack->singlyLinkedList==NULL) return;
destroySinglyLinkedList(stack->singlyLinkedList);
free(stack);
}
void clearStack(Stack *stack)
{
if(stack==NULL) return;
if(stack->singlyLinkedList==NULL) return;
clearSinglyLinkedList(stack->singlyLinkedList);
}
#endif