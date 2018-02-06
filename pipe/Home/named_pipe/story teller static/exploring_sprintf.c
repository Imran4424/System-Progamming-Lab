#include <stdio.h>


int main(int argc, char const *argv[])
{
	char story[3000];

	sprintf(story,"this is the begining of the story");

	printf("%s\n\n",story );

	sprintf(story,"%s\nHi My name is imran",story);

	printf("%s\n\n",story );

	char info[] = "I am a Programmer";

	sprintf(story,"%s\n%s",story,info);

	printf("%s\n\n",story );

	return 0;
}