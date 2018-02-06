#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


const int m_size = 3000;


int main(int argc, char const *argv[])
{
	int fdwrite ,fdread,fdstate; // file descriptors

	

	char *pipeName = "story_teller";
	char *pipeName2 = "reader_response_msg";
	char *state_pipe = "state_description";
	char *like_pipe = "like_state_pipe";

	umask(0); //set file mode creation mask--setting the file creation permission mode

	mknod(pipeName,S_IFIFO|0666, 0); // creating the named pipe and setting up the permissions


	umask(0); //set file mode creation mask--setting the file creation permission mode

	mknod(pipeName2,S_IFIFO|0666, 0); // creating the named pipe and setting up the permissions


	umask(0); //set file mode creation mask--setting the file creation permission mode

	mknod(state_pipe,S_IFIFO|0666, 0); // creating the named pipe and setting up the permissions

	umask(0); //set file mode creation mask--setting the file creation permission mode

	mknod(like_pipe,S_IFIFO|0666, 0); // creating the named pipe and setting up the permissions


	//declaring varibles

	char story[m_size]; // story buff size
	char reader_response[m_size];

	char ready_state_msg[m_size];
	char ready_state_msg_down[m_size];

	sprintf(story,"I am writer Process. id %d.\nI would like tell you a story. I will continue if you like it.",getpid());

	int like_count = 0;
	int dislike_count = 0;

	printf("How many reader do we have\n");

	int num,initial = 1,i;
	scanf("%d",&num);

	printf("write your story\n");

	getchar();

	char my_story[m_size];

	scanf("%[^\n]%*c",my_story);

	sprintf(story,"%s\n%s",story,my_story);

	for(i = 1;i <= num;i++)
	{
		fdwrite = open(pipeName,O_WRONLY);
		write(fdwrite, story, m_size);
		close(fdwrite);

		

		fdread = open(pipeName2,O_RDONLY);
		read(fdread, reader_response, m_size);
		close(fdread);

		printf("%s\n",reader_response);
	}

	

	return 0;
}