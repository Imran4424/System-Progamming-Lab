#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>


int main(int argc, char const *argv[])
{
	int shmID;

	const int size = 1024;

	char *shared_memory;

	shmID = shmget(IPC_PRIVATE,size, S_IRUSR | S_IWUSR);
	
	pid_t childPID,myPID;

	childPID = fork();
	myPID = getpid();


	if(myPID < 0)
	{
		printf("fork failed\n");
	}
	else if(childPID == 0)
	{
		shared_memory = (char *) shmat(shmID,NULL,0);
	
		printf("I am Process - %d. \nMessage from my Parent: %s \n",myPID,shared_memory);

		sprintf(shared_memory,"Thank you for creating me. Good bye\n");
		
		shmdt(shared_memory);
	}
	else
	{
		shared_memory = (char *) shmat(shmID,NULL,0);

		sprintf(shared_memory,"Dear, I am Your Parent. Process id - %d",myPID);
	

		pid_t dead_child = wait(NULL);

		printf("\nI am Process %d,I am sorry to say that my child, Process %d is dead now.\n\n",myPID,dead_child);
		
		
		printf("Last message from my child : %s ", shared_memory);

		shmdt(shared_memory);

		shmctl(shmID,IPC_RMID,NULL);
	}

	return 0;
}