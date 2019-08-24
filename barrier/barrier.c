#include <stdio.h>
#include <errno.h>
#include "barrier.h"
#include <pthread.h>
#include <semaphore.h>

/* the number of threads to wait for */
int waiting_size;

/* the number of waiting threads */
int count;	

pthread_mutex_t locker;

/**
 * Initialize the barrier
 */
int init(int parties)
{
	//write your code here
    if (pthread_mutex_init(&locker, NULL) != 0) {
        fprintf(stderr,"Unable to create mutex lock\n");
          return -1;
    }
    if ( sem_init(&sem, 0,1) == -1) {
        fprintf(stderr,"Unable to create semaphore\n");
          return -1;
    }
    count = 0;
    waiting_size = parties;
    return 0;
}

/**
 * The barrier
 */
int barrier_point()
{
	//write your code here
        /* lock count_lock mutex*/
         pthread_mutex_lock(&locker);
        /* increment the number of waiting threads */
        count++;
        /*Unlock count_lock mutex*/
         printf("count: %d,waiting_size: %d\n",count,waiting_size);
         pthread_mutex_unlock(&locker);
         sem_wait(&sem);
         while(count!=waiting_size){
         }
          sem_post(&sem); 
        return 0;
}
