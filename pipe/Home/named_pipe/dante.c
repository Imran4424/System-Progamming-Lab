#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


const int m_size = 3000;


int main(int argc, char const *argv[])
{
	int fd ,fd2;

	//char *pipeName = "/home/warrior/clone repo/System-Programming-Lab/pipe/home/named_pipe/brotherhood"; //defining pipe

	char *pipeName = "brotherhood";

	char dante_to_vergil[m_size];
	char dante_received[m_size];

	printf("vergil is waiting for your reply\n");

	scanf("%[^\n]",dante_to_vergil);


	fd = open(pipeName,O_WRONLY);
	write(fd,dante_to_vergil,strlen(dante_to_vergil)+1);
	close(fd);

	fd2 = open(pipeName,O_RDONLY);
	read(fd2,dante_received,m_size);
	close(fd2);

	printf("vergil: %s\n",dante_received );

	return 0;
}