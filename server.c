#include "networking.h"
#include "game.h"

struct clientDetails* createClient(int connection){
    struct clientDetails* p = malloc(sizeof(struct clientDetails));
    p -> connection = connection;
    p -> guess = 0;
    p -> wins = 0;
    return p;
}


int main(){
    // start with two players ONLY
    int playerConnections[2]; 
    struct clientDetails* players[2];
    int listen_socket = server_setup();
    for(int i = 0; i < 2; i++){
        playerConnections[i] = server_tcp_handshake(listen_socket);
        printf("%d, %d\n", i, playerConnections[i]);
        players[i] = createClient(playerConnections[i]);
    }
    printf("Waiting for first response\n");
    struct clientDetails* responder = malloc(sizeof(struct clientDetails));
    responder = retrieveNumber(players[0], players[1]);
    printf("Guess is %d\n", responder -> guess);
}
