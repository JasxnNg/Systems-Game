[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# Bunch Of Random Games 

### Brian and Friends

Aareeb Jamil, Brian Chau, Jason Ng
       
### Project Description:

Explain what is this project.
  
### Instructions:

How does the user install/compile/run the program.
We do not use any new libraries. Compile using "make compile". The server user will run make server. For our purposes, the server has to be run from homer and the client users will need to run ./cli homer.stuy.edu. 

How does the user interact with this program?

One user hosts the program (in this case, it needs to be on homer [because of the funny business with ports]/home computer if all the clients are playing from the home computer). The user who control the server can pick the game (either rock, paper, scissors or guess the file size). After an instance of the server is created, the clients can start connecting to the server. The max number of players is 16, but the server user can start whenever they want. 
After the server starts the game, the clients are prompte for an input. If they lose, they will see a message saying they lost. 