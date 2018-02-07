#include <stdio.h>
#include <unistd.h>
#include <signal.h>



int main(int argc, char const *argv[])
{

	int i = 0;

    //printf("pid=%d\n\n",getpid());

    int targetpid;

    scanf("%d",&targetpid);

    while(1)
    {
        kill(targetpid,SIGTERM);

        sleep(1);
    }

	return 0;
}