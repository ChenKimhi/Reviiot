#include "Game.h"
#include <sstream>

Game::Game(char *configurationFile) : players(), deck(), verbal(""), turnCounter(0), winnerName1(""), winnerName2("")
{
    readFile(configurationFile);
}

Game::Game(const Game &otherGame): players(), deck(otherGame.deck), verbal(otherGame.verbal), turnCounter(otherGame.turnCounter), winnerName1(otherGame.winnerName1), winnerName2(otherGame.winnerName2)
{
    for(size_t i=0; i<otherGame.players.size(); i++)
    {
        this->players.push_back(otherGame.players.at(i)->clone());
    }
}
void Game::readFile(char *configFile)
{
    string currLine;
    ifstream configToRead (configFile);
    int validLinesCounter = 0;
    int HIGHEST_NUMBER = 0;
    int countCheck=0;
    string deckstr = "";

    if (configToRead.is_open())
    {
        while(getline(configToRead, currLine)) {

            countCheck++;
            if (currLine.size() > 0 && currLine.at(0) != '#' && currLine.at(0) != ' ')
            {
                switch (validLinesCounter)
                {
                    case 0 :
                        verbal = verbal + currLine.at(0);
                        validLinesCounter++;
                        break;

                    case 1:
                        HIGHEST_NUMBER = stoi(currLine, 0, 10);
                        validLinesCounter++;
                        break;

                    case 2:
                    {

                        deckstr = deckstr + currLine;
                        validLinesCounter++;
                        break;

                    }

                    case 3:
                    {
                        char strategy = currLine.back();
                        currLine.pop_back();
                        currLine.pop_back();
                        switch (strategy)
                        {
                            case '1' :
                                players.push_back(new PlayerType1(currLine, HIGHEST_NUMBER));
                                break;

                            case '2' :
                                players.push_back(new PlayerType2(currLine, HIGHEST_NUMBER));
                                break;

                            case '3' :
                                players.push_back(new PlayerType3(currLine, HIGHEST_NUMBER));
                                break;

                            case '4' :
                                players.push_back(new PlayerType4(currLine, HIGHEST_NUMBER));
                                break;
                        }

                    }

                }
            }
        }
        istringstream toRead(deckstr);
        string cardToPush;

        while (toRead>> cardToPush)
        {
            addCardByString(cardToPush);
        }

    }
    configToRead.close();
}

void Game::addCardByString(string card_str)
{

    char shapeChar = card_str.back();
    card_str.pop_back();
    Shape shape;
    switch (shapeChar)
    {
        case 'C' : shape = Club; break;
        case 'D' : shape = Diamond; break;
        case 'H' : shape = Heart; break;
        case 'S' : shape = Spade; break;
    }
    Card* cardToInsert;
    switch (card_str.at(0))
    {
        case 'J' :
            cardToInsert = new FigureCard(shape, Jack);
            deck.getDeckVec().push_back(cardToInsert);
            break;
        case 'Q' :
            cardToInsert = new FigureCard(shape, Queen);
            deck.getDeckVec().push_back(cardToInsert);
            break;
        case 'K' :
            cardToInsert = new FigureCard(shape, King);
            deck.getDeckVec().push_back(cardToInsert);
            break;
        case 'A' :
            cardToInsert = new FigureCard(shape, Ace);
            deck.getDeckVec().push_back(cardToInsert);
            break;
        default :
            cardToInsert = new NumericCard(shape, stoi(card_str,0,10));
            deck.getDeckVec().push_back(cardToInsert);
            break;
    }
}

void Game::init()
{

    for(size_t i = 0; i < players.size(); i++)
    {
        for(size_t j = 0; j < 7; j++)
            players.at(i)->addCard(*deck.fetchCard());
        reviiyaCheckAtInit(i);
    }

}

