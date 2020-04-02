/* Note: You should not modify this file. */

#include <stdlib.h>
#include <stdio.h>

#include "params.h"
#include "task.h"
#include "event.h"
#include "event_q.h"
#include "gentask.h"
#include "simulate.h"

void main()
{
    //the event queue head and tail
    EventQnodePtr eventsQheadPtr = NULL;
    EventQnodePtr eventsQtailPtr = NULL;

    // Get the parameters from the user
    get_params();

    // Generate the set of tasks and display them.
    gen_tasks(&eventsQheadPtr, &eventsQtailPtr, rand_seed);
    displayEvents(eventsQheadPtr);

    // Regenerate and run fifo.  Note that regenerating with the same seed
    // produces the same events.
    gen_tasks(&eventsQheadPtr, &eventsQtailPtr, rand_seed);
    simulate_fifo(eventsQheadPtr, eventsQtailPtr);

    // Now run SJF
    gen_tasks(&eventsQheadPtr, &eventsQtailPtr, rand_seed);
    simulate_sjf(eventsQheadPtr, eventsQtailPtr);

    // Now run priority
    gen_tasks(&eventsQheadPtr, &eventsQtailPtr, rand_seed);
    simulate_rr(eventsQheadPtr, eventsQtailPtr);

    // Now run priority round robin
    gen_tasks(&eventsQheadPtr, &eventsQtailPtr, rand_seed);
    simulate_multilevel(eventsQheadPtr, eventsQtailPtr);
}
