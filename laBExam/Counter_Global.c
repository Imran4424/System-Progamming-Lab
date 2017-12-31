#include <pthread.h>
#include <stdio.h>
#include <string.h>

int a,d,n;

pthread_mutex_t key;

void *Thread1()
{
	printf("Thread1\n");

	int i;

	//printf("%d %d %d \n",a,d,n);

	for(i=1;i<=n;i++)
	{
		pthread_mutex_lock(&key);
		printf("%d + %d = %d\n",a,d,a+d );
		a = a+d;
		pthread_mutex_unlock(&key);
	}

}

void *Thread2()
{
	printf("Thread2\n");

	int i;

	//printf("%d %d %d \n",a,d,n);

	for(i=1;i<=n;i++)
	{
		pthread_mutex_lock(&key);
		printf("%d + %d = %d\n",a,d,a-d );
		a = a-d;
		pthread_mutex_unlock(&key);
	}

}

/*int char_to_int(const char **num)
{
	int l = strlen(*num);

	printf("%d\n", l);

	int temp = 0;

	int i;

	for(i=0;i<l;i++)
	{
		temp = ((temp*10) + (int*) (num[i]) - 48);
	}

	return temp;
}*/

int main(int argc, char const *argv[])
{
	
	a = atoi(argv[1]);
	d = atoi(argv[2]);
	n = atoi(argv[3]);



	//printf("%d %d %d \n",a,d,n);

	pthread_t TID_1,TID_2;
	int tdStatus;

	tdStatus = pthread_create(&TID_1,NULL,Thread1,NULL);

	if(tdStatus != 0)
	{
		printf("Thread1 is not created\n");
	}

	tdStatus = pthread_create(&TID_2,NULL,Thread2,NULL);

	if(tdStatus != 0)
	{
		printf("Thread2 is not created\n");
	}

	while(1);

	return 0;
}