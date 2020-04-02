/* Note: You should not modify this file */

#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "event.h"
#include "event_q.h"


void
enqueueevent(EventQnodePtr * headPtr, EventQnodePtr * tailPtr, Event se)
{
    EventQnodePtr newNodePtr = malloc(sizeof(EventQnode));
    if (newNodePtr != NULL) {
	newNodePtr->data = se;
	newNodePtr->nextPtr = NULL;
    }
    EventQnodePtr current = *headPtr, prev = NULL;
    while (current != NULL && se.time > (current->data).time) {	//find the insert position in order of time
	prev = current;
	current = current->nextPtr;
    }
    while (current != NULL && se.time == (current->data).time && se.type < (current->data).type) {	//then find the insert position in order of event's type
	prev = current;
	current = current->nextPtr;
    }

    if (prev == NULL) {
	newNodePtr->nextPtr = *headPtr;
	*headPtr = newNodePtr;
    } else {
	newNodePtr->nextPtr = prev->nextPtr;
	prev->nextPtr = newNodePtr;
    }
    if (newNodePtr->nextPtr == NULL) {
	*tailPtr = newNodePtr;
    }
}

Event dequeueevent(EventQnodePtr * headPtr, EventQnodePtr * tailPtr)
{
    Event value;
    EventQnodePtr tempPtr;
    value = (*headPtr)->data;
    tempPtr = *headPtr;
    *headPtr = (*headPtr)->nextPtr;
    if (*headPtr == NULL) {
	*tailPtr = NULL;
    }
    free(tempPtr);
    return value;
}

int isEmptyEQ(EventQnodePtr headPtr)
{
    return headPtr == NULL;
}

void displayEvents(EventQnodePtr currentPtr)
{
    if (currentPtr == NULL)
	printf("The event list is empty ...\n");
    else {
	fprintf(stdout, "Event List:\n");
	while (currentPtr != NULL) {
	    fprintf(stdout, "\tTask %d (at:%d,bt:%d,pr:%d)\n",
		   (currentPtr->data).task.id,
		   (currentPtr->data).task.at, (currentPtr->data).task.bt,
		   (currentPtr->data).task.pr);
	    currentPtr = currentPtr->nextPtr;
	}
    }
}
