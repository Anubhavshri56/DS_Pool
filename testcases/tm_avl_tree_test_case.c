#include<stdio.h>
#include<stdlib.h>
#include<tm_common.h>
#include<tm_sll.h>
#include<tm_avl_tree.h>
#include<tm_stack.h>
int myComparator(void *left,void *right)
{
int i;
char *oriLeftString,*oriRightString;
char leftString[31],rightString[31];
oriRightString=(char *)right;
oriLeftString=(char *)left;
for(i=0;oriLeftString[i];i++) leftString[i]=oriLeftString[i];
leftString[i]='\0';
for(i=0;oriRightString[i];i++) rightString[i]=oriRightString[i];
rightString[i]='\0';
for(i=0;rightString[i];i++) if(rightString[i]>=97 && rightString[i]<=122) rightString[i]=rightString[i]-32;
for(i=0;leftString[i];i++) if(leftString[i]>=97 && leftString[i]<=122) leftString[i]=leftString[i]-32;
for(i=0;leftString[i] && rightString[i];i++) if(leftString[i]!=rightString[i]) return leftString[i]-rightString[i];
if(leftString[i]=='\0' && rightString[i]=='\0') return 0;
if(leftString[i]=='\0' && rightString[i]!='\0') return -1;
if(leftString[i]!='\0' && rightString[i]=='\0') return 1;
}
int main()
{
int num,success,ch;
char *y;
int *x;
char string[31];
char more;
AVLTreeInOrderIterator inOrderiterator;
AVLTreePreOrderIterator preOrderiterator;
AVLTreePostOrderIterator postOrderiterator;
AVLTree *tree;
tree=createAVLTree(&success,myComparator);
if(success==false)
{
printf("Unable to Create Tree\n");
return 0;
}
while(1)
{
printf("1. Insert into Tree\n");
printf("2. Iterate (InOrder)\n");
printf("3. Remove\n");
printf("4. Search\n");
printf("5. Iterate (PreOrder)\n");
printf("6. Iterate (PostOrder)\n");
printf("7. Exit\n");
printf("Enter Your Choice : ");
scanf("%d",&ch);
if(ch==1)
{
printf("Enter a number to add to AVL Tree : ");
y=(char *)malloc(sizeof(char)*31);
scanf("%s",y);
fflush(stdin);
insertIntoAVLTree(tree,(void *)y,&success);
if(success) printf("add of item that contains inserted in Tree\n");
else printf("Unable to insert into Tree\n");
}
else if(ch==2)
{
inOrderiterator=getAVLTreeInOrderIterator(tree,&success);
if(success)
{
while(hasNextInOrderElementInAVLTree(&inOrderiterator))
{
y=(char *)getNextInOrderElementFromAVLTree(&inOrderiterator,&success);
printf("%s\n",y);
}
}
}
else if(ch==3)
{
printf("Enter a number to Remove : ");
scanf("%d",&num);
x=(int *)malloc(sizeof(int));
*x=num;
removeFromAVLTree(tree,(void *)x,&success);
if(success) printf("%d found and Removed\n",*x);
else printf("NOT FOUND\n");
}
else if(ch==4)
{
printf("Enter a number to Search : ");
scanf("%s",string);
y=(char *)malloc(sizeof(char)*31);
y=&string[0];
getFromAVLTree(tree,(void *)y,&success);
if(success) printf("found\n");
else printf("NOT FOUND\n");
}
else if(ch==5)
{
preOrderiterator=getAVLTreePreOrderIterator(tree,&success);
if(success)
{
while(hasNextPreOrderElementInAVLTree(&preOrderiterator))
{
x=(int *)getNextPreOrderElementFromAVLTree(&preOrderiterator,&success);
printf("%d\n",*x);
}
}
}
else if(ch==6)
{
postOrderiterator=getAVLTreePostOrderIterator(tree,&success);
if(success)
{
while(hasNextPostOrderElementInAVLTree(&postOrderiterator))
{
x=(int *)getNextPostOrderElementFromAVLTree(&postOrderiterator,&success);
printf("%d\n",*x);
}
}
}
else if(ch==7) break;
}
destroyAVLTree(tree);
return 0;
}