#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


const int m_size = 3000;


int main(int argc, char const *argv[])
{
	int fdwrite ,fdread; // file descriptors

	

	char *pipeName = "story_teller";
	char *pipeName2 = "reader_response_msg";

	umask(0); //set file mode creation mask--setting the file creation permission mode

	mknod(pipeName,S_IFIFO|0666, 0); // creating the named pipe and setting up the permissions


	umask(0); //set file mode creation mask--setting the file creation permission mode

	mknod(pipeName2,S_IFIFO|0666, 0); // creating the named pipe and setting up the permissions

	char story[m_size]; // story buff size
	char reader_response[m_size];

	sprintf(story,"I am writer Process. id %d.\nI would like tell you a story. I will continue if you like it.",getpid());

	int like_count = 0;
	int dislike_count = 0;

	printf("How many reader do we have\n");

	int num,initial = 1;
	scanf("%d",&num);

	while(like_count >= dislike_count)
	{
		if(initial)
		{
			printf("write your story\n");

			initial = 0;
		}
		else
		{
			printf("Your current story is:\n");
			printf("%s\n",story);

			printf("continue to write your story\n");
		}

		char resume_story[m_size];
		scanf("%[^\n]%*c",resume_story);

		sprintf(story,"%s \n%s",story,resume_story);


		for(int i=1;i<=num;i++)  //looping n times for n number of reader
		{
			fdwrite = open(pipeName,O_WRONLY);
			write(fdwrite, story, m_size);
			close(fdwrite);


			fdread = open(pipeName,O_RDONLY);
			read(fdread, reader_response, m_size);
			close(fdread);

			if(strcmp(reader_response,"like") == 0)
			{
				like_count++;
			}

			if(strcmp(reader_response,"dislike") == 0)
			{
				dislike_count++;
			}

			fdread = open(pipeName2,O_RDONLY);
			read(fdread, reader_response, m_size);
			close(fdread);

			printf("%s\n",reader_response);

		}

	}


	return 0;
}