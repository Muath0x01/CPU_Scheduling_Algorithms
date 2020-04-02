#include<stdio.h>
#include<stdlib.h>
struct queueNode
{
int pid;
int cpuburst;
int wt;
int pr;
struct queueNode *nextPtr;//to implement linked list
};

typedef struct queueNode QUEUENODE;//i.e. process
typedef QUEUENODE *QUEUENODEPTR;

int main()
{

QUEUENODEPTR headPtr=NULL, tailPtr=NULL;
int pid, cpuburst,pr;
int i,n;
printf("Enter no of Jobs: ");
scanf("%d",&n);

for(i=1;i<=n;i++)
{
pid=i;
cpuburst=rand( ) % 30 + 2;
pr=rand( ) % 500 + 1;
QUEUENODEPTR newPtr;
newPtr= malloc(sizeof(QUEUENODE));
//Under Windows use newPtr=new QUEUENODE; to create a new node
if(newPtr !=NULL)//if it is equal null means no enough memory fo it
{
//set its attributes
newPtr->pid=pid;
newPtr->cpuburst=cpuburst;
newPtr->pr=pr;
newPtr->nextPtr=NULL;
printf("%d (%d) ((%d)) -->\n",newPtr->pid,newPtr->wt,newPtr->pr);
if(i==1)//if first node to be queued
{
headPtr=newPtr;
tailPtr=newPtr;
}
else//if not first node to be queued
{//here code to be modified for other types of scheduling algos
QUEUENODEPTR current=headPtr;
QUEUENODEPTR prev;
while(current!=NULL && newPtr->pr>=(current->pr)){
prev = current;
current=current->nextPtr;
}
newPtr->nextPtr=prev->nextPtr;
prev->nextPtr = newPtr;
if (newPtr->nextPtr == NULL) tailPtr =newPtr;
if (newPtr->pr<headPtr->pr) headPtr =newPtr;
}

}////

else//if no enough memory for node
printf("No memory Available \n");
}

if(headPtr==NULL)
printf("The Queue is Empty: \n");
else
{
QUEUENODEPTR currentPtr=headPtr;
printf("The Queue is \n");
int WT=0, prevcpuburst=0;
float SUM=0;
while(currentPtr != NULL)
{
WT=WT+prevcpuburst;//wait is sum of previous burss till cpu ready for current process
currentPtr->wt=WT;//current wait is sum of previous bursts
printf("%d (%d) ((%d)) -->\n",currentPtr->pid,currentPtr->wt,currentPtr->pr);
prevcpuburst=currentPtr->cpuburst;
currentPtr=currentPtr->nextPtr;
SUM=SUM+WT;//
}
printf("NULL \n\n");
printf("AWT=%f\n",SUM/n);
}
return 0;
}
