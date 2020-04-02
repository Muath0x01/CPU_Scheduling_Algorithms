/* Note: You should not modify this file. */

struct eventQnode {		//an node in the events list
    Event data;			//the event
    struct eventQnode *nextPtr;
};
typedef struct eventQnode EventQnode;
typedef EventQnode *EventQnodePtr;

void enqueueevent(EventQnodePtr * headPtr, EventQnodePtr * tailPtr,
		  Event e);
Event dequeueevent(EventQnodePtr * headPtr, EventQnodePtr * tailPtr);
int isEmptyEQ(EventQnodePtr headPtr);
void displayEvents(EventQnodePtr currentPtr);
