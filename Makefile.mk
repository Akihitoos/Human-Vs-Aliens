LIB = -I include -L lib -lmingw32 -lSDL2main -lSDL2

all: src/main.o 
	gcc -o bin/HumanVsAliens src/main.o $(LIB)

src/main.o: src/main.c
	gcc -c src/main.c -o src/main.o $(LIB)

clear:
	del *.o