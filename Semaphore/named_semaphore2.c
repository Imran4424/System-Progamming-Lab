#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <semaphore.h>

const int m_size = 3000;


int main(int argc, char const *argv[])
{
	int fd ,fd2;

	

	char *pipeName = "mknod_brotherhood";

	char vergil_to_dante[m_size];
	char vergil_received[m_size];
	

	fd2 = open(pipeName,O_RDONLY);
	read(fd2,vergil_received,m_size);
	close(fd2);

	printf("dante: %s\n",vergil_received );


	printf("dante is waiting for your reply\n");

	scanf("%[^\n]",vergil_to_dante);


	fd = open(pipeName,O_WRONLY);
	write(fd,vergil_to_dante,strlen(vergil_to_dante)+1);
	close(fd);


	return 0;
}