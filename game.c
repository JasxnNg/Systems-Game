#include "networking.h"

struct fileinfo randFile() {
  // helper function
  // pick a random file and put its size and name in a struct fileinfo
}

int retrieveNumber(struct clientDetails* client1, struct clientDetails* client2){
    fd_set read_fds;
    char buff[10];
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(client1 -> connection, &read_fds);
    FD_SET(client2 -> connection, &read_fds);
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

int game(int client1, int client2) {
  // runs a match between client1 and client2
  // requires the file descriptors for the two clients
  // returns the file descriptor of the winner
}
