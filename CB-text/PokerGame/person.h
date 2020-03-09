#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <algorithm>
#include <vector>
#include "card.h"

class Person
{
public:
    Person();
    Person(int, vector<Card>, bool, string);
    void deBet(int);//下注
    void addBet(int);//赢
    void sortCards();//对手牌排序
    void delCard(int);//删除指定卡牌
    string printCard(int);
    int gethandNum();
    int getFace(int);
    int getBet();
    int getSuit(int);
    int getcurrenthand();
    void altercurrenthand(int);//修改手牌
    string getName();

private:
    int handNum;
    string Name;
    bool vip;
    int currenthand;
    int bet;
    vector<Card> hand;
};


#endif // PERSON_H
