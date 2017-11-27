#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

int main(){

	int fd;
	char *msgBuff = "Hello, I have an interesting story.";	
	char *pipeName = "WriterReaderPipe1";

	umask(0);

	mknod( pipeName, S_IFIFO|0666, 0);

	fd = open( pipeName, O_WRONLY);
	write( fd, msgBuff, strlen(msgBuff)+1 );

	close(fd);

	return 0;
}
