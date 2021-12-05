#include<stdio.h>
#include<stdlib.h>
#include<tm_sll.h>
#include<tm_queue.h>
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
Queue *queue;
queue=createQueue(&success);
if(success==false)
{
printf("Unable to create queue\n");
return 0;
}
addToQueue(queue,&x1,&success);
if(success) printf("%d added to queue\n",x1);
else printf("Unable to add %d\n",x1);

addToQueue(queue,(void *)&x2,&success);
if(success) printf("%d added to queue\n",x2);
else printf("Unable to add %d\n",x2);

addToQueue(queue,(void *)&x3,&success);
if(success) printf("%d added to queue\n",x3);
else printf("Unable to add %d\n",x3);

addToQueue(queue,(void *)&x4,&success);
if(success) printf("%d added to queue\n",x4);
else printf("Unable to add %d\n",x4);
printf("Size of the Queue is %d\n",getSizeOfQueue(queue));
if(isQueueEmpty(queue)) printf("Queue is Empty\n");
else printf("Queue is not Empty\n");
x=(int *)elementAtFrontOfQueue(queue,&success);
printf("%d is the element at the Front of the queue\n",*x);
printf("Now removing All Elements from queue\n");
while(!isQueueEmpty(queue))
{
x=(int *)removeFromQueue(queue,&success);
printf("%d removed\n",*x);
}
if(isQueueEmpty(queue)) printf("Queue is Empty\n");
else printf("Queue is not Empty\n");
destroyQueue(queue);
return 0;
}