#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h> 
#include <time.h> 
#include <netdb.h>

#ifndef GAME_H
#define GAME_H

struct fileinfo {
  int size;
  char name[64];
}
struct clientDetails {
  int guess;
  int wins;
  int connection;
  char identifier[64];
}
struct fileinfo randFile();
struct clientDetails* retrieveNumber(struct clientDetails* client1, struct clientDetails* client2);
int game(int client1, int client2);
#endif
