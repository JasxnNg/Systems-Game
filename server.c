#include "networking.h"
#include "game.h"

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
