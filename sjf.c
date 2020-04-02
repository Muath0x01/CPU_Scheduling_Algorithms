#include <stdlib.h>
#include <stdio.h>

#include "params.h"
#include "task.h"
#include "queue.h"
#include "event.h"
#include "event_q.h"

void simulate_sjf(EventQnodePtr eventsQheadPtr,
		  EventQnodePtr eventsQtailPtr)
{
        QnodePtr rqheadPtr = NULL, rqtailPtr = NULL;	//the run/ready queue

    long clock = 0;		//the sim clock time is currently 0
    int idle = 1;		//CPU is initially idle
    Event currentEvent;		//to hold the current event
    Task task;			//the process structure
    double wt = 0;			//waiting time
    double idletime = 0;		//CPU idle time
    FILE *out_file = NULL;	// Link to output file
    double rt = 0;   
    double tt = 0;
    int temp1 = 0;
    int temp2 = 0;
    int isPrevIdle = 1;// 1 = yes, 0 = no
    out_file = fopen("sjf.trace", "w");
    if (out_file == NULL) {
	fprintf(stderr, "Could not open sjf.trace for writing!\n");
	return;
    }

    fprintf(out_file, "Time\tEvent\t\tTask\n");
    while (!isEmptyEQ(eventsQheadPtr)) {
	currentEvent = dequeueevent(&eventsQheadPtr, &eventsQtailPtr);	//get an event from the events list

	clock = currentEvent.time;

	if (currentEvent.type == 1) {	//Departure logic 
	    idle = 1;
	    task = currentEvent.task;
		tt+= clock - task.at;
	    fprintf
		(out_file, "%d\tDeparture\tTask %d (at:%d,bt:%d,pr:%d)\n",
		 clock, task.id, task.at, task.bt, task.pr);
	}

	if (currentEvent.type == 0) {	//Arrival logic
	    task = currentEvent.task;
	    fprintf(out_file, "%d\tArrival\t\tTask %d (at:%d,bt:%d,pr:%d)\n", clock,
		    task.id, task.at, task.bt, task.pr);
	    enqueue(&rqheadPtr, &rqtailPtr, task, SJF);
	}

	if (idle == 1 && !isEmpty(rqheadPtr)) {	//Service logic 
	    idle = 0;
	    currentEvent.task = dequeue(&rqheadPtr, &rqtailPtr);
	    wt += clock - currentEvent.task.at;
            rt+=clock - currentEvent.task.at;
	    currentEvent.type = 1;
	    currentEvent.time = clock + currentEvent.task.bt;
	    enqueueevent(&eventsQheadPtr, &eventsQtailPtr, currentEvent);
	    task = currentEvent.task;
	    fprintf(out_file, "%d\tServing\t\tTask %d (at:%d,bt:%d,pr:%d)\n", clock,
		    task.id, task.at, task.bt, task.pr);
	}
	if (idle == 1 && isPrevIdle==0){
	temp1 = clock;
	isPrevIdle = 1;
	}
	if (idle == 0 && isPrevIdle==1){
	idletime+=clock - temp1;
	isPrevIdle = 0;
	}
	if (temp2==0){
	idletime-=clock;
	temp2=1;
	}
    }

    /* Do the output.
     * Note that waiting time has been done for you here.
     * You will need to add the functionality for delay time, response time, and turnaround time.
     */
	double avgwait = ((double)wt) / ((double)num_tasks) ;
	double avgresp = ((double)rt) / ((double)num_tasks) ;
	double avgturn = ((double)tt) / ((double)num_tasks) ;
	double cputi = ( ( ((double)clock-  (double)idletime)) / (double)clock)*100;

    fprintf(out_file, "\nPerformance Measures:\n");
    fprintf(out_file, "\tAverage waiting time: %.2f\n",avgwait);
    fprintf(out_file, "\tAverage response time: %.2f\n", avgresp);
    fprintf(out_file, "\tAverage turnaround time: %.2f\n", avgturn);
    fprintf(out_file, "\tCPU Utilization: %.2f%%\n", cputi);
    fclose(out_file);
}
