#ifndef POKER_H
#define POKER_H
#include <string>

using namespace std;

class poker
{
public:
    static const int allCards=54;//一副牌包含鬼牌有54张牌
    static const int totalFaces=13;
    static const int totalSuits=4;
    static const int GhostSuits=2;
    poker();
    virtual ~poker();

    static const string faceNames[totalFaces+GhostSuits];//实际牌的面值
    static const char suitNames[totalSuits+GhostSuits];//实际牌的花色
};

#endif // POKER_H
