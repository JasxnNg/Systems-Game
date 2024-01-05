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
struct fileinfo randFile();
int retrieveNumber(int client1, int client2);
int game(int client1, int client2);
#endif
