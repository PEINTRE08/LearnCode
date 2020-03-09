#include "person.h"

Person::Person() {}

Person::Person(int num, vector<Card> p, bool v, string n)
{
    handNum=num;
    Name=n;
    bet=50;
    currenthand=0;
    hand=p;
    vip=v;
}

string Person::getName()
{
    return Name;
}

void Person::delCard(int num)//用vector的erase删除指定手牌
{
    hand.erase(hand.begin()+num);
    handNum-=1;
}

int Person::getFace(int num)
{
    return hand[num].getFace();
}

int Person::getBet()
{
    return bet;
}

int Person::gethandNum()
{
    return handNum;
}

string Person::printCard(int num)
{
    return hand[num%handNum].toString();
}

int Person::getSuit(int num)
{
    return hand[num].getSuit();
}

void Person::deBet(int b)
{
    bet-=b;
}

void Person::addBet(int a)
{
    bet+=a;
}

int Person::getcurrenthand()
{
    return currenthand;
}

void Person::altercurrenthand(int n)
{
    currenthand = n;
}

bool cmpSuit(Card a, Card b)//设置花色排序的对比规则
{
    return a.getSuit() < b.getSuit();
}

bool cmpFace(Card a, Card b)//设置牌面排序对比规则
{
    return a.getFace() > b.getFace();
}

void Person::sortCards()
{
    vector<Card> sortCard=hand;
    int start[4]= {0};
    int k = 1;

    sort(sortCard.begin(), sortCard.end(), cmpSuit);//先将花色排序

    for(int i = 0; i < handNum-1; i++)//记录每个花色的初始位置
    {
        if(sortCard[i].getSuit() != sortCard[i+1].getSuit())
        {
            start[k++]=i+1;
        }
    }

    sort(sortCard.begin(), sortCard.begin()+start[1], cmpFace);//对每个花色进行排序，
    sort(sortCard.begin()+start[1], sortCard.begin()+start[2], cmpFace);
    sort(sortCard.begin()+start[2], sortCard.begin()+start[3], cmpFace);
    sort(sortCard.begin()+start[3], sortCard.end(), cmpFace);

    hand = sortCard;
}
