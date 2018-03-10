
#include "Player.h"

Player::Player() :Hand(), name(), N()
{
}

Player::Player(string _name, const int _N) : Hand(), name(_name), N(_N)
{
}

Player::Player(const Player &other): Hand(other), name(other.name), N(other.N)
{
}

const string Player::getName() const
{
    return name;
}

const int Player::getN() const
{
    return N;
}

int Player::askForCards(Player* toAsk, string cardValueString) {
    int ret = 0;
    size_t i=0;
    while(i < toAsk->getHand().size()){
        string tmpStr = toAsk->getHand().at(i)->toString();
        tmpStr.pop_back();
        if(cardValueString.compare(tmpStr)==0){
            Card* tmpCard = (toAsk->getHand().at(i));

            toAsk->removeCard(*(toAsk->getHand().at(i)));
            this->addCard(*tmpCard);

            ret++;
        }
        else{
            i++;
        }
    }
    checkForReviiya(cardValueString);
    return ret;
}


Player::~Player()
{
}



PlayerType1::PlayerType1() :Player(), strategy(1) 
{
}

PlayerType1::PlayerType1(string _name, const int _N) : Player(_name, _N) , strategy(1)
{
}

PlayerType1::PlayerType1(const PlayerType1& other): Player(other), strategy(1)
{
}

string PlayerType1::getCardToAsk() {
    int cardsCounter[getN()+5];
    for(int j=0; j<getN()+5; j++){
        cardsCounter[j] = 0;
    }

    for(size_t i = 0; i < getHand().size(); i++)
    {
        string currCardValue = (getHand().at(i))->toString();
        currCardValue.pop_back();
        switch (currCardValue.at(0))
        {
            case 'J' : cardsCounter[getN()+1]++; break;
            case 'Q' : cardsCounter[getN()+2]++; break;
            case 'K' : cardsCounter[getN()+3]++; break;
            case 'A' : cardsCounter[getN()+4]++; break;
            default :
                cardsCounter[stoi(currCardValue,0,10)]++;
        }
    }
    int numberOfCardsInIndex = 0;
    int position = 0;
    for(int i = getN()+4; i>=2;i--){
        if(cardsCounter[i] > numberOfCardsInIndex) {
            position = i;
            numberOfCardsInIndex= cardsCounter[i];
        }
    }
    string strToReturn;

    if(position == getN()+1){
        strToReturn = "J";
    }

    else if(position == getN()+2){
        strToReturn = "Q";
    }
    else if(position == getN()+3){
        strToReturn = "K";
    }
    else if(position == getN()+4){
        strToReturn = "A";
    }
    else strToReturn = to_string(position);

    return  strToReturn;
}

PlayerType1::~PlayerType1()
{
}

int PlayerType1::getStrategy() {
    return strategy;
}

size_t PlayerType1::playerToAskFrom(vector<Player *>* players) {
    size_t position;

    if(this->getName().compare(players->at(0)->getName()) == 0){
        position = 1;
    }
    else {  position = 0;}
    for(size_t i = 0; i < players->size(); i++){
        if(this->getName().compare(players->at(i)->getName()) != 0){
            if(players->at(i)->getNumberOfCards() >= players->at(position)->getNumberOfCards())
                position = i;
        }
    }

    return position;
}

void PlayerType1::setStrategy(int _strategy)
{
    strategy = _strategy;
}

PlayerType1 *PlayerType1::clone()  {
    return (new PlayerType1(*this));
}






PlayerType2::PlayerType2():Player(), strategy(2)
{
}

PlayerType2::PlayerType2(string _name, const int _N) : Player(_name, _N), strategy(2)
{
}

PlayerType2::PlayerType2(const PlayerType2 &other):Player(other),strategy(2)
{
}

