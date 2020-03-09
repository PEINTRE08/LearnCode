#include "poker.h"

poker::poker()
{

}

poker::~poker()
{

}

const string poker::faceNames[totalFaces+GhostSuits]= {"3","4","5","6","7","8","9","10","J","Q","K","A","2","*","**"};
const char poker::suitNames[totalSuits+GhostSuits]= {3, 4, 5, 6, 1, 2};
