
all: compila
	
compila:
	gcc -Wall -g -o main *.c

teste:
	./main <teste.txt >saida.txt

diff:
	diff saida.txt diff.txt

valgrind:
	valgrind --leak-check=full ./main <teste.txt > valgrind.txt 2>&1

report:
	gcc -Wall -g -o main main.c binary_tree.c > report.txt 2>&1

zip:
	zip main.zip *.c *.h

zipall:
	zip main.zip *
	
clean:
	rm -rf main saida.txt main.zip report.txt valgrind.txt
	clear
