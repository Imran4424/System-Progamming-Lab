#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

char msg[30];
int i;

void signalHandler(int sig)
{
	sprintf(msg,"Signal NO-%d is sent to me. I was ordered to be terminated. But I am ignoring it.\n", sig);
	write(1, msg, strlen(msg) + 1);
}


int main(int argc, char const *argv[])
{
	pid_t myPID;
	

	/* To print PID so that we can pass it to 'signalSender'. */
	myPID = getpid();
	sprintf(msg,"My PID-%d.\n", myPID);
	write(1, msg, strlen(msg) + 1);


	signal(SIGTERM, signalHandler);

	while(1)
	{
		/*sprintf(msg,"i = %d\n", i);
		write(1, msg, strlen(msg) + 1);
		i++;
		sleep(1);*/
	}

	return 0;
}