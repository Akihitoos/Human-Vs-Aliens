LIB = -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
CC = gcc
BIN = HumanVsAliens/HumanVsAliens
OBJECTS = src/main.o src/Entity.o src/interaction.o src/mower.o src/update.o src/GameRenderBasics.o src/GameRender.o src/Shop.o src/Player.o

all: $(OBJECTS) 
	$(CC) -o $(BIN) $(OBJECTS) $(LIB)

src/main.o: src/main.c
	$(CC) -c src/main.c -o src/main.o $(LIB)

src/Entity.o: src/Entity.c
	$(CC) -c src/Entity.c -o src/Entity.o $(LIB)

src/interaction.o: src/interaction.c
	$(CC) -c src/interaction.c -o src/interaction.o $(LIB)

src/mower.o: src/mower.c
	$(CC) -c src/mower.c -o src/mower.o $(LIB)

src/update.o: src/update.c
	$(CC) -c src/update.c -o src/update.o $(LIB)

src/GameRenderBasics.o: src/GameRenderBasics.c
	$(CC) -c src/GameRenderBasics.c -o src/GameRenderBasics.o $(LIB)
	
src/GameRender.o: src/GameRender.c
	$(CC) -c src/GameRender.c -o src/GameRender.o $(LIB)

src/Shop.o: src/Shop.c
	$(CC) -c src/Shop.c -o src/Shop.o $(LIB)

src/Player.o: src/Player.c
	$(CC) -c src/Player.c -o src/Player.o $(LIB)

clear:
	del src\\*.o