#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <istream>
#include <fstream>
#include <string>

#include "Player.h"
#include "Deck.h"

using namespace std;

class Game {
private:
    vector <Player *> players;  //The list of the players
    Deck deck;                 //The deck of the game
    string verbal;
    void readFile(char* configFile);
    void addCardByString(string card_str);
    int turnCounter;
    string winnerName1;
    string winnerName2;
    void reviiyaCheckAtInit(size_t i);

public:
    Game(char* configurationFile);
    Game(const Game& otherGame);
    void init();
    void play();
    void printState();        //Print the state of the game as described in the assignment.
    void printWinner();       //Print the winner of the game as describe in the assignment.
    void printNumberOfTurns(); //Print the number of played turns at any given time.
    ~Game();
};

#endif
