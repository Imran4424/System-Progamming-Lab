#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	pid_t cid,mypid;

	mypid = getpid();

	cid = fork();

	if(cid == 0)
	{
		printf("My pid is: %d\n", mypid);
	}
	else
	{
		printf("My pid is: %d\n", mypid);

		while(1);
	}


	return 0;
}