void Game::play()
{
    bool GAME_ON = true;

    

    while (GAME_ON)
    {
        turnCounter++;
        if (verbal == "1")
        {
            cout<<"Turn " << turnCounter<< endl;
            printState();
        }
        size_t plr_index = (turnCounter-1) % players.size();
        size_t plr_to_ask = players.at(plr_index)->playerToAskFrom(&players);
        string card_to_ask_str = players.at(plr_index)->getCardToAsk();
        if (verbal == "1")
        {
            cout << players.at(plr_index)->getName() << " asked " << players.at(plr_to_ask)->getName() << " for the value " << card_to_ask_str << endl;
        }
        int numOfTakenCards;
        numOfTakenCards = players.at(plr_index)->askForCards(players.at(plr_to_ask), card_to_ask_str);
        if(numOfTakenCards == 0 && !deck.getDeckVec().empty())
        {
            Card* cardToCheck = deck.fetchCard();
            players.at(plr_index)->addCard(*cardToCheck);
            string strToCheck= cardToCheck->toString();
            strToCheck.pop_back();
            players.at(plr_index)->checkForReviiya(strToCheck);
        }
        else
        {
            for(int i = 0; i< numOfTakenCards && !deck.getDeckVec().empty(); i++)
            {
                Card* cardToCheck = deck.fetchCard();
                players.at(plr_to_ask)->addCard(*cardToCheck);
                string strToCheck= cardToCheck->toString();
                strToCheck.pop_back();
                players.at(plr_to_ask)->checkForReviiya(strToCheck);
            }

        }

        players.at(plr_index)->checkForReviiya(card_to_ask_str);


        if(players.at(plr_index)->getNumberOfCards() == 0)
        {
            if (players.at(plr_to_ask)->getNumberOfCards() == 0)
            {
                if(plr_index < plr_to_ask)
                {
                    winnerName1 = winnerName1 + players.at(plr_index)->getName();
                    winnerName2 = winnerName2 + players.at(plr_to_ask)->getName();
                }
                else
                {
                    winnerName1 = players.at(plr_to_ask)->getName();
                    winnerName2 = players.at(plr_index)->getName();
                }
            }
            else
                winnerName1 = winnerName1 + players.at(plr_index)->getName();

            GAME_ON = false;
        }

        else if (players.at(plr_to_ask)->getNumberOfCards() == 0)
        {
            winnerName1 = winnerName1 + players.at(plr_to_ask)->getName();
            GAME_ON = false;
        }

    }



}

void Game::printState()
{
    cout<< "Deck: " << deck.toString() << endl;
    for(size_t i = 0; i< players.size(); i++)
        cout<<players.at(i)->getName()<<": "<< players.at(i)->toString()<< endl;
}

void Game::printWinner()
{
    int numOfWinners = 0;
    if (winnerName1.size() > 0)
        numOfWinners++;
    if (winnerName2.size() > 0)
        numOfWinners++;

    if (numOfWinners == 1)
    {
        if(winnerName1.size() > 0)
            cout<< "***** The Winner is: " << winnerName1 << " *****" << endl;
        else
            cout<< "***** The Winner is: " << winnerName2 << " *****" << endl;
    }

    if (numOfWinners == 2)
        cout<< "***** The winners are: " << winnerName1 << " and " << winnerName2 << " *****" << endl;
}

void Game::printNumberOfTurns()
{
    cout << "Number of turns: " << turnCounter <<endl;
}

Game::~Game()
{
    for(size_t i = 0; i < players.size(); i++)
    {
        delete players.at(i);
        players.at(i) = nullptr;

    }
    players.clear();


}

void Game::reviiyaCheckAtInit(size_t i)
{
    for(size_t j = 0; j<4; j++)
    {
        string cardValue = players.at(i)->getHand().at(j)->toString();
        cardValue.pop_back();
        int counter = 0;
        for(size_t k = 0; k < 7; k++)
        {
            string cardToCampare = players.at(i)->getHand().at(k)->toString();
            cardToCampare.pop_back();
            if(cardValue.compare(cardToCampare) == 0)
                counter++;
        }
        if(counter == 4)
            players.at(i)->checkForReviiya(cardValue);

    }

}



