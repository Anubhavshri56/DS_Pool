#include<stdio.h>
#include<stdlib.h>
#include<tm_sll.h>
#include<tm_stack.h>
#include<tm_common.h>
int main()
{
int success;
int x1,x2,x3,x4;
int *x;
x1=10;
x2=20;
x3=30;
x4=40;
Stack *stack;
stack=createStack(&success);
if(success==false)
{
printf("Unable to create stack\n");
return 0;
}
pushOnStack(stack,&x1,&success);
if(success) printf("%d pushed onto stack\n",x1);
else printf("Unable to Push %d\n",x1);

pushOnStack(stack,(void *)&x2,&success);
if(success) printf("%d pushed onto stack\n",x2);
else printf("Unable to Push %d\n",x2);

pushOnStack(stack,(void *)&x3,&success);
if(success) printf("%d pushed onto stack\n",x3);
else printf("Unable to Push %d\n",x3);

pushOnStack(stack,(void *)&x4,&success);
if(success) printf("%d pushed onto stack\n",x4);
else printf("Unable to Push %d\n",x4);
printf("Size of the Stack is %d\n",getSizeOfStack(stack));
if(isStackEmpty(stack)) printf("Stack is Empty\n");
else printf("Stack is not Empty\n");
x=(int *)elementAtTopOfStack(stack,&success);
printf("%d is the element at the top of the stack\n",*x);
printf("Now Popping All Elements from stack\n");
while(!isStackEmpty(stack))
{
x=(int *)popFromStack(stack,&success);
printf("%d popped\n",*x);
}
if(isStackEmpty(stack)) printf("Stack is Empty\n");
else printf("Stack is not Empty\n");
destroyStack(stack);
return 0;
}