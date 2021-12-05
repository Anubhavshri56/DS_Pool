#include<tm_sll.h>
#include<stdio.h>
int main()
{
int i1,i2,i3,i4,i5,i6,y;
int *x;
bool succ;
SinglyLinkedList *list1,*list2;
list1=createSinglyLinkedList(&succ);
list2=NULL;
i1=100;
i2=200;
i3=300;
i4=400;
i5=500;
i6=600;
addToSinglyLinkedList(list1,(void *)&i1,&succ);
addToSinglyLinkedList(list1,(void *)&i2,&succ);
addToSinglyLinkedList(list1,(void *)&i3,&succ);
addToSinglyLinkedList(list1,(void *)&i4,&succ);
addToSinglyLinkedList(list1,(void *)&i5,&succ);
addToSinglyLinkedList(list1,(void *)&i6,&succ);
appendToSinglylinkedList(list1,list2,&succ);
if(succ) printf("Appended\n"); else printf("Unable to append\n");
for(y=0;y<getSizeOfSinglyLinkedList(list1);y++)
{
x=(int *)getFromSinglylinkedList(list1,y,&succ);
printf("%d\n",*x);
}
destroySinglyLinkedList(list1);
return 0;
}