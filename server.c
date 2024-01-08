#include "networking.h"
#include "game.h"
#include <sys/select.h>

struct clientDetails* retrieveNumber(struct clientDetails* client1, struct clientDetails* client2){
  //helper function
  //Gets the number value of a guess from either client
    fd_set read_fds;
    char buff[10];
    int connection1 = client1 -> connection;
    int connection2 = client2 -> connection;
    FD_ZERO(&read_fds);
    FD_SET(connection1, &read_fds);
    FD_SET(connection2, &read_fds);
    printf("test\n"); 
    int number = 0;
    int i = select(connection2 + 1, &read_fds, NULL, NULL, NULL);
    if(FD_ISSET(connection1, &read_fds)){
        read(connection1, buff, sizeof(buff));
        sscanf(buff,"%d", &(client1 -> guess));
        printf("%d\n", client1 -> guess);
        return client1;
    }
    if(FD_ISSET(connection2, &read_fds)){
        read(connection2, buff, sizeof(buff));
        printf("%s\n", buff);
        sscanf(buff,"%d", &(client2 -> guess));
        return client2;
    }
}

struct clientDetails* createClient(int connection, char * buff){
    struct clientDetails* p = malloc(sizeof(struct clientDetails));
    p -> connection = connection;
    p -> guess = 0;
    p -> wins = 0;
    p -> name = buff; 
    return p;
}

int client_handling (int playerConnection) {

}

int main(){
    // start with two players ONLY
    int playerConnections[2]; 
    struct clientDetails* players[2];
    int listen_socket = server_setup();
    char * buff = malloc(sizeof(char ) * BUFFER_SIZE); 
    for(int i = 0; i < 2; i++){
        playerConnections[i] = server_tcp_handshake(listen_socket);
        // printf("%d, %d\n", i, playerConnections[i]); 
        // this is used for filedescriptors to make sure it works
        int bytes = read(playerConnections[i], buff, BUFFER_SIZE); 
        err(bytes, "could not read from client"); 

        printf("user: %s connected to server\n", buff); 
        players[i] = createClient(playerConnections[i], buff);
    }
    printf("Waiting for first response\n");
    struct clientDetails* responder = malloc(sizeof(struct clientDetails));
    responder = retrieveNumber(players[0], players[1]);
    printf("Guess is %d\n", responder -> guess);
}
