#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


const int m_size = 3000;

int main(int argc, char const *argv[])
{
	int fdreadwrite ,fdwrite; // file descriptors

	

	char *pipeName = "story_teller";
	char *pipeName2 = "reader_response_msg";

	char read_story[m_size];
	char response[50];
	char response_message[m_size];

	char liked_msg[m_size];
	char dislike_msg[m_size];

	sprintf(liked_msg,"Story liked by process %d",getpid());
	sprintf(dislike_msg,"Story disliked by process %d",getpid());


	fdreadwrite = open(pipeName,O_RDWR);

	read(fdreadwrite, read_story, m_size);

	printf("%s\n",read_story );

	printf("like or dislike\n");

	scanf("%[^\n]%*c",response);

	write(fdreadwrite, response, m_size);

	close(fdreadwrite);

	if(strcmp(response,"like") == 0)
	{
		sprintf(response_message,"%s",liked_msg);
	}

	if(strcmp(response,"dislike") == 0)
	{
		sprintf(response_message,"%s",dislike_msg);
	}

	fdwrite = open(pipeName2,O_WRONLY);
	write(fdwrite,response_message,m_size);
	close(fdwrite);


	return 0;
}