/* =====================================================================
	Socket Programming-1
    This progam is for creating a client socket. The client socket 
       (a) is created with a socket() call, 
       (b) is connected with a remote address with a connect() call, 
       (c) receives data with recv() call and 
       (d) finshes its life with a close() call.
	---------------------------------------------------------------------- 
    *** htons(Port_No) is for converting HBO to NBO where
        ----> HBO: Host-Byte-Order
        ----> NBO: Network-Byte-Order
        Byte Order: Big Indian & Little Indian
    ---------------------------------------------------------------------
    Necessary System Calls:
       1. socket(domain, type, protocol)
       2. connect() 
       3. recv()
       4. close()  
   ----------------------------------------------------------------------
    Sangeeta Biswas
    Assistant Professor,
    Dept. of CSE, University of Rajshahi,
    Rajshahi-6205, Bangladesh
   ----------------------------------------------------------------------
    28/8/2017
	======================================================================
*/

/* Directives */
#include <sys/socket.h>		// For system call: socket(). 
#include <stdio.h>			// For standard input-output.
#include <netinet/in.h>		// For sockaddr_in, sockaddr, htons().  
#include <unistd.h>
#include <string.h>			// For close().  

/* Main function*/
int main() {
    // STEP-1: socket()
    // 1.1. Create a socket.
    int client_socket;
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 1.2. Specify an address for the above socket.
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(10000); 
    inet_pton(AF_INET, "10.110.53.203", &(server_address.sin_addr));

    // STEP-2: connect()
    // 2.1. Connect to the remote socket
    int addr_len;
    struct sockaddr *sockaddr_ptr;
    addr_len = sizeof(server_address);
    sockaddr_ptr = (struct sockaddr *) &server_address;
    connect(client_socket, sockaddr_ptr, addr_len);
    
     while(1)
     {
 
 
 		// STEP-3: recv()
       // 3.1. Receive data from the server
       int buf_size;
       char server_response[256] ; // For holding server's response
       buf_size = sizeof(server_response);
       recv(client_socket, &server_response, buf_size, 0);
       
       // 3.2. Check sever's response.
       printf("Message from the server: %s\n", server_response);


       char server_message[256] ;
       char message[256];
       printf("Client's turn:");
       gets(message);
       int msg_size;
       strcpy(server_message,message);
       msg_size = sizeof(server_message);
       int sent = send(client_socket, server_message, msg_size, 0);
        
         
     }

      close(client_socket);

    return 0;
}




