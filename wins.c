#include "networking.h"
#include "game.h"

void recordWins (char * user, int currentWins) {
    int recordingFile = open("wins.dat", O_RDWR | O_CREAT, 0666); // create the file 
    if (recordingFile < 0 )
        perror("could not create the file");
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
    int bytes = recordingFile = open("wins.dat", O_RDWR | O_CREAT, 0666);
    err(bytes, "failed to read"); 
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
    close(recordingFile);

} 


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

int main() {
    printf("-----All Time Wins-----\n"); 
    readWins();
    return 0; 
} 