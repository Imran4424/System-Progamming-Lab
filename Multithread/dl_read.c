#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>



const BUFF_SIZE = 1024;

char msgBuff[] = "Hello writer,I am reader";

void *pipe_one()
{
	char *pipeName = "Pipe1";

	umask(0);

	int fd2;
	
	mknod(pipeName, S_IFIFO | 0666, 0);

	fd2 = open( pipeName, O_RDONLY);
	
	read(fd2,msgBuff,strlen(msgBuff)+1);
	
	printf("%s\n",msgBuff);
	
	close(fd2);

}


int main()

{

	int fd;

	

	char *pipeName = "Pipe2";
	
	pthread_t TID[2];
	
	
	
	int tdstatus;
	
	tdstatus = pthread_create(&TID[0],NULL,pipe_one,NULL);
	
	if(tdstatus = 0)
	{
		printf("can't create the thread 1");
		
		return;
	}

	

	umask(0);



	fd = open(pipeName, O_WRONLY);

	write(fd, msgBuff, BUFF_SIZE);

	close(fd);
	
	

	

	printf("I am reader\n");

	return 0;

}
