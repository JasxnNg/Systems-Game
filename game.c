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
