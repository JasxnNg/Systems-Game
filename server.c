#include "networking.h"
#include "game.h"
#include <sys/select.h> // needed for the retrieve files

struct clientDetails* createClient(int connection, char * buff){
    struct clientDetails* p = malloc(sizeof(struct clientDetails));
    p -> connection = connection;
    p -> guess = 0;
    p -> wins = 0;
    strcpy(p -> identifier, buff); 
    return p;
}

int client_handling (struct clientDetails* client1, struct clientDetails* client2) {
    struct clientDetails* winner = malloc(sizeof(struct clientDetails));
    winner = game(client1, client2);
    if(winner -> connection == client1 -> connection){
        return 0;
    } else{
        return 1;
    }
}

int main(){
    int matchStarted = 0;
    int numOfPlayers = 0;
    int maxPlayerCount = 2;
    int playerConnections[2];
    struct clientDetails* players[2];
    int listen_socket = server_setup();
    while(!matchStarted && numOfPlayers < maxPlayerCount){
        fd_set read_fds;
        char buff[20];
        printf("The current number of players is %d\n", numOfPlayers);
        printf("Type in start to start\n");
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(listen_socket, &read_fds);
        int i = select(listen_socket + 1, &read_fds, NULL, NULL, NULL);
        if(FD_ISSET(STDIN_FILENO, &read_fds)){
            fgets(buff, sizeof(buff), stdin);
            buff[strlen(buff)-1]=0;
            if(strcmp(buff, "start") == 0){
                matchStarted = 1;
            }
        }
        if(FD_ISSET(listen_socket, &read_fds)){
            playerConnections[i] = server_tcp_handshake(listen_socket);
            printf("%d, %d\n", i, playerConnections[i]);
            read(playerConnections[i], buff, sizeof(buff));
            players[i] = createClient(playerConnections[i], buff);
            numOfPlayers++;
        }
    }
    printf("Waiting for first response\n");
    for(int i = 0; i < numOfPlayers; i++){
        char startingMessage[BUFFER_SIZE] = "The match is beginning get ready.\n";
        write(playerConnections[i], startingMessage, sizeof(startingMessage));
    }
    printf("Starting Game\n");
    struct clientDetails* responder = malloc(sizeof(struct clientDetails));
    responder = retrieveNumber(players[0], players[1]);
    printf("Guess is %d\n", responder -> guess);
}
