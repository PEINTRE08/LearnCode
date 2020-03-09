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
    void deBet(int);//��ע
    void addBet(int);//Ӯ
    void sortCards();//����������
    void delCard(int);//ɾ��ָ������
    string printCard(int);
    int gethandNum();
    int getFace(int);
    int getBet();
    int getSuit(int);
    int getcurrenthand();
    void altercurrenthand(int);//�޸�����
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
