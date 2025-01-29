all: compila

compila:	
	gcc -Wall -g -o main *.c

teste:
	./main <teste.txt

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

clean:
	rm -f main 
	clear