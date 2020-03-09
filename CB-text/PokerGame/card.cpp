#include "card.h"

Card::Card()
{

}

Card::Card(int faceNumber,int suitNumber)
{
    face=faceNumber;
    suit=suitNumber;
}

string Card::toString()
{
    return poker.suitNames[suit] + poker.faceNames[face];
}

string Card::getFaceName()
{
    return poker.faceNames[face];
}

char Card::getSuitName()
{
    return poker.suitNames[suit];
}

int Card::getFace()
{
    return face;
}
int Card::getSuit()
{
    return suit;
}
