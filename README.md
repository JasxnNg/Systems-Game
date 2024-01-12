[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# Bunch Of Random Games 

### Brian and Friends

Aareeb Jamil, Brian Chau, Jason Ng
       
### Project Description:

Explain what is this project.
The server hosts up to 16 clients and makes them play in a tournament, with the game being chosen by the host (either the file size guessing game or rock paper scissors). The server forks off a subserver for each game played between a pair of clients. The file size guessing game is when two players compete to guess the size of a file (chosen randomly from the gamefiles directory) based on the name of the file. Whoever is closest to the actual size wins. Rock paper scissors is the usual, with the two players entering 0, 1, or 2 corresponding to rock, paper, or scissors. After each win, the server updates the lifetime wins of the players in a data file. At the end of the tournament, the server prints the data file.

### Instructions:

How does the user install/compile/run the program.
How does the user interact with this program?
