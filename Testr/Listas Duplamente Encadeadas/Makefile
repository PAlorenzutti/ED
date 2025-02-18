
all: compila
	
compila:
	gcc -Wall -g -o main *.c

teste:
	./main <teste.txt >saida.txt

diff:
	diff saida.txt diff.txt

valgrind:
	valgrind ./main <teste.txt

zip:
	zip main.zip *.c *.h
	
clean:
	rm -rf main saida.txt main.zip
	clear
