#include "networking.h"
#include "game.h"
#include <sys/select.h> // needed for the retrieve files

int chooseUser () {
    char * buff = malloc(sizeof (char) * BUFFER_SIZE); 
    printf("do you want to use the default usernames? yes or no: ");
    fflush (stdout); 

    while (1) {
    fgets(buff, BUFFER_SIZE, stdin);
    buff = strsep(&buff, "\n");
    if (strcmp (buff, "yes") == 0 ){
        free(buff);
        return 1; 

    }
    else if (strcmp (buff, "no") == 0){
        free(buff); 
        return 2; 

    }
    else {
        printf("please write yes or no\n"); 
        fflush(stdout);
    
    }

    }
 

}

int numUsers () {
    char * buff = malloc(sizeof(char) * BUFFER_SIZE);
    printf("please enter the number of users: ");
    fflush(stdout); 

    fgets(buff, BUFFER_SIZE, stdin); 
    int numOfPlayers; 
    sscanf(buff, "%d", &numOfPlayers);

    free(buff); 
    return numOfPlayers; 
}

struct clientDetails* createClient(int connection, char * buff){
    struct clientDetails* p = malloc(sizeof(struct clientDetails));
    p -> connection = connection;
    p -> guess = 0;
    p -> wins = 0;
    strcpy(p -> identifier, buff); 
    return p;
}

int isPlaying(int playerConnection){
    char* test = malloc(BUFFER_SIZE);
    if(read(playerConnection, test, BUFFER_SIZE) == 0){
        return 0;
    }
    else{
        return 1;
    }
}

int client_handling (struct clientDetails* client1, struct clientDetails* client2) {
    printf("Sending message to start game\n");
    for(int i = 0; i < 2; i++){
        int writeBytes;
        char startingMessage[BUFFER_SIZE] = "The match is beginning get ready.";
        if(i == 0){
            writeBytes = write(client1 -> connection, startingMessage, BUFFER_SIZE);
        }
        if(i == 1){
            writeBytes = write(client2 -> connection, startingMessage, BUFFER_SIZE);
        }
        err(writeBytes, "could not write to client socket"); 
    }
    struct clientDetails* winner = malloc(sizeof(struct clientDetails));
    winner = game(client1, client2);
    if(winner -> connection == client1 -> connection){
        return 0;
    } else{
        return 1;
    }
}

int main(){
    // int choose = chooseUser (); 
    int matchStarted = 0;
    int numOfPlayers = 0;
    int playersJoined = 0;
    int maxPlayerCount = 2;
    pid_t p;
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
        
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            fgets(buff, sizeof(buff), stdin);
            buff[strlen(buff)-1]=0;
            if(strcmp(buff, "start") == 0){
                matchStarted = 1;
            }
        }

        if(FD_ISSET(listen_socket, &read_fds)){

            playerConnections[numOfPlayers] = server_tcp_handshake(listen_socket);
            int readBytes = read(playerConnections[numOfPlayers], buff, sizeof(buff));
            if (readBytes <= 0) {
                perror("could not create the connection\n"); 
            }
            // err(readBytes, "could not create the connection"); 


            players[numOfPlayers] = createClient(playerConnections[numOfPlayers], buff);
            
            //COMMENT THIS OUT AFTERWARD
            printf("%d, %d\n", numOfPlayers, playerConnections[numOfPlayers]); 
            printf("%s joined\n", buff ); 

            numOfPlayers++; // create the amount of numPlayers needed 
        }

    }
    printf("The current number of players is %d\n", numOfPlayers);
    playersJoined = numOfPlayers;
    while(numOfPlayers > 1){
        int numberOfServers = numOfPlayers / 2;
        int playerPosInArray = 0;
        struct clientDetails* alivePlayers[numOfPlayers];
        printf("Completed step 1\n");
        printf("Working on finding alive players\n");
        for(int i = 0; i < playersJoined; i++){
            if(isPlaying(playerConnections[i])){
                printf("Player is still connnected\n");
                alivePlayers[playerPosInArray] = players[i];
                playerPosInArray++;
            }
        }
        printf("Completed step 2\n");
        for(int i = 0; i < numberOfServers; i++){
            p = fork();
            if(p == 0){
                printf("Starting game as the subserver\n");
                client_handling(alivePlayers[0], alivePlayers[1]);
                exit(0);
            }
        }
        if(p != 0){
            int status;
            wait(&status);
        }
        numOfPlayers = numOfPlayers/2 + numOfPlayers % 2;
    }

    // for(int i = 0; i < numOfPlayers; i++){
    //     char startingMessage[BUFFER_SIZE] = "The match is beginning get ready.";
    //     int writeBytes = write(playerConnections[i], startingMessage, BUFFER_SIZE);
    //     err(writeBytes, "could not write to client socket"); 
    //     printf("%d\n", writeBytes);
    // }
<<<<<<< HEAD
    printf("Starting Game\n");
    printf("Waiting for first response\n"); 


    // THIS CODE IS ALREADY IN GAME WHERE WE HAVE MALLOC AND STUFF HERE 
    struct clientDetails* responder = malloc(sizeof(struct clientDetails));
    responder = retrieveNumber(players[0], players[1]);
    printf("Guess is %d\n", responder -> connection);
    game(players[0], players[1]);
=======
    // printf("Starting Game\n");
    // printf("Waiting for first response\n");
    // struct clientDetails* responder = malloc(sizeof(struct clientDetails));
    // responder = retrieveNumber(players[0], players[1]);
    // printf("Guess is %d\n", responder -> connection);
    // game(players[0], players[1]);
>>>>>>> main
}
