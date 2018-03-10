#ifndef HAND_H_
#define HAND_H_

#include <iostream>
#include <vector>

#include "Card.h"

using namespace std;

class Hand {
private:
    vector<Card*> hand;
    int numberOfCards;

public:
    Hand();
    Hand(vector<Card*> _hand);
    Hand(const Hand& other);
    vector<Card*>& operator=(const vector<Card*>& other);
    Hand& operator=(Hand& other);
    const vector<Card*>& getHand() const;
    bool addCard(Card &card);
    bool removeCard(Card &card);
    void setNumberOfCards(int _NumberOfCards);
    int getNumberOfCards(); // Get the number of cards in hand
    string toString(); // Return a list of the cards, separated by space, in one line, in a sorted order, ex: "2S 5D 10H"
    //void checkForReviiya(Card& card);
    virtual void clean();
    virtual ~Hand();
    void checkForReviiya(string cardValue);
};

#endif