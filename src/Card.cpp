#include "Card.h"
#include <string>


Card::Card() :shape()
{
}

Card::Card(Shape _shape) : shape(_shape)
{
}


Shape Card::getShape()
{
    return shape;
}

void Card::setShape(Shape other)
{
    shape = other;
}

Card::Card(Card& card) : shape(card.shape)
{
}


Card::~Card()
{
}

Card& Card::operator=(Card& other) {
    shape = other.getShape();
    return *this;
}

bool Card::operator==(Card& other) {
    return (this->toString().compare(other.toString()) == 0) ;
}

bool Card::operator<(Card &other) {
    string strThis = this->toString();
    string strOther = other.toString();

    char thisShape = strThis.back();
    char otherShape = strOther.back();

    strThis.pop_back();
    strOther.pop_back();

    if(strThis.at(0)== 'A'){
        if (strOther.at(0) == 'A')
            return thisShape < otherShape;
        else
            return false;
    }
    else if (strOther.at(0) == 'A')
        return true;

    if(strThis.at(0)== 'K'){
        if (strOther.at(0) == 'K')
            return thisShape < otherShape;
        else
            return false;
    }
    else if (strOther.at(0) == 'K')
        return true;

    if(strThis.at(0)== 'Q'){
        if (strOther.at(0) == 'Q')
            return thisShape < otherShape;
        else
            return false;
    }
    else if (strOther.at(0) == 'Q')
        return true;

    if(strThis.at(0)== 'J'){
        if (strOther.at(0) == 'J')
            return thisShape < otherShape;
        else
            return false;
    }
    else if (strOther.at(0) == 'J')
        return true;
    //if we got to this line, both card are of type NumericCard

    int thisVal = stoi(strThis, 0 ,10);
    int otherVal = stoi(strOther, 0, 10);

    if (thisVal == otherVal)
        return thisShape < otherShape;
    else
        return thisVal < otherVal;

}


FigureCard::FigureCard() : Card(), figure()
{
}

FigureCard::FigureCard(Shape _shape, Figure _figure): Card(_shape), figure(_figure)
{
}

FigureCard::FigureCard(FigureCard& other):Card(other.getShape()), figure(other.figure)
{
}

FigureCard *FigureCard::clone() {
    return (new FigureCard(*this));
}

Figure& FigureCard::getFigure()
{
    return figure;
}

string FigureCard::toString()
{
    string ret = "";
    switch (getFigure())
    {
        case Jack:
            ret = ret + "J";
            break;
        case Queen:
            ret = ret + "Q";
            break;
        case King:
            ret = ret + "K";
            break;
        case Ace:
            ret = ret + "A";
            break;
        default:
            ret = "unexpected figure at toString";
    }
    switch(getShape())
    {
        case Club:
            ret = ret + "C";
            break;
        case Diamond:
            ret = ret + "D";
            break;
        case Heart:
            ret = ret + "H";
            break;
        case Spade:
            ret = ret + "S";
            break;
        default:
            ret = "unexpected shape in toString";
    }
    return ret;
}



FigureCard::~FigureCard()
{
}

FigureCard &FigureCard::operator=(FigureCard& other) {
    figure = other.figure;
    this->setShape(other.getShape());
    return *this;
}

bool FigureCard::operator==(FigureCard& other) {
    return this->toString() == other.toString();
}



NumericCard::NumericCard() : number()
{
}

NumericCard::NumericCard(Shape _shape, int _number): Card(_shape), number(_number)
{
}

NumericCard::NumericCard(NumericCard& card): Card(card.getShape()), number(card.number)
{
}

NumericCard* NumericCard::clone()
{
    return (new NumericCard(*this));
}

int NumericCard::getNumber()
{
    return number;
}

string NumericCard::toString()
{
    string ret = to_string(getNumber());
    Shape tmp = getShape();
    switch(tmp)
    {
        case Club:
            ret = ret + "C";
            break;
        case Diamond:
            ret = ret + "D";
            break;
        case Heart:
            ret = ret + "H";
            break;
        case Spade:
            ret = ret + "S";
            break;
        default:
            ret = "unexpected shape in toString";
    }

    return ret;
}

NumericCard::~NumericCard()
{
}

NumericCard& NumericCard::operator=(NumericCard& other) {
    this->number = other.number;
    this->setShape(other.getShape());
    return *this;
}

bool NumericCard::operator==(NumericCard& other) {
    return this->toString() == other.toString();
}




