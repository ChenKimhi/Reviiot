#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

#include "Hand.h"
#include <Hand.h>

using namespace std;

class Player : public Hand {
private:
    const string name;
    const int N;
public:
    Player();
    Player(string _name, const int _N);
    Player(const Player& other);
    const string getName() const;   //Returns the name of the player
    const int getN() const;
    int askForCards(Player* toAsk, string cardString);
    virtual  Player* clone()=0;
    virtual size_t playerToAskFrom(vector<Player*>* players) = 0;
    virtual string getCardToAsk() = 0;
    virtual int getStrategy() = 0;
    virtual void setStrategy(int _strategy) = 0;
    virtual ~Player();
};

class PlayerType1 : public Player {  //For strategy 1
private:
    int strategy;
public:
    PlayerType1();
    PlayerType1(string _name, const int _N);
    PlayerType1(const PlayerType1& other);
    virtual  PlayerType1* clone()  ;
    string getCardToAsk();
    size_t playerToAskFrom(vector<Player*>* players);
    int getStrategy();
    void setStrategy(int _strategy);
    virtual ~PlayerType1();
};

class PlayerType2 : public Player {  //For strategy 2
private:
    int strategy;
public:
    PlayerType2();
    PlayerType2(string _name, const int _N);
    PlayerType2(const PlayerType2& other);
    virtual  PlayerType2* clone();
    string getCardToAsk();
    size_t playerToAskFrom(vector<Player*>* players);
    int getStrategy();
    void setStrategy(int _strategy);
    virtual ~PlayerType2();

};

class PlayerType3 : public Player {  //For strategy 3
private:
    int strategy;
    int posOfPlayerToAsk;
public:
    PlayerType3();
    PlayerType3(string _name, const int _N);
    PlayerType3(const PlayerType3& other);
    virtual  PlayerType3* clone();
    string getCardToAsk();
    size_t playerToAskFrom(vector<Player*>* players);
    int getStrategy();
    void setStrategy(int _strategy);
    virtual ~PlayerType3();



};

class PlayerType4 : public Player {  //For strategy 4
private:
    int strategy;
    int posOfPlayerToAsk;
public:
    PlayerType4();
    PlayerType4(string _name, const int _N);
    PlayerType4(const PlayerType4& other);
    virtual  PlayerType4* clone();
    string getCardToAsk();
    size_t playerToAskFrom(vector<Player*>* players);
    int getStrategy();
    void setStrategy(int _strategy);
    virtual ~PlayerType4();
};

#endif
