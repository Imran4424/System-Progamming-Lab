#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


char pipeName[] = "RoyalStory";
int fd,fd2;

void signalHandler(int sig)
{
	char reader_msg[512];

	printf("I am here\n");

	fd = open(pipeName,O_RDONLY);
	read(fd,reader_msg,strlen(reader_msg)+1);
	close(fd);

	printf("readed story is:\n%s",reader_msg);
}

int main(int argc, char const *argv[])
{
	signal(SIGTERM,signalHandler);

	printf("My process id: %d\n", getpid());


	while(1);

	return 0;
}