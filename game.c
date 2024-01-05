#include "game.h"

int countFiles(DIR* d) {
  int counter = 0;
  struct dirent* entry = readdir(d);
  while (entry != NULL) {
    counter++;
    entry = readdir(d);
  }
  return counter;
}

struct fileinfo randFile() {
  // helper function
  // pick a random file and put its size and name in a struct fileinfo
  char dir[32] = "./gamefiles/";
  DIR* d = opendir(dir);
  if (d == NULL) {
    perror("error opening directory");
  }
  else {
    printf("%d files\n", countFiles(d));
  }

  
}

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

int game(int client1, int client2) {
  // runs a match between client1 and client2
  // requires the file descriptors for the two clients
  // returns the file descriptor of the winner
}

int main() {
  char dir[32] = "./gamefiles/";
  DIR* d = opendir(dir);
  if (d == NULL) {
    perror("error opening directory");
  }
  else {
    printf("%d files\n", countFiles(d));
  }
}
