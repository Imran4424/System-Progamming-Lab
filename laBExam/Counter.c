#include <pthread.h>
#include <stdio.h>
#include <string.h>


pthread_mutex_t key;

void *Thread1(void *m,void *n, void *o)
{
	int a = *(char*) m;
	int d = *(char*) n;
	int n = *(char*) o;

	printf("%d %d %d \n",a,d,n);

	// pthread_mutex_lock(&key);
	// printf("%d + %d = %d\n",a,d,a+d );
	// a = a+d;
	// pthread_mutex_unlock(&key);

}

void *Thread2(void *m,void *n, void *o)
{

	int a = *(char*) m;
	int d = *(char*) n;
	int n = *(char*) o;

	printf("%d %d %d \n",a,d,n);

	// pthread_mutex_lock(&key);
	// printf("%d - %d = %d\n",a,d,a-d );
	// a = a-d;
	// pthread_mutex_unlock(&key);

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
	
	int a = atoi(argv[1]);
	int d = atoi(argv[2]);
	int n = atoi(argv[3]);



	printf("%d %d %d \n",a,d,n);

	pthread_t TID_1,TID_2;
	int tdStatus;

	tdStatus = pthread_create(&TID_1,NULL,Thread1,&a,&d,&n);

	if(tdStatus != 0)
	{
		printf("Thread1 is not created\n");
	}

	tdStatus = pthread_create(&TID_2,NULL,Thread2,&a,&d,&n);

	if(tdStatus != 0)
	{
		printf("Thread1 is not created\n");
	}

	return 0;
}