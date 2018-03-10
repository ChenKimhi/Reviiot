#ifndef CARD_H_
#define CARD_H_

#include <iostream>
using namespace std;

enum Shape {
    Club,
    Diamond,
    Heart,
    Spade
};

enum Figure {
    Jack,
    Queen,
    King,
    Ace
};

class Card {
private:
    Shape shape;
public:
    Card();
    Card(Shape);
    virtual Card* clone() = 0;
    Shape getShape();
    void setShape(Shape other);
    Card(Card& card);
    virtual Card& operator=(Card &other);
    bool operator == (Card &other);
    virtual bool operator<(Card &other) ;
    virtual string toString() = 0; //Returns the string representation of the ca<value><shape>" exp: "12S" or "QD"
    virtual ~Card();
};

class FigureCard : public Card {
private:
    Figure figure;
public:
    FigureCard();
    FigureCard(Shape, Figure);
    FigureCard(FigureCard& other);
    FigureCard* clone();
    Figure& getFigure();
    virtual string toString() override;
    FigureCard& operator=(FigureCard& other);
    bool operator==(FigureCard& other);
    ~FigureCard();
};

class NumericCard : public Card {
private:
    int number;
public:
    NumericCard();
    NumericCard(Shape,  int);
    NumericCard(NumericCard& card);
    NumericCard* clone();
    int getNumber();
    virtual string toString() override;
    NumericCard& operator=(NumericCard& other);
    bool operator==(NumericCard& other);
    ~NumericCard();
};

#endif
