#include <semaphore.h>
#define MAX_SLEEP_TIME 		5
#define NUMBER_OF_THREADS	5
sem_t sem;
void *worker(void *);

int init(int);

int barrier_point();

