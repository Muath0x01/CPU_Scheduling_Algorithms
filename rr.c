#include <stdlib.h>
#include <stdio.h>

#include "params.h"
#include "task.h"
#include "queue.h"
#include "event.h"
#include "event_q.h"

void simulate_rr(EventQnodePtr eventsQheadPtr,
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
    int firstService[num_tasks];
    int lastDepartue[num_tasks];
    for (temp1=0;temp1<num_tasks;temp1++){
	firstService[temp1]=0;
	lastDepartue[temp1]=0;
	}
	temp1=0;
    out_file = fopen("rr.trace", "w");
    if (out_file == NULL) {
	fprintf(stderr, "Could not open rr.trace for writing!\n");
	return;
    }

    fprintf(out_file, "Time\tEvent\t\tTask\n");
    while (!isEmptyEQ(eventsQheadPtr)) {
	currentEvent = dequeueevent(&eventsQheadPtr, &eventsQtailPtr);	//get an event from the events list

	clock = currentEvent.time;
	    task = currentEvent.task;
	if (currentEvent.type == 1) {	//Departure logic
	    idle = 1;
	
	if(currentEvent.task.bt>0){
	currentEvent.time=clock;
	enqueue(&rqheadPtr,&rqtailPtr,currentEvent.task, RR);
	fprintf(out_file, "%d\tPreempt\t\tTask %d (at:%d,bt:%d,pr:%d)\n",clock, currentEvent.task.id, currentEvent.task.at, currentEvent.task.bt+quantum_time, currentEvent.task.pr);
	lastDepartue[currentEvent.task.id]=clock;
	} else {
	int temp3 = firstService[currentEvent.task.id]%quantum_time;
	if (temp3 == 0) temp3 = quantum_time;
fprintf(out_file, "%d\tDeparture\tTask %d (at:%d,bt:%d,pr:%d)\n", 	clock, currentEvent.task.id, currentEvent.task.at, temp3, currentEvent.task.pr);
		tt+= clock - currentEvent.task.at;

	}
	}

	if (currentEvent.type == 0) {	//Arrival logic
	    task = currentEvent.task;
	    fprintf(out_file, "%d\tArrival\t\tTask %d (at:%d,bt:%d,pr:%d)\n", clock,
		    task.id, task.at, task.bt, task.pr);
	    enqueue(&rqheadPtr, &rqtailPtr, task, RR);
	}

	if (idle == 1 && !isEmpty(rqheadPtr)) {	//Service logic 
	    idle = 0;

	    currentEvent.task = dequeue(&rqheadPtr, &rqtailPtr);
		    task = currentEvent.task;

	    if (firstService[currentEvent.task.id]==0){
	    rt+=clock - currentEvent.task.at;
	    wt += clock - currentEvent.task.at;
	    firstService[currentEvent.task.id]=currentEvent.task.bt;
	  }
	else {
 	    wt += clock - lastDepartue[currentEvent.task.id];
		}
	    fprintf(out_file, "%d\tServing\t\tTask %d (at:%d,bt:%d,pr:%d)\n", clock,
		    task.id, task.at, task.bt, task.pr);

	    int st;
	    if(currentEvent.task.bt<quantum_time){
	    st=currentEvent.task.bt;}
	    else
	    {st=quantum_time;}
	//if (!isEmpty(rqheadPtr) && st==quantum_time){
	    currentEvent.time=clock+st;
	    currentEvent.task.bt-=st;
	currentEvent.type = 1;
	    enqueueevent(&eventsQheadPtr, &eventsQtailPtr, currentEvent);


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
//*0.19250825656

    fprintf(out_file, "\nPerformance Measures:\n");
    fprintf(out_file, "\tAverage waiting time: %.2f\n",avgwait);
    fprintf(out_file, "\tAverage response time: %.2f\n", avgresp);
    fprintf(out_file, "\tAverage turnaround time: %.2f\n", avgturn);
    fprintf(out_file, "\tCPU Utilization: %.2f%%\n", cputi);
    fclose(out_file);
}

