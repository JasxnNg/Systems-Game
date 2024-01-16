
compile: networking.o client.o server.o game.o wins.o
	@gcc -o cli networking.o client.o
	@gcc -o ser networking.o server.o game.o
	@gcc -o wins.o winning 

cli: networking.o client.o game.o
	@gcc networking.o client.o -o cli

ser: networking.o server.o game.o 
	@gcc networking.o server.o game.o -o ser

winning: wins.o 
	@gcc wins.o -o winning

client: cli 
	@./cli 

server: ser
	@./ser

show: winning
	@./winning

networking.o: networking.c networking.h 
	@gcc -c networking.c 

server.o: server.c 
	@gcc -c server.c 

game.o: game.c 
	@gcc -c game.c  

wins.o: wins.c 
	@gcc -c wins.c

clean: 
	@rm -f wins.dat
	@rm -f ser
	@rm -f cli 
	@rm -f *.o 
	#rm -f winning

homer: cli 
	@./cli homer.stuy.edu