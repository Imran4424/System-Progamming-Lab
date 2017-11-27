#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>


#define size_b 80
#define READ_END 0
#define WRITE_END 1


int main()
{
	int fd[2];

	char msg[] ="Dear,I am Your Parent Process\n\n";
	char msg2[size_b];
	
	pipe(fd); // creating a pipe

	//close(fd[WRITE_END]);

	write(fd[WRITE_END],msg,size_b);


	

	pid_t childPID, myPID;
	
	/*
	   0 > childPID --> unsuccessful
	   0 = childPID --> child process
	   0 < childPID --> parent process 
	*/
	
	//sprintf(shmMem,"Dear,I am Your Parent,Process- %d\n",myPID); //to write

	childPID = fork();
	myPID = getpid();

	
	
	if (childPID < 0)
	{
		printf("fork failed \n");
	}
	else if(childPID == 0 )
	{
		read(fd[READ_END],msg2,size_b);


		printf("I am process- %d . Message from my parent: %s",myPID,msg2);

		
		write(fd[WRITE_END],"Thank You for creating me . Good Bye\n",size_b);
		
		//read(fd[READ_END],msg2,size_b);	
		
		//sprintf(shmMem,"Thank You for creating me . Good Bye\n"); //to write
	}
	else
	{
		pid_t childPID_DEAD = wait(NULL);

		printf("\nI am Process %d,I am sorry to say that my child, Process %d is dead now.\n\n",myPID,childPID_DEAD);
		
		read(fd[READ_END],msg2,size_b);
		printf("Last message from my child : %s ", msg2);

	}

	

	return 0;
}
