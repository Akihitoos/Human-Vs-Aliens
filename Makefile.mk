LIB = -I include -L lib -lmingw32 -lSDL2main -lSDL2
CC = gcc
BIN = bin/HumanVsAliens
OBJECTS = src/main.o src/Entity.o src/interaction.o

all: $(OBJECTS) 
	$(CC) -o $(BIN) $(OBJECTS) $(LIB)

src/main.o: src/main.c
	$(CC) -c src/main.c -o src/main.o $(LIB)

src/Entity.o: src/Entity.c
	$(CC) -c src/Entity.c -o src/Entity.o $(LIB)

src/interaction.o: src/interaction.c
	$(CC) -c src/interaction.c -o src/interaction.o $(LIB)

clear:
	del src/*.o