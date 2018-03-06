#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>




const int BUFF_SIZE = 1024;



int main(int num,char *argv[])

{

	int fd;

	char msgBuff[BUFF_SIZE];

	char pipeName[] = "Pipe2";

	

	umask(0);



	fd = open(pipeName, O_WRONLY);

	write(fd, msgBuff, BUFF_SIZE);

	close(fd);

	int fd2;
	
	mknod(argv[1], S_IFIFO | 0666, 0);

	fd2 = open(argv[1], O_RDONLY);
	
	read(fd2,msgBuff,strlen(msgBuff)+1);
	
	close(fd2);

	printf("I am reader\n");

	return 0;

}
