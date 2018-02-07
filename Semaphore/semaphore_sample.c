#include <pthread.h>	// For pthread_create().
#include <stdio.h>	// For sprintf().
#include <unistd.h>	//	For write().
#include <string.h>	// For strlen().
#include <stdlib.h>	// For exit().
#include <semaphore.h>


#define MSG_SZ 200

sem_t sem;


int a = 0,N;


void *thread1 (void *arg)
{
	
	
	
	/* 
		Local variables having common names 
		with other threads. 
	*/
	int i;
	char msg[MSG_SZ];
		
	
	
	for (i = 1; i <= N; i++) {

		sprintf(msg, "%d. I am Thread-1. My task is to increase a. Before (a = a + 1): %d\n", i, a);	
		write(1, msg, strlen(msg) + 1);
		
		//pthread_mutex_lock(&key);
		sem_wait(&sem);

		a = a + 1;
		//pthread_mutex_unlock(&key);	
		
		sem_post(&sem);

		sprintf(msg, "%d. I am Thread-1. My task is to increase a. After (a = a + 1): %d\n", i, a);
		write(1, msg, strlen(msg) + 1);
	}
	
	
}

void *thread2 (void *arg)
{
	/* 
		Local variables having common names 
		with other threads. 
	*/
	int i;
	char msg[MSG_SZ];	
	
	

	for (i = 1; i <= N; i++) {
		sprintf(msg, "%d. I am Thread-2. My task is to decrease a. Before (a = a - 1): %d\n", i, a);	
		write(1, msg, strlen(msg) + 1);
		
		sem_wait(&sem);
		a = a - 1;
		sem_post(&sem);
	
		
		sprintf(msg, "%d. I am Thread-2. My task is to decrease a. After (a = a - 1): %d\n", i, a);
		write(1, msg, strlen(msg) + 1);
	}
	
	
}


int main(int argc, char const *argv[])
{
	int status;
	pthread_t TID,TID2;

	printf("input the number of iteration\n");
	scanf("%d",&N);

	sem_init(&sem,0,1);


	status = pthread_create(&TID, NULL, thread1, NULL);
	
	if (status != 0) 
	{
		perror("Error during pthread_create()");
		exit(EXIT_FAILURE);
	}

	status = pthread_create(&TID2, NULL, thread2, NULL);
	
	if (status != 0) 
	{
		perror("Error during pthread_create()");
		exit(EXIT_FAILURE);	// similar to "return 0;"
	}


	//pthread_join(&TID,NULL);
	//pthread_join(&TID2,NULL);

	while(1);

	sem_destroy(&sem);

	return 0;
}