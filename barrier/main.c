/**
 * Script  for testing the barrier implementation.
 *
 * Usage:
 *	./testbarrier <number of threads>
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "barrier.h"

int main(int argc, char *argv[])
{
	/*if (argc != 2) {
		fprintf(stderr,"Usage: ./testbarrier <number of threads>\n");
		return -1;
	}

	int i;
	int number = atoi(argv[1]);*/
    int i;
    int number=5;

	pthread_t workers[number];

	if (init(number) != 0){
            return -1;
        }    

	for (i = 0; i < number; i++) {
	     pthread_create(&workers[i], 0, worker,0);
	}

	for (i = 0; i < number; i++){
             pthread_join(workers[i], 0);
        }
        sem_destroy(&sem);
        printf("Everything is OK");
         
	return 0;
}
