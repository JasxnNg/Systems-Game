#define SEMKEY 0xDEADBEEF

//THIS FILE IS TO MANAGE CLIENT CONNECTIONS 

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};


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


void access_data() {
    
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

}

void let_go() {
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

}