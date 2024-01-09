#include "networking.h"
#include "game.h"
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
        char buff[BUFFER_SIZE];
        printf("The current number of players is %d\n", numOfPlayers);
        printf("Type in start to start\n");
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(listen_socket, &read_fds);
        int j = select(listen_socket + 1, &read_fds, NULL, NULL, NULL);
        if(FD_ISSET(STDIN_FILENO, &read_fds)){
            fgets(buff, sizeof(buff), stdin);
            buff[strlen(buff)-1]=0;
            if(strcmp(buff, "start") == 0){
                matchStarted = 1;
            }
        }
        if(FD_ISSET(listen_socket, &read_fds)){
            playerConnections[numOfPlayers] = server_tcp_handshake(listen_socket);
            int readBytes = read(playerConnections[numOfPlayers], buff, sizeof(buff));
            players[numOfPlayers] = createClient(playerConnections[numOfPlayers], buff);
            printf("%d, %d\n", numOfPlayers, playerConnections[numOfPlayers]);
            numOfPlayers++;
        }
    }
    printf("The current number of players is %d\n", numOfPlayers);
    for(int i = 0; i < numOfPlayers; i++){
        char startingMessage[BUFFER_SIZE] = "The match is beginning get ready.";
        int writeBytes = write(playerConnections[i], startingMessage, BUFFER_SIZE);
        printf("%d\n", writeBytes);
    }
    for(int i = 0; i < numOfPlayers; i++){
        char confirmMessage[BUFFER_SIZE];
        int readBytes = read(playerConnections[i], confirmMessage, BUFFER_SIZE);
        printf("Confirmation: %s, bytes read: %d\n", confirmMessage, readBytes);
        err(readBytes, "could not read from the client socket"); 
    }
    printf("Starting Game\n");
    /*printf("Waiting for first response\n");
    struct clientDetails* responder = malloc(sizeof(struct clientDetails));
    responder = retrieveNumber(players[0], players[1]);
    printf("Guess is %d\n", responder -> connection);*/
    game(players[0], players[1]);
}
