#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "queue.h"


void enqueue(QnodePtr * headPtr, QnodePtr * tailPtr, Task task,
	     int sort_by)
{
    QnodePtr newNodePtr = malloc(sizeof(Qnode));
    if (newNodePtr == NULL) {
	fprintf(stderr, "Error: Could not allocate memory.\n");
	exit(-1);
    }
    newNodePtr->data = task;
    newNodePtr->nextPtr = NULL;

    if (sort_by == FIFO) {
	// Here is where the code goes to insert in FIFO order
	if (isEmpty(*headPtr)) {
	    *headPtr = newNodePtr;
	} else {
	    (*tailPtr)->nextPtr = newNodePtr;
	}
	*tailPtr = newNodePtr;
    } 
	else if (sort_by == SJF) {
	QnodePtr current = *headPtr, prev = NULL;
	while(current!=NULL && task.bt>=(current->data).bt){
		prev = current;
		current = current->nextPtr;
	}
	if(prev==NULL){
		newNodePtr->nextPtr= *headPtr;
		*headPtr=newNodePtr;
	}
	else{
		newNodePtr->nextPtr=prev->nextPtr;		
		prev->nextPtr=newNodePtr;			
	}	
	if(newNodePtr->nextPtr==NULL){
		*tailPtr = newNodePtr;
	}
	}

	else if (sort_by == RR) {
	  if (isEmpty(*headPtr)) {
	    *headPtr = newNodePtr;
	} else {
	    (*tailPtr)->nextPtr = newNodePtr;
	}
	*tailPtr = newNodePtr;
	}
	else {
	fprintf(stderr,
		"Error: Queue was asked to sort by something not recognized.\n");
	exit(-1);
    }
}

Task dequeue(QnodePtr * headPtr, QnodePtr * tailPtr)
{
    Task value;
    QnodePtr tempPtr;
    value = (*headPtr)->data;
    tempPtr = *headPtr;
    *headPtr = (*headPtr)->nextPtr;
    if (*headPtr == NULL) {
	*tailPtr = NULL;
    }
    free(tempPtr);
    return value;
}

int isEmpty(QnodePtr headPtr)
{
    return headPtr == NULL;
}
