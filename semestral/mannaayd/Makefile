CC=g++
CFLAGS=-c -w -g -std=c++14 -Wall -pedantic -Wno-long-long -O0 -ggdb 
CLIBS=-std=c++14 -lSDL2 -lSDL2_image

all: doc mannaayd

mannaayd: Ant.o Anthill.o Enemy.o Game.o Map.o Menu.o Number.o Object.o Obstacle.o Participant.o Player.o Source.o Table.o Textures.o 
	$(CC) Ant.o Anthill.o Enemy.o Game.o Map.o Menu.o Number.o Object.o Obstacle.o Participant.o Player.o Source.o Table.o Textures.o  -o "mannaayd" $(CLIBS)

Ant.o: src/Ant.cpp src/Anthill.h src/Object.h src/Ant.h 
	$(CC) $(CFLAGS) src/Ant.cpp -o $@

Anthill.o: src/Anthill.cpp src/Object.h src/Table.h src/Ant.h src/Anthill.h 
	$(CC) $(CFLAGS) src/Anthill.cpp -o $@

Enemy.o: src/Enemy.cpp src/Enemy.h src/Player.h src/Participant.h 
	$(CC) $(CFLAGS) src/Enemy.cpp -o $@

Map.o: src/Map.cpp src/Game.h src/Enemy.h src/Player.h src/Obstacle.h src/Anthill.h src/Textures.h src/Table.h src/Map.h 
	$(CC) $(CFLAGS) src/Map.cpp -o $@

Game.o: src/Game.cpp src/Textures.h src/Player.h src/Object.h src/Table.h src/Number.h src/Map.h src/Participant.h src/Enemy.h src/Ant.h src/Anthill.h src/Menu.h src/Obstacle.h src/Game.h 
	$(CC) $(CFLAGS) src/Game.cpp -o $@

Menu.o: src/Menu.cpp src/Object.h src/Textures.h src/Menu.h 
	$(CC) $(CFLAGS) src/Menu.cpp -o $@

Number.o: src/Number.cpp src/Object.h src/Textures.h src/Number.h 
	$(CC) $(CFLAGS) src/Number.cpp -o $@

Object.o: src/Object.cpp src/Textures.h src/Game.h src/Object.h 
	$(CC) $(CFLAGS) src/Object.cpp -o $@

Obstacle.o: src/Obstacle.cpp src/Object.h src/Obstacle.h 
	$(CC) $(CFLAGS) src/Obstacle.cpp -o $@

Participant.o: src/Participant.cpp src/Anthill.h src/Game.h src/Participant.h 
	$(CC) $(CFLAGS) src/Participant.cpp -o $@

Player.o: src/Player.cpp src/Player.h src/Enemy.h src/Participant.h 
	$(CC) $(CFLAGS) src/Player.cpp -o $@

Source.o: src/Source.cpp src/Game.h
	$(CC) $(CFLAGS) src/Source.cpp -o $@

Table.o: src/Table.cpp src/Number.h src/Table.h 
	$(CC) $(CFLAGS) src/Table.cpp -o $@

Textures.o: src/Textures.cpp src/Game.h src/Textures.h 
	$(CC) $(CFLAGS) src/Textures.cpp -o $@




doc:
	doxygen doxygen.conf
	mv doc/html/* doc/
	rm -r doc/html

documentation: doc
	firefox doc/index.html

clean:
	rm -f *.o
	rm -f mannaayd
	rm -rf doc
	rm -rf *.dSYM

compile: doc mannaayd

run: doc mannaayd
	./mannaayd
