#include<tm_sll.h>
#include<tm_common.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
int i1,i2,i3,i4,i5,i6,y;
int *x;
bool success;
SinglyLinkedList * list1,*list2;
list1=createSinglyLinkedList(&success);
list2=createSinglyLinkedList(&success);
if(success==false) printf("Unable to create List\n");
else
{
i1=100;
i2=200;
i3=300;
i4=400;
i5=500;
i6=600;
addToSinglyLinkedList(list1,(void *)&i1,&success);
addToSinglyLinkedList(list1,(void *)&i2,&success);
addToSinglyLinkedList(list2,(void *)&i3,&success);
addToSinglyLinkedList(list2,(void *)&i4,&success);
addToSinglyLinkedList(list2,(void *)&i5,&success);
addToSinglyLinkedList(list2,(void *)&i6,&success);
}
appendToSinglyLinkedList(list1,list2,&success);
if(success) printf("Appended\n");
else
{
printf("Unable to Append\n");
return 0;
}
for(y=0;y<getSizeOfSinglyLinkedList(list1);y++) printf("%d\n",* (int *)getFromSinglyLinkedList(list1,y,&success));
printf("Clearing list\n");
clearSinglyLinkedList(list1);
printf("destroying the List\n");
destroySinglyLinkedList(list1);
return 0;
}