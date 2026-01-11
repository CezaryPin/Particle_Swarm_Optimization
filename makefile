out.exe: main.o utils.o pso.o 
	gcc main.o utils.o pso.o -o out.exe

main.o: main.c
	gcc -c main.c -o main.o

utils.o: utils.c
	gcc -c utils.c -o utils.o

pso.o:pso.c
	gcc -c pso.c -o pso.o

mapGen.o: mapGen.c
	gcc -c mapGen.c -o mapgen.o


clean:
	rm -f out.exe utils.o pso.o mapGen.o test.o