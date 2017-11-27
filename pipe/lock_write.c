#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main()
{
	int fd;
	char *msgBuff = "Hello World";
	char *pipeName = "WriterReaderPipe";

	umask(0);

	mknod(pipeName, S_IFIFO | 0666, 0);

	fd = open(pipeName, O_WRONLY);
	write(fd, msgBuff, strlen(msgBuff)+1);
	close(fd);

	return 0;
}
