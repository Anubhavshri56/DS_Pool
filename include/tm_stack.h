#ifndef __TM_STACK__H
#define __TM_STACK__H 123
#include<stdio.h>
#include<tm_sll.h>
#include<tm_common.h>
typedef struct __$_tm_stack
{
SinglyLinkedList *singlyLinkedList;
}Stack;
Stack *createStack(bool *success);
void pushOnStack(Stack *stack,void *ptr,bool *success);
void *popFromStack(Stack *stack,bool *success);
bool getSizeOfStack(Stack *stack);
bool isStackEmpty(Stack *stack);
void *elementAtTopOfStack(Stack *stack,bool *success);
void destroyStack(Stack *stack);
void clearStack(Stack *stack);
#endif