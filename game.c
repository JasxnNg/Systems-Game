#include "game.h"
#include "networking.h"

struct clientDetails* retrieveNumber(struct clientDetails* client1, struct clientDetails* client2){
  //helper function
  //Gets the number value of a guess from either client
    fd_set read_fds;
    char buff[BUFFER_SIZE];
    int connection1 = client1 -> connection;
    int connection2 = client2 -> connection;
    FD_ZERO(&read_fds);
    FD_SET(connection1, &read_fds);
    FD_SET(connection2, &read_fds);
    int number = 0;
    int largestConnection = 0;
    if(connection1 > connection2){
      largestConnection = connection1;
    } else{
      largestConnection = connection2;
    }
    int i = select(largestConnection + 1, &read_fds, NULL, NULL, NULL);
    if(FD_ISSET(connection1, &read_fds)){
        int readBytes = read(connection1, buff, sizeof(buff));
        if(readBytes == 0){
          return client2;
        }
        printf("%d\n", readBytes);
        sscanf(buff,"%d", &(client1 -> guess));
        printf("%d\n", client1 -> guess);
        return client1;
    }
    if(FD_ISSET(connection2, &read_fds)){
        int readBytes = read(connection2, buff, sizeof(buff));
        if(readBytes == 0){
          return client1;
        }
        printf("%s\n", buff);
        sscanf(buff,"%d", &(client2 -> guess));
        return client2;
    }
}


int countFiles(char* dir) {
  DIR* d = opendir(dir);
  int counter = 0;
  struct dirent* entry = readdir(d);
  while (entry != NULL) {
    if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
      counter++;
    }
    entry = readdir(d);
  }
  closedir(d);
  return counter;
}

struct fileinfo randFile() {
  // helper function
  // pick a random file and put its size and name in a struct fileinfo
  char dir[256] = "./gamefiles/";
  DIR* d = opendir(dir);
  if (d == NULL) {
    perror("error opening directory");
  }
  else {
    srand( time(NULL) );
    struct dirent* entry = readdir(d);
    for (int i = 0; i < abs(rand()) % countFiles(dir); i++) {
      entry = readdir(d);
    }
    struct stat file;
    strncat(dir, entry->d_name, 127);
    if (stat(dir, &file) == -1) perror("error with struct stat");
    struct fileinfo data;
    data.size = file.st_size;
    strncpy(data.name, entry->d_name, 127);
    closedir(d);
    return data;
  }
}


struct clientDetails* game(struct clientDetails* client1, struct clientDetails* client2) {
  // runs a match between client1 and client2
  // requires the file descriptors for the two clients
  // returns the file descriptor of the winner

  struct fileinfo data = randFile();
  char msg[128] = "Guess the size of the following file: ";
  strcat(msg, data.name);
  strcat(msg, "\n");
  write(client1->connection, msg, 64);
  write(client2->connection, msg, 64);
}
