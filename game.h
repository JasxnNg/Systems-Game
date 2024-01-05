#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h> 

#ifndef GAME_H
#define GAME_H
struct fileinfo {
  int size;
  char name[64];
};
struct clientDetails {
  int connection;
  int guess;
  int wins;
};
struct fileinfo randFile();
int retrieveNumber(struct clientDetails* client1, struct clientDetails* client2);
int game(int client1, int client2);
#endif
