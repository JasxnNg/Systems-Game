#include "networking.h"
#include "game.h"

struct clientData* createClient(int connection){
    struct node* p = malloc(sizeof(struct clientData));
    p -> connection = connection;
    p -> guess = 0;
    p -> wins = 0;
    return p;
}

int main(){
    int playerConnections[16];
    struct clientData* players[16];
    int listen_socket = server_setup();
    for(int i = 0; i < 16; i++){
        playerConnections[i] = server_tcp_handshake(listen_socket);
        players[i] = createClient(playerConnections[i]);
    }
}
