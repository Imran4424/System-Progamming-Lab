#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>

int main(){

	int fd1, fd2, fd3, fd4;
	char *msgBuff = "Hello, I am process -  ";	
	char *msgBuff1 = "I have read a funny story. Should I believe it?";

	char *msgBuff2 ="Hi , I am process - ";
 	char *msgBuff3 = "I would like to tell you a story . i will continue writing if you like.\n [once upon a time there were a frog prince & butterfly princess .Their parent were a Banyan Tree and a river.\n Have you like My story ? [Y/N]\n";

	char *pipeName = "WriterReaderPipe7";
	char *pipeName1 = "WriterReaderPipe8";

	umask(0);

	mknod( pipeName, S_IFIFO|0666, 0);
	// first terminal 
	fd1 = open( pipeName, O_WRONLY);
	write( fd1, msgBuff, strlen(msgBuff)+1 );
    close(fd1);

    fd2 = open( pipeName, O_WRONLY);
	write( fd2, msgBuff1, strlen(msgBuff1)+1 );
	close(fd2);

	// Second terminal 
	fd3 = open( pipeName1, O_WRONLY);
	write( fd3, msgBuff2, strlen(msgBuff2)+1 );
    close(fd3);

    fd4 = open( pipeName1, O_WRONLY);
	write( fd4, msgBuff3, strlen(msgBuff3)+1 );
	close(fd4);

	return 0;
}
