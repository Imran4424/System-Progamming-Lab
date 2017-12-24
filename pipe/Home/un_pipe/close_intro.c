#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>



const int read_end = 0;
const int write_end = 1;
const int m_size = 512;

int main()
{
	int Fd[2];
	int Fd2[2];

	pipe(Fd);  //creating pipe
	//pipe(Fd2); //creating second pipe




	pid_t childPID, myPID;

	childPID = fork();
	myPID = getpid();

	if(childPID < 0)
	{
		printf("fork failed\n");
	}
	else if(childPID == 0)
	{
		char child_to_parent[m_size];

		char child_received[m_size];

		close(Fd[write_end]);
		read(Fd[read_end],child_received,m_size);
		close(Fd[read_end]);

		printf("I am Process - %d. \nMessage from my Parent: \n%s\n",myPID,child_received);

		
		sprintf(child_to_parent,"Thank you for creating me. Good Bye\n");
	

		close(Fd[read_end]);
		write(Fd[write_end],child_to_parent,strlen(child_to_parent)+1);
		close(Fd[write_end]);
	}
	else
	{
		char Parent_to_child[m_size];
		char Parent_received[m_size];

		sprintf(Parent_to_child,"Dear, I am Your Parent Process. id: %d\n\n",getpid());


		close(Fd[read_end]);  //closing unused read end
		write(Fd[write_end],Parent_to_child,strlen(Parent_to_child)+1);
		close(Fd[write_end]);  //closing write end
	
		pid_t dead_child = wait(NULL);

		printf("\nI am Process: %d, \nI am sorry to say my child is Dead.Process %d\n",myPID,dead_child);

		close(Fd[write_end]);
		read(Fd[read_end],Parent_received,m_size);
		close(Fd[read_end]);

		printf("Last Message from My child: \n%s\n", Parent_received);

	}


	return 0;
}