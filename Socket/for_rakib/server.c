#include <sys/socket.h> 	
#include <netinet/in.h>
#include <unistd.h> 		
#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>   //for boolean data
#include <string.h>   // for strcmp()


//global variables

bool file_share_mode = false;
bool rec_again = false;

char file_share[] = "need file";

//int recv_int;


int main() {
    // Create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the above socket to the specified IP and port
    int addr_len;
    struct sockaddr *sockaddr_ptr;
    addr_len = sizeof(server_address);
    sockaddr_ptr = (struct sockaddr *)&server_address;
    bind(server_socket, sockaddr_ptr, addr_len);
        
    // Listen
    listen(server_socket, 5);

    // Accept
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // Send message to the client
    
    //declaring varibales
    //char client_response[256];
   

    printf("Converstation Begins:\n");

    while(1)
    {
        //server sending
        char server_message[256];

        if(!rec_again)
        {

            printf("in sent end\n");

            scanf ("%[^\n]%*c", server_message);

            int send_int = send(client_socket, server_message, sizeof(server_message), 0);
            
            if(send_int< 0)
            {
                perror("in send");
            }
        }

        

        if(strcmp(server_message,file_share) == 0)
        {
            file_share_mode = true;
        }

        //Recieve message from the client

        char client_response[256];

        int recv_int = recv(client_socket, client_response, sizeof(client_response), 0);

        if(recv_int< 0){
            perror("in recv");
        }

        if(rec_again)
        {
            rec_again = false;
        }

        if(strcmp(client_response,"File received successfully") == 0)
        {
            rec_again = true;
        }

        if(!file_share_mode)
        {
            printf("clinet: %s\n", client_response);
        }
        else
        {
            char msg[] = "File received successfully";

            FILE *ptr;

            ptr = fopen("server_received_file.txt","w");

            fprintf(ptr, "%s\n",client_response); // to write on file

            printf("%s\n",msg );

            int sending = send(client_socket,msg,strlen(msg)+1,0);

            
            if(sending < 0)
            {
                perror("In server sending");
            }
            

            fclose(ptr);

            file_share_mode = false;
        }

        if(strcmp(client_response,file_share) == 0)
        {

            //sleep(1);

            FILE *ptr;

            ptr = fopen("server_file.txt","r");
            
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

            rec_again = true;
        } 
        

    }

    // Close socket
    close(server_socket);

}
