/*
===========================================================
FileName: whatsapp.c

About: This is a socket programming code

	   We implement server socket here

Purpose: 






===========================================================
*/


#include <sys/socket.h>		// For system call: socket(). 
#include <stdio.h>			// For standard input-output.
#include <netinet/in.h>		// For sockaddr_in, sockaddr, htons().  
#include <unistd.h>			// For close().  
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>  //for exit()


//global variable
int server_socket;

int good_bye_count = 0;
int good_bye_count2 = 0;
int good_bye_count_final = 0;

int client_socket_connect = 0;
int client_socket;
int client_socket2;
//bool recei_status = false;
bool file_share_mode = false;
char file_share[] = "share file";

char client_one[] = "client1";
char client_two[] = "client2";

bool receive1_state = false;
bool receive2_state = false;

char indication[50];

void *sender()
{
	
    printf("connection stablish With Anik\n");

    // Send message to the client


    //declaring the variables

	char messenger_one_message[1024];

    while(good_bye_count != 2)
    {
        there:

        while(strcmp(indication,client_one) == 0)
        {
            receive1_state = true;


            while(good_bye_count != 2)
            {
                //printf("sender in while\n");

                input:

                scanf ("%[^\n]%*c", messenger_one_message);  ///send good bye to finish the conversation

                //scanf("%[^\n]s",server_message);

                if(strcmp(messenger_one_message,"pause") == 0)
                {
                    printf("with which client you want to resume your chat\n");

                    scanf("%[^\n]%*c",indication);

                    receive1_state = false;

                    goto there;
                }

                if(strcmp(messenger_one_message,"read my file") == 0)
                {
                    FILE *ptr;

                    ptr = fopen("read_me.txt","r");
                    
                    if(ptr == NULL)
                    {
                        printf("Error\n");

                        return 0;
                    }

                    char contents[1024];

                    fscanf(ptr,"%[^\n]%*c",contents); // to read file contents

                    printf("my file contents:\n%s\n",contents);

                    goto input;
                }

                if(strcmp(messenger_one_message,"read received file") == 0)
                {
                    FILE *ptr;

                    ptr = fopen("received_file.txt","r");
                    
                    if(ptr == NULL)
                    {
                        printf("Error\n");

                        return 0;
                    }

                    char contents[1024];

                    fscanf(ptr,"%[^\n]%*c",contents); // to read file contents

                    printf("my file contents:\n%s\n",contents);

                    goto input;
                }
                        
                int sending = send(client_socket, messenger_one_message, sizeof(messenger_one_message), 0);
                        
                if(sending < 0)
                {
                    perror("In server sending");
                }

                if(strcmp(messenger_one_message,file_share) == 0)
                {
                    file_share_mode = true;
                }

                if(strcmp(messenger_one_message,"good bye") == 0)
                {
                        good_bye_count++;
                } 
            }
        }
        
    }
    

	
    if(good_bye_count == 2)
    {
        good_bye_count_final += 2;
    }


	// Close socket
    if (good_bye_count_final == 4)
    {
        close(server_socket);
    }

}




void *received()
{

	char messenger_two_response[1024];

    while(good_bye_count != 2)
    {
        while(strcmp(indication,client_one) == 0)
        {
            while(good_bye_count != 2 && receive1_state == true)
            {
                //printf("receiver in while\n");
                
                /*if(!recei_status)
                {
                    continue;
                }*/

                int receiving = recv(client_socket,messenger_two_response,sizeof(messenger_two_response),0);

            

                if(receiving < 0)
                {
                    printf("received is failed\n");
                }
                else if(!file_share_mode)
                {
                    // 3.2. Check sever's response.
                    printf("Anik: %s\n", messenger_two_response);

                }
               
                if(file_share_mode)
                {

                    char msg[] = "File received successful";

                    FILE *ptr;

                    ptr = fopen("received_file.txt","w");

                    fprintf(ptr, "%s\n",messenger_two_response ); // to write on file

                    printf("%s\n",msg );

                    int sending = send(client_socket,msg,strlen(msg)+1,0);

                    
                    if(sending < 0)
                    {
                        perror("In server sending");
                    }
                    

                    fclose(ptr);

                    file_share_mode = false;
                }
                


                if(strcmp(messenger_two_response,file_share) == 0)
                {

                    //sleep(1);

                    FILE *ptr;

                    ptr = fopen("read_me.txt","r");
                    
                    if(ptr == NULL)
                    {
                        printf("Error\n");

                        return 0;
                    }

                    char contents[1024];

                    fscanf(ptr,"%[^\n]%*c",contents); // to read file contents

                    int sending = send(client_socket, contents, sizeof(contents), 0);
                        
                    if(sending < 0)
                    {
                        printf("file send failed\n");
                    }
                    else
                    {
                        printf("File send successful\n");
                    }

                    fclose(ptr);
                } 
                
                if(strcmp(messenger_two_response,"good bye") == 0)
                {
                    good_bye_count++;
                    
                } 
            }
        }
    }
}


