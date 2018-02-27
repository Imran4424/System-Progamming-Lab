#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


sem_t sem;
int targetPID,targetPID2;
int fd,fd2;

char pipeName[] = "RoyalStory";

void *writer1()
{
	//printf("Hi,I am thread one\n");

	sem_wait(&sem);

	char writer1_story[512];

	printf("Hi, I am writer1, write your your story\n");
	//scanf("%[^\n]",writer1_story);
	kill(targetPID,SIGTERM);

	sprintf(writer1_story,"Hi i am writer1, nice to meet you");

	fd = open(pipeName,O_WRONLY);
	write(fd,writer1_story,strlen(writer1_story)+1);
	close(fd);


	sem_post(&sem);

}

void *writer2()
{
	sem_wait(&sem);

	char writer2_story[512];
	kill(targetPID2,SIGTERM);

	printf("Hi, I am writer2, write your your story\n");
	//scanf("%[^\n]",writer1_story);

	sprintf(writer2_story,"Hi i am writer1, nice to meet you");

	fd = open(pipeName,O_WRONLY);
	write(fd,writer2_story,strlen(writer2_story)+1);
	close(fd);


	sem_post(&sem);

}

int main(int argc, char const *argv[])
{
	sem_init(&sem,0,1);

	

	umask(0); 

	mknod(pipeName,S_IFIFO|0666, 0);


	pthread_t TID,TID2;

	int status;


	targetPID = atoi(argv[1]);
	targetPID2 = atoi(argv[2]);

	printf("%d %d\n",targetPID, targetPID2);

	printf("%s\n", pipeName);


	status = pthread_create(&TID, NULL, writer1, NULL);
	
	if (status != 0) 
	{
		perror("Error during pthread_create()");
		exit(EXIT_FAILURE);	
	}

	status = pthread_create(&TID2, NULL, writer2, NULL);
	
	if (status != 0) 
	{
		perror("Error during pthread_create()");
		exit(EXIT_FAILURE);	
	}

	while(1);

	return 0;
}