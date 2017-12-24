#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


const int m_size = 256;

int main(int argc, char const *argv[])
{
	pid_t childPID , myPID;

	char processName[m_size];

	char pipeName[m_size];

	scanf("%s %s", processName, pipeName);

	//pipeName = "OSNoteBook";

	argv[1] = "Writer";
	argv[2] = "Reader";

	int fd;

	childPID = fork();

	//printf("%d\n",childPID);

	if(childPID < 0)
	{
		printf("fork failed\n");
	}
	else if(childPID == 0)
	{
		//argv[0] = "Writer";

		//const char *w = "Writer";

		strcpy(argv[0],"Writer");

		//printf("Writer: %s\n", argv[0]);

		char msg[m_size];

		sprintf(msg,"OS is like the mother of a family who hides all difficulties from kids. Writer - %d", getpid());

		fd = open(pipeName,O_WRONLY);
		write(fd,msg,m_size);
		close(fd);
	}
	else if(childPID > 0)
	{
		//wait(NULL);


		pid_t childPID2 = fork();

		if(childPID2 < 0)
		{
			printf("fork failed\n");
		}
		else if(childPID2 == 0)
		{
			//argv[0] = "Reader";

			//const char *r = "reader";

			strcpy(argv[0],"Reader");

			//printf("Reader: %s\n", argv[0]);

			char received[m_size];

			printf("Hi, I am reader. My PID: %d. I read the latest version of %s\n",getpid(),pipeName);
			printf("==================================================================\n");

			fd = open(pipeName,O_RDONLY);
			read(fd,received,m_size);
			close(fd);

			printf("%s\n",received);

			printf("==================================================================\n");
		}

	}

	while(1);

	return 0;
}