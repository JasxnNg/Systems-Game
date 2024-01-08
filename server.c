#include "networking.h"
#include "game.h"
#include <sys/select.h> // needed for the retrieve files

int chooseUser () {
    char * buff = malloc(sizeof (char) * BUFFER_SIZE); 
    printf("do you want to use the default usernames? yes or no:");
    fflush (stdout); 

    while (1) {
    fgets(buff, BUFFER_SIZE, stdin);
    buff = strsep(&buff, "\n");
    if (strcmp (buff, "yes") == 0 ){
        free(buff);
        return 1; 

    }
    else if (strcmp (buff, "no" == 0)){
        free(buff); 
        return 2; 

    }
    else {
        printf("please write yes or no"); 
        fflush(stdout);
    
    }

    }
 

}

struct clientDetails* createClient(int connection, char * buff){
    struct clientDetails* p = malloc(sizeof(struct clientDetails));
    p -> connection = connection;
    p -> guess = 0;
    p -> wins = 0;
    strcpy(p -> identifier, buff); 
    return p;
}

int client_handling (int playerConnection) {

}

int main(){
    int choose = chooseUser (); 
    int matchStarted = 0;
    int numOfPlayers = 0;
    int maxPlayerCount = 2;
    int playerConnections[2];
    struct clientDetails* players[2];
    int listen_socket = server_setup();
    while(!matchStarted || numOfPlayers >= maxPlayerCount){
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
    for(int i = 0; i < numOfPlayers){
        char startingMessage[20] = "The match is beginning get ready.\n";
        write(playerConnection[i], startingMessage, sizeof(startingMessage));
    }
    struct clientDetails* responder = malloc(sizeof(struct clientDetails));
    responder = retrieveNumber(players[0], players[1]);
    printf("Guess is %d\n", responder -> guess);
}
