
all: compila
	
compila:
	gcc -Wall -g -o main *.c

teste:
	./main <testes/in/in25.txt >saida.txt

diff:
	diff saida.txt diff.txt

valgrind:
	valgrind --leak-check=full ./main <teste.txt > valgrind.txt 2>&1

teste_all:
	for i in $$(seq 1 29); do \
		valgrind --leak-check=full ./main <teste$$i.txt > valgrind$$i.txt 2>&1; \
		echo "valgrind$$i:"; \
		tail -n 1 valgrind$$i.txt; \
	done

report_comp:
	gcc -Wall -g -o main main.c binary_tree.c > report.txt 2>&1

report_teste:
	./main <teste.txt >saida.txt > report.txt 2>&1

zip:
	zip main.zip *.c *.h

zipall:
	zip main.zip *
	
clean:
	rm -rf main saida.txt main.zip report.txt valgrind.txt
	clear

clean_teste:
	find . -type f -name "*.txt" \
		! -name "teste.txt" ! -name "diff.txt" \
		! -name "jogadores0.txt" ! -name "jogadores1.txt" ! -name "jogadores2.txt" ! -name "jogadores3.txt" \
		! -name "jogadores4.txt" ! -name "jogadores5.txt" ! -name "jogadores6.txt" \
		! -name "jogadores7.txt" ! -name "jogadores8.txt" ! -name "entrada.txt" \
		-delete
	clear
