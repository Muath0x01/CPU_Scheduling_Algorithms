/* Note: You should not modify this file. */
#include <stdlib.h>

#include "params.h"
#include "task.h"
#include "event.h"
#include "event_q.h"

int gen_tasks(EventQnodePtr * headPtr, EventQnodePtr * tailPtr, int seed)
{
    Task task;			//the process structure
    Event event;		//the event structure
    int prevat = 0, i;		//set the previous arrival time to zero 

    *headPtr = NULL;
    *tailPtr = NULL;

    srand(seed);

    for (i = 0; i < num_tasks; i++) {	//generate all arrivals and insert them in the event list
	//fill up the info of the process structure             
	task.id = i;
	task.at = (rand() % iat) + prevat;
	// Intentionally prevent two processes arriving at the same time.
	if (task.at == prevat) {
		task.at++;
	}
	prevat = task.at;
	task.bt = rand() % max_burst_time + 1;
	task.pr = rand() % MAXPR;

	//fill up the info of the event structure
	event.type = 0;		//event type is 0:arrival
	event.time = task.at;	//event time
	event.task = task;	//note that the process is encapsulated in an event structure

	enqueueevent(headPtr, tailPtr, event);	//insert the event in the events list
    }
    return 0;
}
