#include "networking.h"

int retrieveNumber(int client1, int client2){
    fd_set read_fds;
    char buff[10];
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(client1, &read_fds);
    FD_SET(client2, &read_fds);
    int number = 0;
    int i = select(client2 + 1, &read_fds, NULL, NULL, NULL);
    if(FD_ISSET(STDIN_FILENO, &read_fds)){
        fgets(buff, sizeof(buff), stdin);
        buff[strlen(buff)-1]=0;
        printf("Recieved command: '%s'\n",buff);
    }
    if(FD_ISSET(client2, &read_fds)){
        read(client2, buff, sizeof(buff));
        printf("%s\n", buff);
        sscanf(buff,"%d", number);
    }
    if(FD_ISSET(client1, &read_fds)){
        read(client1, buff, sizeof(buff));
        printf("%s\n", buff);   
        sscanf(buff,"%d", number);
    }
    return number;
}

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
