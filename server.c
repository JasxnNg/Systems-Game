#include "networking.h"

int main(){
    int playerConnections[16];
    int listen_socket = server_setup();
    for(int i = 0; i < 16; i++){
        playerConnections[i] = server_tcp_handshake(listen_socket);
    }
    for(int i = 0; i < 16; i++){
        printf("%d\n", playerConnections[i]);
    }
}
