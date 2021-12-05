#ifndef __TM_AVL_TREE__C
#define __TM_AVL_TREE__C 123
#include<stdlib.h>
#include<tm_common.h>
#include<tm_sll.h>
#include<tm_stack.h>
#include<tm_avl_tree.h>
#include<tm_queue.h>
int getHeightOfTree(AVLTreeNode *root)
{
int leftTreeHeight,rightTreeHeight;
if(root==NULL) return 0;
leftTreeHeight=getHeightOfTree(root->left);
rightTreeHeight=getHeightOfTree(root->right);
if(leftTreeHeight>rightTreeHeight) return leftTreeHeight+1;
else return rightTreeHeight+1;
}
void balanceIt(AVLTree *avlTree,Stack *stack)
{
AVLTreeNode *j,*rc,*lc,*rclc,*lcrc,*parent;
AVLTreeNode **p2p;
int leftTreeHeight,rightTreeHeight,diff,succ;
if(stack==NULL) return;
while(!(isStackEmpty(stack)))
{
j=(AVLTreeNode *)popFromStack(stack,&succ);
parent=(AVLTreeNode *)popFromStack(stack,&succ);
if(succ) pushOnStack(stack,(void *)parent,&succ);
leftTreeHeight=getHeightOfTree(j->left);
rightTreeHeight=getHeightOfTree(j->right);
diff=leftTreeHeight-rightTreeHeight;
if(diff>=-1 && diff<=1) continue;
if(isStackEmpty(stack)) p2p=&(avlTree->start);
else if(j==parent->right) p2p=&(parent->right);
else p2p=&(parent->left);
if(diff<0)
{
rc=j->right;
if(getHeightOfTree(rc->left)>getHeightOfTree(rc->right))
{
rclc=rc->left;
rc->left=rclc->right;
rclc->right=rc;
j->right=rclc;
rc=j->right;
}
j->right=rc->left;
rc->left=j;
*p2p=rc;
}
else
{
lc=j->left;
if(getHeightOfTree(lc->right)>getHeightOfTree(lc->left))
{
lcrc=lc->right;
lc->right=lcrc->left;
lcrc->left=lc;
j->left=lcrc;
lc=j->left;
}
j->left=lc->right;
lc->right=j;
*p2p=lc;
}
}
}
AVLTree * createAVLTree(bool *success,int (*predicate)(void *,void *))
{
AVLTree *avlTree;
if(success) *success=false;
avlTree=(AVLTree *)malloc(sizeof(AVLTree));
if(avlTree==NULL || predicate==NULL) return NULL;
avlTree->start=NULL;
avlTree->predicate=predicate;
avlTree->size=0;
if(success) *success=true;
return avlTree;
}
void insertIntoAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
AVLTreeNode *t,*j;
int weight,succ;
Stack *stack;
stack=NULL;
if(success) *success=false;
if(avlTree==NULL) return;
if(avlTree->start==NULL)
{
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
if(t==NULL) return;
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
avlTree->start=t;
avlTree->size++;
if(success) *success=true;
return;
}
j=avlTree->start;
stack=createStack(&succ);
if(succ==false)
{
return;
}
while(1)
{
weight=avlTree->predicate(ptr,j->ptr);
if(weight==0)
{
destroyStack(stack);
return;
}
pushOnStack(stack,(void *)j,&succ);
if(succ==false)
{
destroyStack(stack);
return;
}
else if(weight>0)
{
if(j->right==NULL)
{
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
j->right=t;
break;
}
j=j->right;
}
else
{
if(j->left==NULL)
{
t=(AVLTreeNode *)malloc(sizeof(AVLTreeNode));
t->ptr=ptr;
t->left=NULL;
t->right=NULL;
j->left=t;
break;
}
j=j->left;
}
}
avlTree->size++;
if(success) *success=true;
balanceIt(avlTree,stack);
destroyStack(stack);
}
void * removeFromAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
AVLTreeNode *t,*j,*e,*f,*g;
AVLTreeNode **p2p;
int weight,succ;
Stack *stack;
Queue *queue;
void *foundPtr;
if(success) *success=false;
if(avlTree==NULL) return NULL;
if(avlTree->start==NULL) return NULL;
t=avlTree->start;
stack=createStack(&succ);
if(succ==false)
{
destroyStack(stack);
return NULL;
}
queue=createQueue(&succ);
if(succ==false)
{
destroyQueue(queue);
return NULL;
}
while(t!=NULL)
{
weight=avlTree->predicate(ptr,t->ptr);
if(weight==0) break;
pushOnStack(stack,(void *)t,&succ);
if(succ==false)
{
destroyStack(stack);
return NULL;
}
j=t;
if(weight<0) t=t->left; else t=t->right;
}
if(t==NULL) return NULL;
foundPtr=t->ptr;
if(t==avlTree->start) p2p=&(avlTree->start);
else if(j->right==t) p2p=&(j->right);
else p2p=&(j->left);
if(t->left==t->right) *p2p=NULL;
else if(t->right!=NULL)
{
for(e=t->right;e->left!=NULL;e=e->left)
{
addToQueue(queue,(void *)e,&succ);
if(succ==false)
{
destroyQueue(queue);
return NULL;
}
f=e;
}
while(!(isQueueEmpty(queue)))
{
g=(AVLTreeNode *)removeFromQueue(queue,&succ);
pushOnStack(stack,(void*)g,&succ);
}
destroyQueue(queue);
if(e==t->right) e->left=t->left;
else
{
f->left=e->right;
e->left=t->left;
e->right=t->right;
}
*p2p=e;
}
else
{
for(e=t->left;e->right!=NULL;e=e->right) f=e;
if(e!=t->left)
{
f->right=e->left;
e->left=t->left;
}
*p2p=e;
}
free(t);
avlTree->size--;
if(success) *success=true;
balanceIt(avlTree,stack);
destroyStack(stack);
return foundPtr;
}
void clearAVLTree(AVLTree *avlTree)
{

}
void * getFromAVLTree(AVLTree *avlTree,void *ptr,bool *success)
{
AVLTreeNode *j,*t;
int weight;
if(success) *success=false;
if(avlTree==NULL) return NULL;
if(avlTree->start==NULL) return NULL;
t=avlTree->start;
while(t!=NULL)
{
weight=avlTree->predicate(ptr,t->ptr);
if(weight==0)
{
if(success) *success=true;
return t->ptr;
}
else if(weight>0) t=t->right;
else t=t->left;
}
return NULL;
}
void destroyAVLTree(AVLTree *avlTree)
{
if(avlTree==NULL) return;
clearAVLTree(avlTree);
free(avlTree);
}
int getSizeOfAVLTree(AVLTree *avlTree)
{
if(avlTree==NULL) return 0;
return avlTree->size;
}
AVLTreeInOrderIterator getAVLTreeInOrderIterator(AVLTree *avlTree,bool *success)
{
int succ;
AVLTreeNode *t;
AVLTreeInOrderIterator avlTreeInOrderIterator;
if(success) *success=false;
avlTreeInOrderIterator.node=NULL;
avlTreeInOrderIterator.stack=NULL;
if(avlTree==NULL) return avlTreeInOrderIterator;
if(avlTree->start==NULL)
{
if(success) *success=true;
return avlTreeInOrderIterator;
}
t=avlTree->start;
avlTreeInOrderIterator.stack=createStack(&succ);
if(succ==false) return avlTreeInOrderIterator;
while(t!=NULL)
{
pushOnStack(avlTreeInOrderIterator.stack,t,&succ);
if(succ==false)
{
destroyStack(avlTreeInOrderIterator.stack);
avlTreeInOrderIterator.stack=NULL;
return avlTreeInOrderIterator;
}
t=t->left;
}
avlTreeInOrderIterator.node=(AVLTreeNode *)popFromStack(avlTreeInOrderIterator.stack,&succ);
if(success) *success=true;
return avlTreeInOrderIterator;
}
bool hasNextInOrderElementInAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator)
{
if(avlTreeInOrderIterator==NULL || avlTreeInOrderIterator->node==NULL) return false;
return true;
}
void * getNextInOrderElementFromAVLTree(AVLTreeInOrderIterator *avlTreeInOrderIterator,bool *success)
{
AVLTreeNode *t,*j;
int succ;
if(success) *success=false;
if(avlTreeInOrderIterator==NULL) return NULL;
if(avlTreeInOrderIterator->node==NULL) return NULL;
j=avlTreeInOrderIterator->node;
t=j->right;
while(t!=NULL)
{
pushOnStack(avlTreeInOrderIterator->stack,t,&succ);
if(succ==false)
{
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->stack=NULL;
avlTreeInOrderIterator->node=NULL;
if(success) *success=true;
return j->ptr;
}
t=t->left;
}
if(isStackEmpty(avlTreeInOrderIterator->stack))
{
destroyStack(avlTreeInOrderIterator->stack);
avlTreeInOrderIterator->stack=NULL;
avlTreeInOrderIterator->node=NULL;
}
else
{
avlTreeInOrderIterator->node=(AVLTreeNode *)popFromStack(avlTreeInOrderIterator->stack,&succ);
}
if(success) *success=true;
return j->ptr;
}
AVLTreePreOrderIterator getAVLTreePreOrderIterator(AVLTree *avlTree,bool *success)
{
int succ;
AVLTreePreOrderIterator avlTreePreOrderIterator;
if(success) *success=false;
avlTreePreOrderIterator.node=NULL;
avlTreePreOrderIterator.stack=NULL;
if(avlTree==NULL) return avlTreePreOrderIterator;
if(avlTree->start==NULL)
{
if(success) *success=true;
return avlTreePreOrderIterator;
}
avlTreePreOrderIterator.stack=createStack(&succ);
if(succ==false) return avlTreePreOrderIterator;
avlTreePreOrderIterator.node=avlTree->start;
if(success) *success=true;
return avlTreePreOrderIterator;
}
bool hasNextPreOrderElementInAVLTree(AVLTreePreOrderIterator *avlTreePreOrderIterator)
{
if(avlTreePreOrderIterator==NULL || avlTreePreOrderIterator->node==NULL) return false;
return true;
}
void *getNextPreOrderElementFromAVLTree(AVLTreePreOrderIterator *avlTreePreOrderIterator,bool *success)
{
AVLTreeNode *t,*j;
int succ;
if(success) *success=false;
if(avlTreePreOrderIterator==NULL) return NULL;
if(avlTreePreOrderIterator->node==NULL) return NULL;
j=avlTreePreOrderIterator->node;
if(j->right!=NULL)
{
pushOnStack(avlTreePreOrderIterator->stack,(void *)j->right,&succ);
if(succ==false)
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
if(success) *success=true;
return j->ptr;
}
}
if(j->left!=NULL)
{
pushOnStack(avlTreePreOrderIterator->stack,(void *)j->left,&succ);
if(succ==false)
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
if(success) *success=true;
return j->ptr;
}
}
if(isStackEmpty(avlTreePreOrderIterator->stack))
{
destroyStack(avlTreePreOrderIterator->stack);
avlTreePreOrderIterator->stack=NULL;
avlTreePreOrderIterator->node=NULL;
}
else
{
avlTreePreOrderIterator->node=(AVLTreeNode *)popFromStack(avlTreePreOrderIterator->stack,&succ);
}
if(success) *success=true;
return j->ptr;
}
AVLTreePostOrderIterator getAVLTreePostOrderIterator(AVLTree *avlTree,bool *success)
{
int succ;
AVLTreeNode *t;
AVLTreePostOrderIterator avlTreePostOrderIterator;
if(success) *success=false;
avlTreePostOrderIterator.node=NULL;
avlTreePostOrderIterator.stack=NULL;
if(avlTree==NULL) return avlTreePostOrderIterator;
if(avlTree->start==NULL)
{
if(success) *success=true;
return avlTreePostOrderIterator;
}
avlTreePostOrderIterator.stack=createStack(&succ);
if(succ==false) return avlTreePostOrderIterator;
t=avlTree->start;
while(1)
{
while(t!=NULL)
{
if(t->right!=NULL) pushOnStack(avlTreePostOrderIterator.stack,t->right,&succ);
if(succ==false)
{
destroyStack(avlTreePostOrderIterator.stack);
avlTreePostOrderIterator.stack=NULL;
return avlTreePostOrderIterator;
}
pushOnStack(avlTreePostOrderIterator.stack,t,&succ);
if(succ==false)
{
destroyStack(avlTreePostOrderIterator.stack);
avlTreePostOrderIterator.stack=NULL;
return avlTreePostOrderIterator;
}
t=t->left;
}
t=popFromStack(avlTreePostOrderIterator.stack,&succ);
if(!(isStackEmpty(avlTreePostOrderIterator.stack)) && t->right!=NULL && t->right==elementAtTopOfStack(avlTreePostOrderIterator.stack,&succ))
{
popFromStack(avlTreePostOrderIterator.stack,&succ);
pushOnStack(avlTreePostOrderIterator.stack,t,&succ);
t=t->right;
}
else break;
}
avlTreePostOrderIterator.node=(AVLTreeNode *)t;
if(success) *success=true;
return avlTreePostOrderIterator;
}
bool hasNextPostOrderElementInAVLTree(AVLTreePostOrderIterator *avlTreePostOrderIterator)
{
if(avlTreePostOrderIterator==NULL || avlTreePostOrderIterator->node==NULL) return false;
return true;
}
void *getNextPostOrderElementFromAVLTree(AVLTreePostOrderIterator *avlTreePostOrderIterator,bool *success)
{
AVLTreeNode *t,*j;
int succ;
if(success) *success=false;
if(avlTreePostOrderIterator==NULL) return NULL;
if(avlTreePostOrderIterator->node==NULL) return NULL;
t=avlTreePostOrderIterator->node;
while(1)
{
if(!(isStackEmpty(avlTreePostOrderIterator->stack)) && t->right!=NULL && t->right==elementAtTopOfStack(avlTreePostOrderIterator->stack,&succ))
{
popFromStack(avlTreePostOrderIterator->stack,&succ);
pushOnStack(avlTreePostOrderIterator->stack,t,&succ);
t=t->right;
}
else
{
avlTreePostOrderIterator->node=(AVLTreeNode *)popFromStack(avlTreePostOrderIterator->stack,&succ);
break;
}
while(t!=NULL)
{
if(t->right!=NULL) pushOnStack(avlTreePostOrderIterator->stack,t->right,&succ);
if(succ==false)
{
destroyStack(avlTreePostOrderIterator->stack);
avlTreePostOrderIterator->stack=NULL;
return avlTreePostOrderIterator;
}
pushOnStack(avlTreePostOrderIterator->stack,t,&succ);
if(succ==false)
{
destroyStack(avlTreePostOrderIterator->stack);
avlTreePostOrderIterator->stack=NULL;
return avlTreePostOrderIterator;
}
t=t->left;
}
t=popFromStack(avlTreePostOrderIterator->stack,&succ);
}
if(success) *success=true;
return t->ptr;
}
#endif