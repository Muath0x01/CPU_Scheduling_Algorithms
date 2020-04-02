/* Note: You should not modify this file. */

struct event {			//an event event
    int type;			//event type 0:arrival, 1: departure
    int time;			//event time
    Task task;			//the process
};
typedef struct event Event;
typedef Event *EventPtr;
