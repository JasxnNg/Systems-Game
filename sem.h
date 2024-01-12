#include "networking"
#include <sys/sem.h>
#include <sys/ipc.h>

#ifndef SEMAPHORES 
#define SEMAPHORES

#define SEMKEY 0xDEADBEEF

//THIS FILE IS TO MANAGE CLIENT CONNECTIONS 

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};

#endif