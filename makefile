out.exe: main.o utils.o pso.o map.o logger.o
	gcc main.o utils.o pso.o map.o logger.o -o out.exe

main.o: main.c
	gcc -c main.c -o main.o

utils.o: utils.c
	gcc -c utils.c -o utils.o

pso.o:pso.c
	gcc -c pso.c -o pso.o

map.o:map.c
	gcc -c map.c -o map.o

logger.o: logger.c
	gcc -c logger.c -o logger.o

mapGen.o: mapGen.c
	gcc -c mapGen.c -o mapgen.o


clean:
	rm -f out.exe utils.o pso.o mapGen.o test.o