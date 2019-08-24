#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_GREEN   "\x1b[32m"

#define MAX_RESOURCES 5
int decrease_count(int count);
int increase_count(int count);
int available_resources = MAX_RESOURCES;
pthread_mutex_t locker;
void *runner(void *);

int main(void){
     pthread_mutex_init(&locker, NULL);
    int i;
	int threadNo = 7;
	pthread_t th[threadNo];
	
	/*
	* In this part you have to 
	*	- create threads 
			-> all threads execute runner() function
			-> each thead passed a unique identifier used as threadID
	*	- wait for all threads to finish (use pthread_join over a for loop) 
	*/
        for(i=0;i<threadNo;i++){   //creating threadNo threads and passing their identifiers
            int *value;
            value=i;
           pthread_create(&th[i], NULL, runner,(void *) value);   
        }

         for (i=0;i<threadNo;i++){  //joining all threads to get the final result "waits for all threads to finish"
           pthread_join(th[i],NULL);
         }
	return 0;
}

void *runner(void *param){
	/*
	* In this part you should:
	*	- print a statement that contain threadID (the one you passed from main) and the 
	*	  amount of available resources in red.
	*	- use rand() function to generate the required resources the thread needs it shoud be between
	*	  1 and 5
	*	- call decrease_count and if you succeed in acquiring resource print threadID and the resources 
	*	  it acquires, if the process cann't acquire resource print threadID and the amount of resources
	*	  in blue (in case of failing to acquire resources).
	*	- Use sleep() function to let the thread sleep for amount of time equals to the required resources
	*	- Call decrease_count after that if appropriate, print the threadID and amount of resources released     
	*	- Before exit print threadID and the amount of resources available
	*	- Use pthread_exit to exit form the thread. 
	*/
   
    int id =(int *) param;
    printf("threadID: "ANSI_COLOR_RED"%d"ANSI_COLOR_RESET" ,amount of available resources: " ANSI_COLOR_RED"%d \n" ANSI_COLOR_RESET,id,available_resources);
     int req = (random()%5) +1; //random() instead of rand() because rand() generates one value for all threads.
           pthread_mutex_lock(&locker);
         if(available_resources>=req){
             int total=0;
             while(decrease_count(req)==0){
                printf("acquiring resources ,threadID: %d ,required resources: %d\n",id,req);
                pthread_mutex_unlock(&locker);
                total+=req;
                 sleep(req);
             }
             increase_count(total);
             printf("releasing resources ,threadID: %d ,released resources: %d\n",id,total);
             pthread_mutex_unlock(&locker);
         }else{ 
             pthread_mutex_unlock(&locker);
              printf("Can't acquire resources ,threadID: "ANSI_COLOR_BLUE"%d" ANSI_COLOR_RESET" ,required resources: " ANSI_COLOR_BLUE"%d\n" ANSI_COLOR_RESET,id,req);
         }
      
         printf("threadID: %d ,amount of available resources: %d \n",id,available_resources);
     pthread_exit(NULL);
}


/*
*	decrease available_resources by count resources 
*	return 0 if sufficient resources available, 
*	othrewise return -1
*/
int decrease_count(int count){
	if(available_resources < count){
		return  -1;
	}else{
		available_resources -= count;
		return 0;
	}
}


// increase available_resources by count
int increase_count(int count){
	available_resources += count;
	return 0;
}
