#ifndef POKER_H
#define POKER_H
#include <string>

using namespace std;

class poker
{
public:
    static const int allCards=54;//һ���ư���������54����
    static const int totalFaces=13;
    static const int totalSuits=4;
    static const int GhostSuits=2;
    poker();
    virtual ~poker();

    static const string faceNames[totalFaces+GhostSuits];//ʵ���Ƶ���ֵ
    static const char suitNames[totalSuits+GhostSuits];//ʵ���ƵĻ�ɫ
};

#endif // POKER_H
