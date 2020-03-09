#ifndef CARD_H
#define CARD_H
#include "poker.h"

class Card
{
public:

    Card();
    Card(int,int);
    int getFace();
    int getSuit();
    string getFaceName();
    char getSuitName();
    string toString();

private:
    int face, suit;//牌的编号
    poker poker;
};

#endif // CARD_H
