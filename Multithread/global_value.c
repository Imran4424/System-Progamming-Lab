#include <stdio.h>
#include <pthread.h>

int num = 100;

void *thread_1()
{
	printf("I am thread 1, %d\n",num);
}

void *thread_2()
{
	printf("I am thread 2, %d\n",num);
}

int main()
{
	num = 50;
	
	
	pthread_t TID[5];
	
	int tdstatus;
	
	tdstatus = pthread_create(&TID[0],NULL,thread_1,NULL);
	
	if(tdstatus != 0)
	{
		printf("can't create the thread 1");
		
		return;
	}
	
	//sleep(3);
	
	num = 25;
	
	tdstatus = pthread_create(&TID[1],NULL,thread_2,NULL);
	
	if(tdstatus != 0)
	{
		printf("can't create the thread 2");
		
		return;
	}
	
	
	while(1)
	{
	
	}

}
