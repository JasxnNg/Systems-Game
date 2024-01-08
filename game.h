#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h> 
#include <netdb.h> 

#ifndef GAME_H
#define GAME_H
struct fileinfo {
  int size;
  char name[128];
};
struct clientDetails {
  int connection;
  int guess;
  int wins;
  char * name; 
};
struct fileinfo randFile();
struct clientDetails* retrieveNumber(struct clientDetails* client1, struct clientDetails* client2);
int game(int client1, int client2);
#endif
