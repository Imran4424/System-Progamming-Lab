#include <stdio.h>
#include <pthread.h>


#define num_thread 5

void *add()
{
	while(1)
	{
		printf("add is: %d\n",5+3);
	}

}

void *substract()
{

	printf("add is: %d\n",5+3);
}


void *slang()
{
	printf("Don't say it\n");
}

void *who()
{
	printf("DEAD MAN");
}

/*
void *recursion()
{
	func();
	
}

void func()
{
	printf("Who are you\n");
	
	func2();
}


void func2()
{
	printf("I am a programmer\n");
	
	func();
} */

int main()
{
	//sum();
	
	pthread_t TID[5];
	
	int tdstatus;
	
	tdstatus = pthread_create(&TID[0],NULL,add,NULL);
	
	if(tdstatus = 0)
	{
		printf("can't create the thread 1");
		
		return;
	}
	
	
	tdstatus = pthread_create(&TID[1],NULL,substract,NULL);
	
	if(tdstatus = 0)
	{
		printf("can't create the thread 2");
		
		return;
	}
	
	tdstatus = pthread_create(&TID[2],NULL,slang,NULL);
	
	if(tdstatus = 0)
	{
		printf("can't create the thread 3");
		
		return;
	}
	
	tdstatus = pthread_create(&TID[3],NULL,who,NULL);
	
	if(tdstatus = 0)
	{
		printf("can't create the thread 4");
		
		return;
	}
	
	/*
	tdstatus = pthread_create(&TID[4],NULL,recursion,NULL);
	
	if(tdstatus = 0)
	{
		printf("can't create the thread 5");
		
		return;
	} */
	
	while(1)
	{
		printf("I am unstopable\n");
	}
	
	
	return 0;
}
