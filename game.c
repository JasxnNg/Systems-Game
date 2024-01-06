#include "game.h"

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


struct clientDetails* retrieveNumber(struct clientDetails* client1, struct clientDetails* client2){
  //helper function
  //Gets the number value of a guess from either client
    fd_set read_fds;
    char buff[10];
    int connection1 = client1 -> connection;
    int connection2 = client2 -> connection;
    FD_ZERO(&read_fds);
    FD_SET(connection1, &read_fds);
    FD_SET(connection2, &read_fds);
    int number = 0;
    int i = select(connection2 + 1, &read_fds, NULL, NULL, NULL);
    if(FD_ISSET(connection1, &read_fds)){
        read(connection1, buff, sizeof(buff));
        sscanf(buff,"%d", &(client1 -> guess));
        printf("%d\n", client1 -> guess);
        return client2;
    }
    if(FD_ISSET(connection2, &read_fds)){
        read(connection2, buff, sizeof(buff));
        printf("%s\n", buff);
        sscanf(buff,"%d", &(client2 -> guess));
        return client1;
    }
}

int game(int client1, int client2) {
  // runs a match between client1 and client2
  // requires the file descriptors for the two clients
  // returns the file descriptor of the winner
}

int main() {
  struct fileinfo data = randFile();
  printf("%s has a size of %d bytes\n", data.name, data.size);
}