void *sender2()
{
	
    printf("connection stablish with Linkon\n");

    // Send message to the client


    //declaring the variables

	char messenger_one_message[1024];



    while(good_bye_count2 != 2)
    {
        there:

        while(strcmp(indication,client_two) == 0)
        {
            receive2_state = true;

            while(good_bye_count2 != 2)
            {
                //printf("sender in while\n");

                input:

                scanf ("%[^\n]%*c", messenger_one_message);  ///send good bye to finish the conversation

                //scanf("%[^\n]s",server_message);

                if(strcmp(messenger_one_message,"pause") == 0)
                {
                    printf("with which client you want to resume your chat\n");

                    scanf("%[^\n]%*c",indication);

                    receive2_state = false;

                    goto there;
                }

                if(strcmp(messenger_one_message,"read my file") == 0)
                {
                    FILE *ptr;

                    ptr = fopen("read_me.txt","r");
                    
                    if(ptr == NULL)
                    {
                        printf("Error\n");

                        return 0;
                    }

                    char contents[1024];

                    fscanf(ptr,"%[^\n]%*c",contents); // to read file contents

                    printf("my file contents:\n%s\n",contents);

                    goto input;
                }

                if(strcmp(messenger_one_message,"read received file") == 0)
                {
                    FILE *ptr;

                    ptr = fopen("received_file.txt","r");
                    
                    if(ptr == NULL)
                    {
                        printf("Error\n");

                        return 0;
                    }

                    char contents[1024];

                    fscanf(ptr,"%[^\n]%*c",contents); // to read file contents

                    printf("my file contents:\n%s\n",contents);

                    goto input;
                }
                        
                int sending = send(client_socket2, messenger_one_message, sizeof(messenger_one_message), 0);
                        
                if(sending < 0)
                {
                    perror("In server sending");
                }

                if(strcmp(messenger_one_message,file_share) == 0)
                {
                    file_share_mode = true;
                }

                if(strcmp(messenger_one_message,"good bye") == 0)
                {
                        good_bye_count++;
                } 
            }
        }
    }
	

	if(good_bye_count2 == 2)
    {
        good_bye_count_final += 2;
    }


	if (good_bye_count_final == 4)
    {
        close(server_socket);
    }

}




void *received2()
{

	char messenger_two_response[1024];

    while(good_bye_count2 != 2)
    {
        while(strcmp(indication,client_two) == 0)
        {
            while(good_bye_count2 != 2 && receive2_state == true)
            {
                //printf("receiver in while\n");
                
                /*if(!recei_status)
                {
                    continue;
                }*/

                int receiving = recv(client_socket2,messenger_two_response,sizeof(messenger_two_response),0);

            

                if(receiving < 0)
                {
                    printf("received is failed\n");
                }
                else if(!file_share_mode)
                {
                    // 3.2. Check sever's response.
                    printf("Linkon: %s\n", messenger_two_response);

                }
               
                if(file_share_mode)
                {

                    char msg[] = "File received successful";

                    FILE *ptr;

                    ptr = fopen("received_file.txt","w");

                    fprintf(ptr, "%s\n",messenger_two_response ); // to write on file

                    printf("%s\n",msg );

                    int sending = send(client_socket2,msg,strlen(msg)+1,0);

                    
                    if(sending < 0)
                    {
                        perror("In server sending");
                    }
                    

                    fclose(ptr);

                    file_share_mode = false;
                }
                


                if(strcmp(messenger_two_response,file_share) == 0)
                {

                    //sleep(1);

                    FILE *ptr;

                    ptr = fopen("read_me.txt","r");
                    
                    if(ptr == NULL)
                    {
                        printf("Error\n");

                        return 0;
                    }

                    char contents[1024];

                    fscanf(ptr,"%[^\n]%*c",contents); // to read file contents

                    int sending = send(client_socket2, contents, sizeof(contents), 0);
                        
                    if(sending < 0)
                    {
                        printf("file send failed\n");
                    }
                    else
                    {
                        printf("File send successful\n");
                    }

                    fclose(ptr);
                } 
                
                if(strcmp(messenger_two_response,"good bye") == 0)
                {
                    good_bye_count++;
                    
                } 
            }
        }
    }

}



int main()
{
	int tdStatus;
	pthread_t TID[5];


	//printf("sender\n");

	// Create a socket
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12000);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the above socket to the specified IP and port
    int addr_len;
    struct sockaddr *sockaddr_ptr;
    addr_len = sizeof(server_address);
    sockaddr_ptr = (struct sockaddr *)&server_address;
    bind(server_socket, sockaddr_ptr, addr_len);
        

    for(int i = 0;i<4;i++)
    {
	    // Listen
	    listen(server_socket, 5);  // here five indicates number of clients server socket can accept

	    // Accept
    	client_socket_connect = accept(server_socket, NULL, NULL);

	    if(client_socket_connect != 0)
	    {
			if(i == 0)
			{
				client_socket = client_socket_connect;

		        tdStatus = pthread_create(&TID[i], NULL, sender, NULL);

				if(tdStatus != 0){
					perror("Error during pthread_create()");
					exit(EXIT_FAILURE); // Equivalent of "return 1;".
				}
				
				i++;


				tdStatus = pthread_create(&TID[i], NULL, received, NULL);

				if(tdStatus != 0){
					perror("Error during pthread_create()");
					exit(EXIT_FAILURE);
				}
			}
			



			if(i == 2)
			{
				client_socket2 = client_socket_connect;

				tdStatus = pthread_create(&TID[i], NULL, sender2, NULL);

				if(tdStatus != 0){
					perror("Error during pthread_create()");
					exit(EXIT_FAILURE); // Equivalent of "return 1;".
				}
				
				i++;


				tdStatus = pthread_create(&TID[i], NULL, received2, NULL);

				if(tdStatus != 0){
					perror("Error during pthread_create()");
					exit(EXIT_FAILURE);
				}
			}
	    }

    }

    printf("%d %d \n",client_socket,client_socket2 );
    
    
    printf("with which client you want to chat first\n");

	scanf("%[^\n]%*c",indication);

	

	while(1)
	{
        if(good_bye_count == 2)
        {
            break;
        }
	}

	return 0;
}
