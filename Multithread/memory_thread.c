#include <pthread.h>  // thread creation
#include <stdio.h>   // printf , scanf
#include <string.h>

char indication[100];


void *sum()
{

	int a,b;
	
	while(1)
	{
		while(strcmp(indication,"add") == 0)
		{

			scanf("%d %d", &a,&b);

			printf("%d\n",a+b );



			char inc[50];

			printf("Do you want to stay\n");
			scanf("%s",inc);
			
			if(strcmp(inc,"exit") == 0)
			{
				break;
			}
		}

		if(strcmp(indication,"add") == 0)
		{
			scanf("%[^\n]s",indication);
		}
	}
	
}

void *multipication()
{
	while(1)
	{
		while(strcmp(indication,"multi") == 0)
		{
			int a,b;

			scanf("%d %d", &a,&b);

			printf("%d\n",a*b );

			char inc[50];

			printf("Do you want to stay\n");
			scanf("%[^\n]s",inc);

			if(strcmp(inc,"exit") == 0)
			{
				break;
			}
		}

		if(strcmp(indication,"multi") == 0)
		{
			scanf("%[^\n]s",indication);
		}
	}
}




int main()
{
	int tdstatus;
	pthread_t thread1,thread2, thread3; // these variables will hold thread ID

	tdstatus = pthread_create(&thread1,NULL,sum,NULL);

	if(tdstatus != 0)
	{
		printf("thread creation failed\n");
	}

	tdstatus = pthread_create(&thread2,NULL,multipication,NULL);

	if (tdstatus != 0)
	{
		
		printf("thread creation failed\n");
	}

	

	printf("I am main thread\n");

	printf("where you want to go\n");

	scanf("%[^\n]s",indication);

	while(1);

	return 0;
}