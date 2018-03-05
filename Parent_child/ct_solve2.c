#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	fork();

	printf("My pid: %d\n", getpid());

	fork();

	printf("My parent's PID: %d\n", getppid());

	while(1);

	return 0;
}