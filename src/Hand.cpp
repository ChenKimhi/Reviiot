#include "Hand.h"



Hand::Hand() : hand(), numberOfCards(0)
{
}

Hand::Hand(vector<Card*> _hand): hand(), numberOfCards(0)
{
    clean();
    hand.clear();
    for (size_t i=0; i < hand.size(); i++)
    {
        Card* toInsert = hand.at(i)->clone();
        hand.push_back(toInsert);
        numberOfCards++;
    }
}


Hand::Hand(const Hand& other): hand(), numberOfCards(0)
{
    clean();
    hand.clear();
    for (size_t i=0; i < other.hand.size(); i++)
    {
        Card* toInsert = other.hand.at(i)->clone();
        hand.push_back(toInsert);
        numberOfCards++;
    }

}


Hand& Hand::operator=(Hand & other)
{



    clean();
    hand.clear();
    for (size_t i=0; i < hand.size(); i++)
    {
        Card* toInsert = hand.at(i)->clone();
        hand.push_back(toInsert);
        numberOfCards++;
    }
    return *this;
}

const vector<Card*>& Hand::getHand() const
{
    return hand;
}


bool Hand::addCard(Card & card)
{
    size_t i = 0;
    while ((i < hand.size()) && (*(hand.at(i)) < card)) {
        i++;
    }
    if(i == hand.size()|| card < *(hand.at(i))){
        hand.insert(hand.begin() + i, &card);
        numberOfCards++;
        return true;
    }

    return false;

}

bool Hand::removeCard(Card &card)
{
    size_t i = 0;
    while(i<hand.size() && *(hand.at(i)) < card){
        i++;
    }
    if(i<hand.size() && *(hand.at(i)) == card)
    {
        hand.erase(hand.begin() + i);
        numberOfCards--;
        return true;
    }
    return false;
}

void Hand::setNumberOfCards(int _NumberOfCards)
{
    numberOfCards = _NumberOfCards;
}

int Hand::getNumberOfCards()
{
    return numberOfCards;
}

string Hand::toString()
{
    string s = "";
    for (size_t i = 0; i < hand.size(); i++) {
        s = s + hand.at(i)->toString() + " ";
    }

    return s;
}

void Hand::clean()
{
    for(size_t i=0; i<hand.size();i++){
        delete hand.at(i);
         hand.at(i) = nullptr;
    }
    hand.clear();
}

Hand::~Hand()
{
    clean();
}

void Hand::checkForReviiya(string cardValue)
{
    int counter=0;
    for(size_t j = 0; j<hand.size(); j++){
        string tmp_str = hand.at(j)->toString();
        tmp_str.pop_back();
        if(cardValue.compare(tmp_str) == 0)
            counter++;
    }

    if(counter==4)
    {
        size_t j = 0;
        while(j < hand.size()){
            string tmp_str = hand.at(j)->toString();
            tmp_str.pop_back();
            if(cardValue.compare(tmp_str) == 0) {
                delete hand.at(j);
                hand.erase(hand.begin() + j);
                numberOfCards--;

            }
            else
                j++;
        }
    }
}