string PlayerType2::getCardToAsk() {
    int cardsCounter[getN()+5];
    for(int j=0; j<getN()+5; j++){
        cardsCounter[j] = 0;
    }

    for(size_t i = 0; i < getHand().size(); i++)
    {
        string currCardValue = (getHand().at(i))->toString();
        currCardValue.pop_back();
        switch (currCardValue.at(0))
        {
            case 'J' : cardsCounter[getN()+1]++; break;
            case 'Q' : cardsCounter[getN()+2]++; break;
            case 'K' : cardsCounter[getN()+3]++; break;
            case 'A' : cardsCounter[getN()+4]++; break;
            default :
                cardsCounter[stoi(currCardValue,0,10)]++;
        }
    }
    int numberOfCardsInIndex = 4;
    int position = 0;
    for(int i = 2; i< getN()+5; i++){
        if(cardsCounter[i] > 0 && cardsCounter[i] < numberOfCardsInIndex ) {
            position = i;
            numberOfCardsInIndex= cardsCounter[i];
        }
    }
    string strToReturn;

    if(position == getN()+1){
        strToReturn = "J";
    }

    else if(position == getN()+2){
        strToReturn = "Q";
    }
    else if(position == getN()+3){
        strToReturn = "K";
    }
    else if(position == getN()+4){
        strToReturn = "A";
    }
    else strToReturn = to_string(position);

    return  strToReturn;
}

PlayerType2::~PlayerType2() {}

int PlayerType2::getStrategy() {
    return strategy;
}

size_t PlayerType2::playerToAskFrom(vector<Player *> *players) {
    size_t position;

    if(this->getName().compare(players->at(0)->getName()) == 0){
        position = 1;
    }
    else {  position = 0;}
    for(size_t i = 0; i < players->size(); i++){
        if(this->getName().compare(players->at(i)->getName()) != 0){
            if(players->at(i)->getNumberOfCards() >= players->at(position)->getNumberOfCards())
                position = i;
        }
    }

    return position;
}

void PlayerType2::setStrategy(int _strategy)
{
    strategy = _strategy;
}

PlayerType2 *PlayerType2::clone() {
    return (new PlayerType2(*this));
}








PlayerType3::PlayerType3() : Player(), strategy(3), posOfPlayerToAsk(-1)
{
}

PlayerType3::PlayerType3(string _name, const int _N) : Player(_name, _N), strategy(3), posOfPlayerToAsk(-1)
{
}

PlayerType3::PlayerType3(const PlayerType3 &other):Player(other), strategy(3), posOfPlayerToAsk(other.posOfPlayerToAsk)
{
}

string PlayerType3::getCardToAsk() {
    string strToReturn;
    strToReturn = getHand().at(getHand().size() - 1)->toString();
    strToReturn.pop_back();
    return strToReturn;

}

size_t PlayerType3::playerToAskFrom(vector<Player *>* players) {
    posOfPlayerToAsk = (posOfPlayerToAsk+1) % players->size();
    if(players->at(posOfPlayerToAsk)->getName().compare(this->getName()) == 0){
        posOfPlayerToAsk++;
    }
    return (posOfPlayerToAsk % players->size());

}

PlayerType3::~PlayerType3() {}

int PlayerType3::getStrategy() {
    return strategy;
}

void PlayerType3::setStrategy(int _strategy)
{
    strategy = _strategy;
}

PlayerType3 *PlayerType3::clone() {
    return (new PlayerType3(*this));
}






PlayerType4::PlayerType4() : Player(), strategy(4), posOfPlayerToAsk(-1)
{
}

PlayerType4::PlayerType4(string _name, const int _N) : Player(_name, _N), strategy(4), posOfPlayerToAsk(-1)
{
}

PlayerType4::PlayerType4(const PlayerType4 &other):Player(other), strategy(4), posOfPlayerToAsk(other.posOfPlayerToAsk)
{
}

string PlayerType4::getCardToAsk() {
    string strToReturn;
    strToReturn = getHand().at(0)->toString();
    strToReturn.pop_back();
    return strToReturn;

}

size_t PlayerType4::playerToAskFrom(vector<Player *>* players) {
    posOfPlayerToAsk = (posOfPlayerToAsk+1) % players->size();
    if(players->at(posOfPlayerToAsk)->getName().compare(this->getName()) == 0){
        posOfPlayerToAsk++;
    }
    return (posOfPlayerToAsk % players->size());

}

PlayerType4::~PlayerType4() {}

int PlayerType4::getStrategy() {
    return strategy;
}

void PlayerType4::setStrategy(int _strategy)
{
    strategy = _strategy;
}

PlayerType4 *PlayerType4::clone() {
    return (new PlayerType4(*this));
}
