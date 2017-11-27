#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

#define BUFF_SIZE 1024

int main()
{
	int fd;
	char *pipeName = "WriterReaderPipe1";
	char msgBuff[ BUFF_SIZE ];	

	umask(0);
	mknod( pipeName, S_IFIFO | 0666, 0);


	fd = open( pipeName, O_RDONLY);
	read( fd, msgBuff, BUFF_SIZE );
	close(fd);

	printf("Message from writer : %s\n",msgBuff);
	

	return 0;
}
