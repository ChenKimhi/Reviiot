CC=g++
CFLAGS=-g -Wall -Weffc++ -std=c++11
LFLAGS  =  -L/usr/lib

all: bin/Card.o bin/Hand.o bin/Deck.o bin/Player.o bin/Game.o bin/reviiyot.o
	$(CC) bin/Card.o bin/Hand.o bin/Deck.o bin/Player.o  bin/Game.o bin/reviiyot.o -o bin/reviiot $(LFLAGS)

bin/Card.o : src/Card.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Card.o src/Card.cpp

bin/Hand.o : src/Hand.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Hand.o src/Hand.cpp

bin/Deck.o : src/Deck.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Deck.o src/Deck.cpp

bin/Player.o : src/Player.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Player.o src/Player.cpp

 
bin/Game.o : src/Game.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Game.o src/Game.cpp

bin/reviiyot.o : src/reviiyot.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/reviiyot.o src/reviiyot.cpp

clean:
	rm -f bin/*
