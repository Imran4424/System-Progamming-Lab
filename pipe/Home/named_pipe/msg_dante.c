#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>

const int m_size = 3000;

int fd ,fd2;

//char *pipeName = "/home/warrior/clone repo/System-Programming-Lab/pipe/home/named_pipe/brotherhood"; //defining pipe

char *pipeNameDante = "msg_brotherhood";
char *pipeNameVergil = "msg_brotherhood2";


int good_bye_count = 0;

void *sender()
{
	char dante_to_vergil[m_size];
	
	while(good_bye_count != 2)
	{
		scanf("%[^\n]",dante_to_vergil);

		if(strcmp(dante_to_vergil,"good bye") == 0)
		{
			good_bye_count++;
		}


		fd = open(pipeNameDante,O_WRONLY);
		write(fd,dante_to_vergil,strlen(dante_to_vergil)+1);
		close(fd);
		
	}	
}


void *receiver()
{
	char dante_received[m_size];
	
	while(good_bye_count != 2)
	{
		fd2 = open(pipeNameVergil,O_RDONLY);
		read(fd2,dante_received,m_size);
		close(fd2);

		printf("vergil: %s\n",dante_received );

		if(strcmp(dante_received,"good bye") == 0)
		{
			good_bye_count++;
		}
	}
}




int main(int argc, char const *argv[])
{
	int tdStatus;

	umask(0); //set file mode creation mask--setting the file creation permission mode

	mknod(pipeNameDante,S_IFIFO|0666, 0); // creating the named pipe and setting up the permissions

	
	printf("Conversation started\n");


	pthread_t TID_1, TID_2;

	

	tdStatus = pthread_create(&TID_1, NULL, sender, NULL);
	if(tdStatus != 0){
		perror("Error during pthread_create()");
		exit(EXIT_FAILURE); // Equivalent of "return 1;".
	}

	


	tdStatus = pthread_create(&TID_2, NULL, receiver, NULL);
	if(tdStatus != 0){
		perror("Error during pthread_create()");
		exit(EXIT_FAILURE);
	} 

	while(1)
	{
        if(good_bye_count == 2)
        {
            break;
        }
	}

	return 0;
}