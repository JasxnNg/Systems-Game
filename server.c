#include "networking.h"
#include "game.h"
#include <sys/select.h> // needed for the retrieve files



void serverConnection (int i, char * message) {
    if (i == 0) {
        printf("Client lost connection with the server!\n"); 
    }
    else if (i < 0) {
        printf("Error: %s - %s\n", message, strerror(errno));
        exit(1); 
    }

}


// choose the amount of users that you want for this function 
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
        printf("please write yes or no "); 
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
    p -> isAlive = 1;
    strcpy(p -> identifier, buff); 
    return p;
}

int isPlaying(int playerConnection){
    char* test = malloc(BUFFER_SIZE);
    int po = read(playerConnection, test, BUFFER_SIZE);
    printf("player connection %d ; %d %d \n", playerConnection, po, BUFFER_SIZE);
    if(read(playerConnection, test, BUFFER_SIZE) == 0){
        free(test); 
        return 0;
    }
    else{
        free(test); 
        return 1;
    }
}

int client_handling (struct clientDetails* client1, struct clientDetails* client2, int whichGame) {
    printf("Sending message to start game\n");
    int writeBytes;
    char startingMessage[BUFFER_SIZE] = "The match is beginning get ready.\0";
    int connection1 = client1 -> connection;\
    int connection2 = client2 -> connection;
    
    writeBytes = write(client1 -> connection, startingMessage, BUFFER_SIZE);
    serverConnection(writeBytes, "failed to write to the client"); 

    writeBytes = write(client2 -> connection, startingMessage, BUFFER_SIZE);
    serverConnection(writeBytes, "failed to write to the client"); 
        // reminder need to check writeBytes for == 0 if connection is broken
    
    struct clientDetails* winner = malloc(sizeof(struct clientDetails));
    if (whichGame == 0) {
      winner = game(client1, client2);
    }
    else if (whichGame == 1) {
      winner = rockPaperScissors(client1, client2);
    }
    char* loseFlag = malloc(BUFFER_SIZE); 
    char* winFlag = malloc(BUFFER_SIZE); 
    winFlag[0] = '1';
    loseFlag[0] = '0';
    if(winner -> connection == client1 -> connection){
        write(connection2, loseFlag, BUFFER_SIZE);
        write(connection1, winFlag, BUFFER_SIZE);
        free(winner);
        return 0;
    } else{
        write(connection1, loseFlag, BUFFER_SIZE);
        write(connection2, winFlag, BUFFER_SIZE);
        free(winner);
        return 1;
    }
}

// AUTOMATICALLY GIVE THE WIN IF SOMEONE LOSES CONNECTION

int main(){
    printf("Which game would you like to play? Enter 0 for file size guessing game or 1 for rock paper scissors: ");
    char buff[BUFFER_SIZE];
    fgets(buff, BUFFER_SIZE, stdin);
    int whichGame;
    sscanf(buff, "%d", &whichGame);

    // INIT ALL VARIABLES 
    // int choose = chooseUser (); 
    int matchStarted = 0;
    int numOfPlayers = 0;
    int playersJoined = 0;
    int maxPlayerCount = 16;
    //might be able to add a semaphore here  
    pid_t p;

    //malloc the rest 
    int playerConnections[maxPlayerCount];
    struct clientDetails* players[maxPlayerCount];
    int listen_socket = server_setup();

    // THIS LOOP IS TO GET OBTAIN PLAYERS 
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

            //THIS READ IS TO READ THE USERNAMES 
            int readBytes = read(playerConnections[numOfPlayers], buff, sizeof(buff));
            if (readBytes <= 0) {
                perror("could not create the connection\n"); 
            }
            // err(readBytes, "could not create the connection"); 

            //CREATE THE CLIENTS WITH USERNAME + SERVER SOCKET
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
            // THIS FUNCTION DOES NOT WORK PROPERLY  
            // TESTED BY STOPPING THE PLAYERS 
            // PLEASE CHECK THIS SOON
            //FOR SOME REASON THIS IS CHECKED AFTER??? IN LINE 41 
            if(players[i] -> isAlive){
                printf("Player is still connnected %d\n", playerConnections[i]);
                alivePlayers[playerPosInArray] = players[i];
                playerPosInArray++;
            }
            // we should have logic that handles the server sockets; we should close them if they aren't in use? or at least
            // remove from the alivePlayers 
        }
        printf("Completed step 2\n");
        for(int i = 0; i < numberOfServers; i++){
            p = fork();
            if(p == 0){
                //THE SUBSERVER CAN'T EVEN PRINT HERE 
                printf("Starting game as the subserver\n");
                int exiting = client_handling(alivePlayers[2 * i], alivePlayers[2 * i + 1], whichGame); 
                if(exiting == 0){
                    exit(alivePlayers[2 * i + 1] -> connection);
                } else{
                    exit(alivePlayers[2 * i] -> connection);
                }
            }
        }
        if(p != 0){
            for(int i = 0; i < numberOfServers; i++){
                int status;
                wait(&status);
                for(int i = 0; i < playersJoined; i++){
                    if(playerConnections[i] == WEXITSTATUS(status)){
                        players[i] -> isAlive = 0;
                        printf("Unaliving a player\n");
                    }
                }
                printf("EXIT STATUS: %d LINE 167\n", WEXITSTATUS(status));
            }
        }
        printf("%d\n", numOfPlayers - numberOfServers);
        numOfPlayers -= numberOfServers;
        printf("%d\n", numOfPlayers);
        sleep(1);
    }
    printf("Game over!\n");
    for(int i = 0; i < playersJoined; i++){
        printf("in the loop\n");
        if(players[i] -> isAlive){
            printf("The winning player is %s, congratulation %s!\n", players[i] -> identifier, players[i] -> identifier);
            char* winFlag = malloc(BUFFER_SIZE);
            strcpy(winFlag, "the winner is you");
            write(players[i] -> connection, winFlag, BUFFER_SIZE);
        }
    }
    // for(int i = 0; i < numOfPlayers; i++){
    //     char startingMessage[BUFFER_SIZE] = "The match is beginning get ready.";
    //     int writeBytes = write(playerConnections[i], startingMessage, BUFFER_SIZE);
    //     err(writeBytes, "could not write to client socket"); 
    //     printf("%d\n", writeBytes);
    // }
    // printf("Starting Game\n");
    // printf("Waiting for first response\n");
    // struct clientDetails* responder = malloc(sizeof(struct clientDetails));
    // responder = retrieveNumber(players[0], players[1]);
    // printf("Guess is %d\n", responder -> connection);
    // game(players[0], players[1]);
}
