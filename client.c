#include "networking.h"
#include "game.h"
#include <pwd.h> 

// int fdError(int errInt, int size, ) {
//     if (errInt )
// } 

int server_handling (int server_socket) {
    int * flag; // this will be used to identify the winner
    (* flag) = 1;  
    char * buff = malloc (sizeof(char) * BUFFER_SIZE); 
    // maybe add a struct here? 
    // this can help identify which one this is from? 
    while (* flag) { 

        // we should probably make the read in a struct as well 
        // this is to know when to stop and how to win

        // struct clientDetails * data = malloc(sizeof(struct clientDetails)); 
        // read(server_socket, data, sizeof (struct clientDetails)); 

        printf("enter a number: "); 
        fgets(buff, BUFFER_SIZE, stdin);
        buff = strsep(&buff, "\n"); 
        // preprocess the buff

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
        //free(data); 
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


    // this is for getting your user  
    char * userName = malloc(sizeof (char) * BUFFER_SIZE); 
    uid_t uid = geteuid(); 
    struct passwd *pw = getpwuid(uid);
    if (pw) {
        strcpy (userName, pw->pw_name); 
    }
    else { // if we can't retrieve a username for this 
        printf("enter a username: "); 
        if (fgets(userName, BUFFER_SIZE, stdin)) {
            printf("failed to fgets");
            exit(1);  
        } 
        
    }  

    int server_socket = client_tcp_handshake(IP);
    printf("user: %s joined server successfully!\n", userName);
    int bytes = write(server_socket, userName, BUFFER_SIZE);  // write the user to the server
    // add logic for everything here 
    server_handling (server_socket); 

    free(userName);
} 

