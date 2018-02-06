#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


const int m_size = 3000;

int main(int argc, char const *argv[])
{
	int fdread ,fdwrite,fdstate; // file descriptors

	
	//declaring pipe names

	char *pipeName = "story_teller";
	char *pipeName2 = "reader_response_msg";
	char *state_pipe = "state_description";

	//declaring variables

	char read_story[m_size];
	char response[m_size];
	char response_message[m_size];

	char liked_msg[m_size];
	char dislike_msg[m_size];

	char ready_state_msg[m_size];

	sprintf(liked_msg,"Story liked by process %d",getpid());
	sprintf(dislike_msg,"Story disliked by process %d",getpid());

	sleep(1);

	fdread = open(pipeName,O_RDONLY);
	read(fdread, read_story, m_size);
	close(fdread);

	printf("%s\n",read_story );

	fdwrite = open(pipeName2,O_WRONLY);
	write(fdwrite, dislike_msg, m_size);
	close(fdwrite);

	return 0;
}