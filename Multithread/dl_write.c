#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>


const BUFF_SIZE = 1024;

char msgBuff[] = "Hello reader,I am writer";


void *pipe_two()
{
	char *pipeName = "Pipe2";
	
	umask(0);	

	int fd2;
	
	mknod(pipeName, S_IFIFO | 0666, 0);

	fd2 = open(pipeName, O_RDONLY);
	
	read(fd2,msgBuff,strlen(msgBuff)+1);
	
	printf("%s\n",msgBuff);

	close(fd2);

}



int main()

{

	int fd;

	

	char *pipeName = "Pipe1";
	
	
	
	
	pthread_t TID[2];
	
	int tdstatus;
	
	tdstatus = pthread_create(&TID[0],NULL,pipe_two,NULL);
	
	if(tdstatus = 0)
	{
		printf("can't create the thread 1");
		
		return;
	}



	umask(0);



	mknod(pipeName, S_IFIFO | 0666, 0);



	fd = open(pipeName, O_WRONLY);

	write(fd, msgBuff, strlen(msgBuff)+1);

	close(fd);
	
	

	


	printf("I am writer\n");

	return 0;

}
