#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>


const BUFF_SIZE = 1024;

char msgBuff[] = "Hello reader";


void *pipe_two(void *pipeName)
{
	umask(0);	

	int fd2;
	
	mknod(pipeName, S_IFIFO | 0666, 0);

	fd2 = (int) open(*(char *)pipeName, O_RDONLY);
	
	read(fd2,msgBuff,strlen(msgBuff)+1);
	
	close(fd2);

}



int main(int num,char *argv[])

{

	int fd;

	

	char *pipeName = "Pipe1";
	
	char *ter_pipe = argv[1];
	
	
	pthread_t TID[2];
	
	int tdstatus;
	
	tdstatus = pthread_create(&TID[0],NULL,pipe_two,&ter_pipe);
	
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
