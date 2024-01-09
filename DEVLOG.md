# Dev Log:

## Player 1

### 2024-01-02 - Brief description

Expanded description including how much time was spent on task.

### 2024-01-03 - Brief description

Expanded description including how much time was spent on task.

## Player 2

### 2024-01-02 - Brief description

Expanded description including how much time was spent on task.

### 2024-01-03 - Brief description

Expanded description including how much time was spent on task.

```
Brian Chau:

2024-01-03 Started working on proposal
I added names of group members, our idea and how the user would use the program I worked on it with group members for roughly 30 minutes. At home I started on the technical details by determing which topics we were going to use for our project which took another 20 minutes.

2024-01-04 Finished proposal and began work on networking
I modified our intended project usage and topics we added because of the change in the type of game
we wanted. I worked on this with my group for 30 minutes. At home I copied over a bunch of the networking code from lab to be modified and added main to server and made sure that it worked properly which took 10 minutes. Then, I decided to make the server an array to hold all the connections and then put the connections into the array. This took 20 minutes with most of the time spent coming with the idea.

2024-01-05 Started work on a way to listen to multiple clients
Spent the 40 minutes at school working on the first itieration of the retrieveNumber function which was a copy of the select demo with some changes to fit the project. Then I created a struct to be used to hold both the guess and client metadata to be able to determine which client was communicating. At home, I fixed the struct and then added the struct to the function and fixed all the compiling issues which took 20 minutes.

2024-01-05 Started work on a way to listen to multiple clients
Spent the 40 minutes at school working on the first itieration of the retrieveNumber function which was a copy of the select demo with some changes to fit the project. Then I created a struct to be used to hold both the guess and client metadata to be able to determine which client was communicating. At home, I fixed the struct and then added the struct to the function and fixed all the compiling issues which took 20 minutes.

2025-01-06 Fixing bugs on retrieveNumber and server creates structs
Made a function to create structs based on the connections from clients to store the guesses from retrieveNumber. Then I fixed some bugs so that retrieveNumber works fully with the clientData struct rather than an int. ~40 minutes

2025-01-07 Started implementation of dynamic starts
Allowed the server to start a match whenever it wanted even if max number of players was not reached. Also continued working on retrieveNumber to fix some bugs. ~30 minutes

2025-01-08 Completed work on starting match and couldn't fix bug with retrieveNumber
I merge all of the changes from the weekend in class as well as worked on a way to prevent the client from prompting for an answer before the match started. At home, I completed this and started work on what the forking server would do but not the actual forking. I spent a large amount of time fixing a bug with socket but could not fix retrieveNumber. ~2 hour
Aareeb Jamil:

2024-01-04 Edited proposal
I added the intended pacing of our project and our planned division of labor to PROPOSAL.md

2024-01-05 Writing helper functions for game.c
In the morning (before school), I planned the overall structure of game.c by adding some function headers to game.c (and game.h). In class, I created a directory called gamefiles with some random files for our file size guessing game. I also started working on countFiles() and randFile(), which are helper functions in game.c. After school, I finished writing countFiles() and randFile(), and I tested them by creating a dummy main in game.c.

2023-01-08 Writing main game function

Jason Ng:

2024-01-03 11:32 PM Reformatted devlog
Created this entire textbox for greater organization ~5 minutes

2024-01-04 2:32 PM Created files
Planned and created the structure of our project. Worked on making a skeleton for networking and added make commands to the make file. Worked on the input logic for client.c total time: ~30 minutes

2024-01-04 9:01 PM Client logic
Worked on client-side logic again (planning out client-server communication and how they will communicate); primarly worked on server_handling() function ~20 minutes

2024-01-05 2:05 PM Client
Worked on a way to distinguish clients between each other by adding usernames; added logic for communication with server; mostly in the main() function of the client program ~40 minutes

2024-01-07 7:48 PM Client finished + Networking needs restructing
Finished client input logic; worked on debugging and testing; tested the server and client connection and realized we need to completely scrap our previous networking. Need to talk to Brian about this --- need to put the accept function into the server.c or else bad things will happen (error: connection reset by peer); also need to include <sys/select.h> for fd_set function ~1 hour

2024-01-08 2:10 PM Working on choosing usernames
Wrote function chooseUser() in server.c and added communication between server and client... fixing a ton of merge conflicts


```
