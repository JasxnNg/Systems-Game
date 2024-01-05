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
struct fileinfo randFile();
int retrieveNumber(int client1, int client2);
int game(int client1, int client2);
#endif
