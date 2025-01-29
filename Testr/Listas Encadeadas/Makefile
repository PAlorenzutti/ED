
all: compila
	
compila:
	gcc -Wall -g -o main *.c

teste:
	./main <teste.txt >saida.txt

valgrind:
	valgrind ./main <teste.txt
	
clean:
	rm -rf main saida.txt
	clear
