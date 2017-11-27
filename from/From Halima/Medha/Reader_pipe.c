#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

#define BUFF_SIZE 1024

int main(){
	int fd1,fd2;
	pid_t myPID;
	char *pipeName = "WriterReaderPipe7";
	char msgBuff[ BUFF_SIZE ];	
	char msgBuff1[ BUFF_SIZE ];

	myPID = getpid();

	umask(0);
	mknod( pipeName, S_IFIFO | 0666, 0);


	fd1 = open( pipeName, O_RDONLY);
	read( fd1, msgBuff, BUFF_SIZE );
	close(fd1);
	fd2 = open (pipeName, O_RDONLY);
	read( fd2, msgBuff1, BUFF_SIZE );
	close(fd2);

	printf("%s %d %s.\n",msgBuff,myPID,msgBuff1);
	

	return 0;
}
