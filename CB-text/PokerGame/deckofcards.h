#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H
#include "card.h"
#include "poker.h"
#include "person.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class DeckOfCards
{
public:
    DeckOfCards();
    void shuffle();//洗牌
    void deleteCard(char, string);
    void PrintAllCard();
    void judgeWinMan(Person,Person,Person,Person);//判断谁赢的机制

    void PlayGame();

private:
    vector<Card> deck;
    int initBet=10;
    int deckAllBet;
    int currentCard;//删除之后桌上有几张牌
    poker poker;
};
#endif // DECKOFCARDS_H
