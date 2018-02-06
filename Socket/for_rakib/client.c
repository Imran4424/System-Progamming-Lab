#include <sys/socket.h>		// For system call: socket(). 
#include <stdio.h>			// For standard input-output.
#include <netinet/in.h>		// For sockaddr_in, sockaddr, htons().  
#include <unistd.h>			// For close().  
#include <arpa/inet.h>
#include <stdbool.h>   //for boolean data
#include <string.h>   // for strcmp()


//global variables

bool file_share_mode = false;
bool rec_again = false;

char file_share[] = "need file";
//int recv_int;


int main() {
    // STEP-1: socket()
    // 1.1. Create a socket.
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 1.2. Specify an address for the above socket.
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(9002); 

    //***************************************
    //**************************************
    //In the very below line, instead of putting 10.20.30.40 put your server's Ip
    //*****************************
    //******************************
    //inet_aton("10.20.30.40", &(server_address.sin_addr));
	server_address.sin_addr.s_addr = INADDR_ANY;

    // STEP-2: connect()
    // 2.1. Connect to the remote socket
    int addr_len;
    struct sockaddr *sockaddr_ptr;
    addr_len = sizeof(server_address);
    sockaddr_ptr = (struct sockaddr *) &server_address;
    connect(client_socket, sockaddr_ptr, addr_len);
    
    
    //declaring variables

    //char server_response[256] ; // For holding server's response
    
    // STEP-3: recv()
    // 3.1. Receive data from the server
    
    printf("Converstation Begins:\n");

    while(1)
    {
        //client receiving

        char server_response[256] ; // For holding server's response
        
        int recv_int = recv(client_socket, &server_response,sizeof(server_response), 0);

        if( recv_int < 0){
            perror("in Recv");
        }

        if(rec_again)
        {
            rec_again = false;
        }

        if(strcmp(server_response,"File received successfully") == 0)
        {
            rec_again = true;
        }

        // 3.2. Check sever's response.

        if(!file_share_mode)
        {
            printf("server: %s\n", server_response);
        }
        else
        {
            char msg[] = "File received successfully";

            FILE *ptr;

            ptr = fopen("client_received_file.txt","w");

            fprintf(ptr, "%s\n",server_response); // to write on file

            printf("%s\n",msg );

            int sending = send(client_socket,&msg,strlen(msg)+1,0);

            
            if(sending < 0)
            {
                perror("In server sending");
            }
            

            fclose(ptr);

            file_share_mode = false;
        }

        if(strcmp(server_response,file_share) == 0)
        {

            
            FILE *ptr;

            ptr = fopen("client_file.txt","r");
            
            if(ptr == NULL)
            {
                printf("Error\n");

                return 0;
            }

            char contents[1024];

            fscanf(ptr,"%[^\n]%*c",contents); // to read file contents

            int sending = send(client_socket, &contents, sizeof(contents), 0);
                
            if(sending < 0)
            {
                printf("file send failed\n");
            }
            else
            {
                printf("File send successful\n");
            }

            fclose(ptr);

            rec_again = true;
        } 
        

        
        char client_response[256];
        
        //client sending

        if(!rec_again)
        {

            printf("in sent end\n");

            scanf ("%[^\n]%*c", client_response);

            int send_int = send(client_socket, &client_response, sizeof(server_response), 0);

            if( send_int < 0){
                perror("in send");
            }
        }
        
        

        if(strcmp(client_response,file_share) == 0)
        {
            file_share_mode = true;
        }


    }


    // STEP-4: close()
    // 4.1. Close the socket
    close(client_socket);

    return 0;
}




