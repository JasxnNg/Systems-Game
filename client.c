#include "networking.h"
#include "game.h"
#include <pwd.h> 

// int fdError(int errInt, int size, ) {
//     if (errInt )
// } 


void checkConnection (int server_socket, char * message) {
    if (server_socket <= 0) {
        printf("Error: %s\n", message);
        if (server_socket == 0 ) {
            printf("Lost connection with the server\n");
        }
        exit(1);
    }
}


int server_handling (int server_socket) {
    int flag; // this will be used to identify the winner
    flag = 1;  
    char * buff = malloc (sizeof(char) * BUFFER_SIZE); 
    // maybe add a struct here? 
    // this can help identify which one this is from? 
    while ( flag) {
        // we should probably make the read in a struct as well 
        // this is to know when to stop and how to win
        strcpy(buff, "Ready to play");
        int bytes = write(server_socket, buff, BUFFER_SIZE);
        checkConnection(bytes, "could not write to the server socket [LINE 28]"); 
        
        // COMMENT THIS OUT LATER
        printf("%d bytes written [LINE 28]\n", bytes);
    

        bytes = read(server_socket, buff, BUFFER_SIZE);
        checkConnection(bytes, "could not read from the server socket [LINE 32]"); 

        printf("%s %d\n", buff, bytes); 

        char * data = malloc(sizeof(char) * BUFFER_SIZE);
        bytes = read(server_socket, data, BUFFER_SIZE); 
        checkConnection(bytes, "could not read [LINE 41]"); 

        //COMMENT THIS OUT LATER
        printf("%s %d [LINE 41]\n", data, bytes);

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
        bytes = write(server_socket, buff, BUFFER_SIZE); 
        checkConnection(bytes, "could not write to the server socket [LINE 62]"); 

        bytes = read(server_socket, buff, BUFFER_SIZE); 
        checkConnection(bytes, "could not read from server socket [LINE 65]"); 

        // probably check if less than or equal and then throw an error here if 0 bytes
        sscanf(buff, "%d", &flag);  
        // free(data); 

        bytes = read(server_socket, buff, BUFFER_SIZE); 
        checkConnection(server_socket, "could not read bytes [LINE 72]"); 

        printf("%s\n", buff);
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
    char * userName = malloc(sizeof (char) * NAME_SIZE); 
    uid_t uid = geteuid(); 
    struct passwd *pw = getpwuid(uid);
    if (pw) {
        strcpy (userName, pw->pw_name); 
    }
    else { // if we can't retrieve a username for this 
        printf("enter a username: "); 
        if (fgets(userName, NAME_SIZE, stdin)) {
            printf("failed to fgets");
            exit(1);  
        } 
        
    }  

    int server_socket = client_tcp_handshake(IP);
    printf("user: %s joined server successfully!\n", userName);
    int bytes = write(server_socket, userName, NAME_SIZE);  // write the user to the server
    err(bytes, "could not write the bytes to the server socket"); 
    // add logic for everything here 
    server_handling (server_socket); 

    char * data = malloc(sizeof(char) * BUFFER_SIZE);
    bytes = read(server_socket, data, BUFFER_SIZE); 
    checkConnection(bytes, "could not read LINE 106"); 
  

    printf("%s %d\n", data, bytes);

    free(userName);
} 

