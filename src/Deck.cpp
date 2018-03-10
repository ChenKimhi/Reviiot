#include "Deck.h"

Deck::Deck() : deck()
{
}


Deck::Deck(const Deck &other)  : deck()
{
    for(size_t i = 0; i<other.deck.size(); i++){
        Card* tmpCard = other.deck.at(i)->clone();
        deck.push_back(tmpCard);
    }

}

Card * Deck::fetchCard()
{
    Card *c = deck.at(0);
    deck.erase(deck.begin());
    return c;
}

int Deck::getNumberOfCards()
{
    return deck.size();
}

string Deck::toString()
{
    string s = "";
    for (size_t i = 0; i < deck.size(); i++) {
        s = s + deck.at(i)->toString()+" ";
    }
    return s;
}

Deck::~Deck()
{
    for(size_t i = 0; i < deck.size(); i++) {
        delete deck.at(i);
        deck.at(i) = nullptr;
    }
    deck.clear();
}

vector<Card *> &Deck::getDeckVec() {
    return deck;
}



