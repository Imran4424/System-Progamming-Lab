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
	int threa_no = *(int*) arg;

	sem_wait(&sem);

	int i;

	for(i = 0;i<200;i++)
	{
		a = a+5;
		printf("I am thread NO: %d\n",threa_no);
	
		printf("%d\n", a);
	}

	sem_post(&sem);

	
	
	
}

void *thread2 (void *arg)
{
	int threa_no = *(int*) arg;
	

	sem_wait(&sem);

	int i;

	for(i = 0;i<200;i++)
	{
		printf("I am thread NO: %d\n",threa_no);
	
		a = a - 3;

		printf("%d\n", a);
	}

	sem_post(&sem);
	
}

void *thread3 (void *arg)
{
	int threa_no = *(int*) arg;

	sem_wait(&sem);

	int i;

	for(i = 0;i<200;i++)
	{
		printf("I am thread NO: %d\n",threa_no);
	
		a = a+10;

		printf("%d\n", a);
	}

	sem_post(&sem);
	
}


int main(int argc, char const *argv[])
{
	int status;
	pthread_t TID,TID2,TID3;

	//printf("input the number of iteration\n");
	//scanf("%d",&N);

	sem_init(&sem,0,2);

	int a[] = {1,2,3};


	status = pthread_create(&TID, NULL, thread1, &a[0]);
	
	if (status != 0) 
	{
		perror("Error during pthread_create()");
		exit(EXIT_FAILURE);
	}

	status = pthread_create(&TID2, NULL, thread2, &a[1]);
	
	if (status != 0) 
	{
		perror("Error during pthread_create()");
		exit(EXIT_FAILURE);	// similar to "return 0;"
	}

	status = pthread_create(&TID3, NULL, thread3, &a[2]);
	
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