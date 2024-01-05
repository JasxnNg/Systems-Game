#include "networking.h"


int server_handling (int server_socket) {
    int flag = 1; // this will be used to identify the winner 
    char * buff = malloc (sizeof(char) * BUFFER_SIZE); 
    // maybe add a struct here? 
    // this can help identify which one this is from? 
    while (flag) { 
        printf("enter a number: "); 
        fgets(buff, BUFFER_SIZE, stdin);
        // maybe add logic here to check whether or not this
        // part is the right input? 
        // should we have error checking to be local? 

        // it would be cool to have a help command here! 
        int bytes = write(server_socket, buff, BUFFER_SIZE); 
        err(bytes, "could not write to the server socket"); 

        bytes = read(server_socket, buff, BUFFER_SIZE); 
        err(bytes, "could not read the bytes"); 
        // probably check if less than or equal and then throw an error here if 0 bytes
        sscanf(buff, "%d", &flag);  
        
    }
    free(buff); 
    return flag; 

} 



int main (int argc, char *argv[]) {
    char* IP = "127.0.0.1";
    if (argc > 1)
    {
        IP = argv[1];
    }

    int server_socket = client_tcp_handshake(IP);

    
} 

