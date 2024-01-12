#include "sem.h"
#include "networking.h"
#include "game.h"
#include <sys/select.h>


int create_sem () {
    int semd = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0666); 
    if (semd < 0) {
        printf("semaphore already exists\n"); 
        return -1; 
    }
    else {
        union semun us;
        us.val = 1;
        int r = semctl(semd, 0, SETVAL, us);
        // printf("semctl returned: %d\n", r);
        return 0;
    }
} 


int getUpSem() {
    
  printf("attempting to access shared memory...\n");
  int semd = semget(SEMKEY, 1, 0); 
  if (semd == -1) {
    printf("semaphore does not exist\n");
    return 1; 
  }
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = -1;
  sb.sem_flg = SEM_UNDO;
  semop(semd, &sb, 1); // wait for the semaphore to be available
  return 0; 
}

int  getDownSem() {
    int semd = semget(SEMKEY, 1, 0); 
    if (semd == -1) {
        printf("semaphore does not exist\n");
        return 1; 
    }


    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = 1;
    sb.sem_flg = SEM_UNDO;
    semop(semd, &sb, 1); // wait for the semaphore to be available
    return 0;
} // needed for the retrieve files

void readWins() {
    int recordingFile = open("wins.dat", O_RDONLY); 
    if (recordingFile < 0 )
        perror("could not create the file");
    struct writeFile * reader = malloc(sizeof (struct writeFile)); 
    while (read(recordingFile, reader, sizeof(struct writeFile))) {
        printf("name: %s wins: %d\n", reader->name, reader->wins); 
    }
    close(recordingFile); 
}

void recordWins (char * user, int currentWins) {
    int recordingFile = open("wins.dat", O_RDWR | O_CREAT, 0666); // create the file 
    if (recordingFile < 0 )
        perror("could not create the file");
    // struct writeFile * update = malloc(sizeof(struct writeFile)); 
    // update->wins = currentWins; 
    // update->name = user; 
    int i = 0; // this is to keep track of indexing 
    int totalWins = 0; 
    struct writeFile * reader = malloc(sizeof (struct writeFile)); 
    while (read(recordingFile, reader, sizeof(struct writeFile))) {
        if (strcmp(reader->name, user) == 0){
            totalWins = currentWins + reader->wins; 
            break; 
        }
        i++; 
    }
    close(recordingFile); 
    recordingFile = open("wins.dat", O_RDWR | O_CREAT, 0666);
    lseek(recordingFile, sizeof(struct writeFile) * i, 0); 

    if (totalWins != 0 ) {
        strcpy (reader->name, user); 
        reader->wins = totalWins; 
        write(recordingFile, reader, sizeof(struct writeFile)); 

        
    }
    else {
        strcpy (reader->name, user); 
        reader->wins = currentWins; 
        write(recordingFile, reader, sizeof(struct writeFile)); 
        
    }
    // make a struct here 

} 

int main () {
  printf("%ld size of struct\n", sizeof(struct writeFile)); 
  char * buff = malloc(256);
  buff = "hello"; 
  recordWins(buff, 1231 );
  readWins();


}
