OBJECTS = util.o index.o operacoes.o main.o

all: main

main: $(OBJECTS)
	gcc $(OBJECTS) -o main -lm

util.o: util.c
	gcc -c -g -Wall util.c

operacoes.o: operacoes.c
	gcc -c -g -Wall operacoes.c

index.o: index.c
	gcc -c -g -Wall index.c

main.o: main.c
	gcc -c -g -Wall main.c

run: main
	./main

clean:
	rm $(OBJECTS) main *.bin *.out