#include <time.h>
#include <stdio.h>
#include "barrier.h"


/**
 * Each thread does work for awhile and then waits for all other threads.
 */
void *worker(void *worker)
{
	int sleep_time;

	/* sleep for a random period of time */
	sleep_time = (int) ( (random() % MAX_SLEEP_TIME) + 1);
	printf("sleeping for %d seconds\n",sleep_time);
	sleep(sleep_time);
	/* now wait for other threads to arrive */
	int res=barrier_point();
        if(res==0)	
            printf("out of the barrier\n");
        else
             printf("can't leave the barrier\n");
        pthread_exit(NULL);

}
