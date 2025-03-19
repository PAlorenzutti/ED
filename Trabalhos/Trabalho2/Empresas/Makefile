
all: compila
	
compila:
	gcc -Wall -g -o main *.c

teste:
	./main <teste.txt >saida.txt

diff:
	diff saida.txt diff.txt

valgrind:
	valgrind --leak-check=full ./main <teste.txt > valgrind.txt 2>&1

teste_all:
	for i in $$(seq 1 41); do \
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
		! -name "lst1.txt" ! -name "lst2.txt" ! -name "lst3.txt" \
		! -name "lst4.txt" ! -name "lst5.txt" ! -name "lst6.txt" \
		! -name "lst7.txt" ! -name "lst8.txt" ! -name "entrada.txt" \
		-delete
	clear
