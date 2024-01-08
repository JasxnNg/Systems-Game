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



int game(int client1, int client2) {
  // runs a match between client1 and client2
  // requires the file descriptors for the two clients
  // returns the file descriptor of the winner
}

// int main() {
//   struct fileinfo data = randFile();
//   printf("%s has a size of %d bytes\n", data.name, data.size);
// }
