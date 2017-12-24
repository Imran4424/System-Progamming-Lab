#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>


int main()
{
	int shmID;

	const int size = 1024;
	char *shmMem;

	shmID = shmget(IPC_PRIVATE, size, S_IRUSR | S_IWUSR);
	
	shmMem = (char *)shmat(shmID, NULL, 0);

	pid_t childPID, myPID;
	
	/*
	   0 > childPID --> unsuccessful
	   0 = childPID --> child process
	   0 < childPID --> parent process 
	*/
	
	sprintf(shmMem,"Dear,I am Your Parent,Process- %d\n",myPID); //to write

	childPID = fork();
	myPID = getpid();

	
	
	if (childPID < 0)
	{
		printf("fork failed \n");
	}
	else if(childPID == 0 )
	{
		printf("I am process- %d . Message from my parent: %s",myPID,shmMem);

		
		sprintf(shmMem,"Thank You for creating me . Good Bye\n"); //to write
	}
	else
	{
		pid_t childPID_DEAD = wait(NULL);

		printf("\nI am Process %d,I am sorry to say that my child, Process %d is dead now.\n\n",myPID,childPID_DEAD);
		
		
		printf("Last message from my child : %s ", shmMem);


		shmdt(shmMem);

		shmctl(shmID,IPC_RMID,NULL);
	}

	

	return 0;
}
