#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

#define BUFF_SIZE 1024

int main(){
	int fd3,fd4;
	pid_t myPID;
	char *pipeName1 = "WriterReaderPipe8";
	char msgBuff2[ BUFF_SIZE ];	
	char msgBuff3[ BUFF_SIZE ];

	myPID = getpid();

	umask(0);
	mknod( pipeName1, S_IFIFO | 0666, 0);


	fd3 = open( pipeName1, O_RDONLY);
	read( fd3, msgBuff2, BUFF_SIZE );
	close(fd3);
	fd4 = open (pipeName1, O_RDONLY);
	read( fd4, msgBuff3, BUFF_SIZE );
	close(fd4);

	printf("%s %d %s.\n",msgBuff2,myPID,msgBuff3);
	

	return 0;
}
