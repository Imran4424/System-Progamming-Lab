#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include <sys/shm.h>



#define size_b 80
#define READ_END 0
#define WRITE_END 1

int main()
{
	int fd[2];

	char *msg ="I am a Programmer.";
	char msg2[size_b];
	
	pipe(fd); // creating a pipe


	//close(fd[READ_END]);   //close(fd[0]);

	write(fd[WRITE_END],msg,size_b);
	//close(fd[WRITE_END]);
	

	
	//close(fd[WRITE_END]);
	read(fd[READ_END],msg2,size_b);
	//close(fd[READ_END]); 

	printf("My msg for me %s \n",msg2);

	return 0;
}

