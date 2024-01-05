#include "game.h"
#include "networking.h"

struct fileinfo randFile() {
  // helper function
  // pick a random file and put its size and name in a struct fileinfo
  char dir[32] = "./gamefiles/";
  
}

int game(int client1, int client2) {
  // runs a match between client1 and client2
  // requires the file descriptors for the two clients
  // returns the file descriptor of the winner
}
