#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
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

class Person
{
public:
    Person();
    Person(int, vector<Card>, bool, string, string);
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
    string getPassword();
    string getName();

private:
    string pas;
    int handNum;
    string Name;
    bool vip;
    int currenthand;
    int bet;
    vector<Card> hand;
};

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
    int initBet;
    int deckAllBet;
    int currentCard;//删除之后桌上有几张牌
    poker poker;
};

poker::poker()
{

}

poker::~poker()
{

}

const string poker::faceNames[totalFaces+GhostSuits]= {"3","4","5","6","7","8","9","10","J","Q","K","A","2","*","**"};
const char poker::suitNames[totalSuits+GhostSuits]= {3, 4, 5, 6, 1, 2};

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

Person::Person() {}

Person::Person(int num, vector<Card> p, bool v, string n, string pa)
{
    handNum=num;
    Name=n;
    bet=50;
    currenthand=0;
    hand=p;
    vip=v;
    pas=pa;
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

string Person::getPassword()
{
    return pas;
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

DeckOfCards::DeckOfCards()
{
    //currentCard=0;
    int i, j;
    Card card;
    for(i = 0; i < poker.totalSuits; i++)
    {
        for(j = 0; j < poker.totalFaces; j++)
        {
            card=Card(j, i);
            deck.push_back(card);
        }
    }
    card=Card(j++, i++);
    deck.push_back(card);//add ghost card

    card=Card(j,i);
    deck.push_back(card);

    currentCard=poker.allCards;

    deckAllBet=0;

    initBet=10;
}

void DeckOfCards::deleteCard(char s, string f)
{
    char t=0;
    switch(s){
        case 'H':t=3;break;
        case 'D':t=4;break;
        case 'C':t=5;break;
        case 'S':t=6;break;
        case '1':t=1;break;
        case '2':t=2;break;
    }
    for(int i = 0; i < currentCard; i++)
    {
        if(deck[i].getSuitName() == t && deck[i].getFaceName() == f)
        {
            cout << "Successfully Delete " << deck[i].toString() << endl;
            deck.erase(deck.begin()+i);
            currentCard--;
            i--;
        }
    }
}

void DeckOfCards::shuffle()
{
    srand(time(0));

    int swapRandom[54];

    for(int i=0; i<currentCard; i++)//利用rand（）先随机生成一个随机数组
        swapRandom[i]=int(rand())%currentCard;

    for(int i=0; i<currentCard; i++)//让有序数组与随机数组的值对换
    {
        Card swapCard;
        swapCard=deck[i];
        deck[i]=deck[swapRandom[i]];
        deck[swapRandom[i]]=swapCard;
    }

}

void DeckOfCards::PrintAllCard()
{
    for(int i=0; i<currentCard; i++)
    {
        cout << deck[i].toString() << '\t';
        if((i+1)%13==0)
            cout << endl;
    }
    cout << endl;
}

void DeckOfCards::PlayGame()
{
    //显示所有纸牌
    PrintAllCard();

    //删除指定牌
    cout << "是否要删除纸牌（按y/n)" << '\t';
    char del;
    cin >> del;
    if(del == 'y' || del == 'Y')
    {
        cout << "请输入删除牌数" << '\t';
        int delNum=0;
        cin >> delNum;
        cout << "***********************************" << endl;
        cout << "*花色说明：                       *" << endl;
        cout << "*          H：" << (char)3 << "                   *" << endl;
        cout << "*          D：" << (char)4 << "                   *" << endl;
        cout << "*          C：" << (char)5 << "                   *" << endl;
        cout << "*          S：" << (char)6 << "                   *" << endl;
        cout << "*          1：" << (char)1 << '\t' << "*: " << (char)1 << "              *" << endl;
        cout << "*          2：" << (char)2 << '\t' << "**: " << (char)2 << "             *" << endl;
        cout << "***********************************" << endl;
        for(int i = 0; i < delNum; i++)
        {
            cout << "请输入要删除的牌的花色" << '\t';
            char delSuit;
            cin >> delSuit;
            cout << "请输入要删除的牌" << '\t';
            string delFace;
            cin >> delFace;
            deleteCard(delSuit, delFace);
        }
    }

    //显示余牌
    PrintAllCard();

    //洗牌
    shuffle();

    //创建四名玩家并且发牌
    vector<Card> p1, p2, p3, p4;
    int num = currentCard/4, i = 0;//平均分发纸牌，多余的牌丢弃
    for(i = 0; i < num; i++)
    {
        p4.push_back(deck[i]);
    }
    for(i = num;i < num*2; i++)
    {
        p3.push_back(deck[i]);
    }
    for(i = num*2; i < num*3; i++)
    {
        p2.push_back(deck[i]);
    }
    for(i = num*3; i < num*4; i++)
    {
        p1.push_back(deck[i]);
    }
    cout << "请输入您的游戏名称：";
    string vipName;
    cin >> vipName;
    cout << "请输入您的密码：";
    string password;
    cin >> password;
    Person player1=Person(num, p1, 1, vipName, password); //vip高级玩家
    //player1.sortCards();
    Person player2=Person(num, p2, 0, "Player2", "0");
    //player2.sortCards();
    Person player3=Person(num, p3, 0, "Player3", "0");
    //player3.sortCards();
    Person player4=Person(num, p4, 0, "Player4", "0");
    //player4.sortCards();

    //Begin
    char continuePlay;
    do{
        //下注之前判断玩家是否还有赌注
        if(player1.getBet() == 0 || player2.getBet() == 0 || player3.getBet() == 0 || player4.getBet() == 0)
        {
            cout << "有玩家赌注不足，游戏结束" << endl;
            break;
        }
        //最开始下注
        player1.deBet(initBet);
        player2.deBet(initBet);
        player3.deBet(initBet);
        player4.deBet(initBet);

        deckAllBet=initBet*4;
        cout << "下注10 现桌上有40赌注" << endl;

        //抽牌
        char continueH;
        do{
            cout << "您当前牌为：" << player1.printCard(player1.getcurrenthand()) << '\t' << player1.printCard(player1.getcurrenthand()+1) << endl;
            cout << "是否更换牌？(y/n)" << '\t';
            cin >> continueH;
            if(continueH == 'y' || continueH == 'Y')
            {
                cout << "请输入您的密码：";
                cin >> password;
                if(password == player1.getPassword())
                {
                    player1.altercurrenthand(player1.getcurrenthand()+1);
                }
            }
        }while((continueH == 'y' || continueH == 'Y') && password == player1.getPassword());

        //vip加注
        char look;
        cout << "是否查看其他玩家的手牌？(y/n)" << '\t';
        cin >> look;
        if(look == 'y' || look == 'Y')
        {
            cout << "Player2: " << player2.printCard(0) << '\t' << player2.printCard(1) << endl;
            cout << "Player3: " << player3.printCard(0) << '\t' << player3.printCard(1) << endl;
            cout << "Player4: " << player4.printCard(0) << '\t' << player4.printCard(1) << endl;
        }
        char continueBet;
        cout << "你现在有赌注" << player1.getBet() << endl;
        cout << "请问是否加注？（y/n）" << '\t';
        cin >> continueBet;
        if(continueBet == 'y' || continueBet == 'Y')
        {
            cout << "请输入加多少注：";
            int debet=0;
            cin >> debet;
            player1.deBet(debet);
            deckAllBet+=debet;
        }

        //机器人加注
        if(player2.getFace(0) + player2.getFace(1) > 7)
        {
            int tempbet=int(rand())%9+1;
            if(player2.getBet() < tempbet)
            {
                tempbet=player2.getBet();
            }
            player2.deBet(tempbet);
            cout << "Player2加注" << tempbet << endl;
            deckAllBet+=tempbet;
        }
        if(player3.getFace(0) + player3.getFace(1) > 7)
        {
            int tempbet=int(rand())%9+1;
            if(player3.getBet() < tempbet)
            {
                tempbet=player3.getBet();
            }
            player3.deBet(tempbet);
            cout << "Player3加注" << tempbet << endl;
            deckAllBet+=tempbet;
        }
        if(player4.getFace(0) + player4.getFace(1) > 7)
        {
            int tempbet=int(rand())%9+1;
            if(player4.getBet() < tempbet)
            {
                tempbet=player4.getBet();
            }
            player4.deBet(tempbet);
            cout << "Player2加注" << tempbet << endl;
            deckAllBet+=tempbet;
        }
        cout << "目前桌上有赌注" << deckAllBet << endl;
        judgeWinMan(player1, player2, player3, player4);
        player1.delCard(player1.getcurrenthand());//出牌
        player1.delCard(player1.getcurrenthand()+1);
        player2.delCard(player2.getcurrenthand());
        player2.delCard(player2.getcurrenthand()+1);
        player3.delCard(player3.getcurrenthand());
        player3.delCard(player3.getcurrenthand()+1);
        player4.delCard(player4.getcurrenthand());
        player3.delCard(player4.getcurrenthand()+1);
        cout << "请问要继续游戏吗？(y/n)" << '\t';
        cin >> continuePlay;
    }while((continuePlay == 'y' || continuePlay == 'Y') && player1.gethandNum() >= 2);
}

Person twoCmp(vector<Person> p)
{
    if(p[0].getFace(p[0].getcurrenthand()) > p[1].getFace(p[1].getcurrenthand()))
    {
        return p[0];
    }
    else if(p[0].getFace(p[0].getcurrenthand()) < p[1].getFace(p[1].getcurrenthand()))
    {
        return p[1];
    }
    else
    {
        if(p[0].getSuit(p[0].getcurrenthand()) == 6 || p[0].getSuit(p[0].getcurrenthand()+1) == 6)
        {
            return p[1];
        }
        else
        {
            return p[2];
        }
    }
}

bool cmpDeckFace(Person a, Person b)
{
    return a.getFace(a.getcurrenthand()) > b.getFace(b.getcurrenthand());
}

bool cmpTwo(Person a, Person b)
{
    return a.getFace(a.getcurrenthand()) + a.getFace(a.getcurrenthand()+1) > b.getFace(b.getcurrenthand()) + b.getFace(b.getcurrenthand()+1);
}

void DeckOfCards::judgeWinMan(Person p1,Person p2, Person p3, Person p4)
{
    int doubleC1 = 0, doubleC2 = 0, doubleC3 = 0, doubleC4 = 0;
    vector<Person> doubleMan;
    if(p1.getFace(p1.getcurrenthand()) == p1.getFace(p1.getcurrenthand()+1))//判断是否是对牌
    {
        doubleC1 = 1;
        doubleMan.push_back(p1);
    }
    if(p2.getFace(p2.getcurrenthand()) == p2.getFace(p2.getcurrenthand()+1))
    {
        doubleC2 = 1;
        doubleMan.push_back(p2);
    }
    if(p3.getFace(p3.getcurrenthand()) == p3.getFace(p3.getcurrenthand()+1))
    {
        doubleC3 = 1;
        doubleMan.push_back(p3);
    }
    if(p4.getFace(p4.getcurrenthand()) == p4.getFace(p4.getcurrenthand()+1))
    {
        doubleC4 = 1;
        doubleMan.push_back(p4);
    }
    if(doubleC1 || doubleC2 || doubleC3 || doubleC4)//存在对牌
    {
        if(doubleMan.size() == 1)
        {
            cout << doubleMan[0].getName() << " Win!" << endl;
            doubleMan[0].addBet(deckAllBet);
            cout << doubleMan[0].getName() << ": " << doubleMan[0].getBet() << endl;
        }
        else
        {
            sort(doubleMan.begin(), doubleMan.end(), cmpDeckFace);
            Person temp = twoCmp(doubleMan);
            cout << temp.getName() << " Win!" << endl;
            temp.addBet(deckAllBet);
            cout << temp.getName() << ": " << temp.getBet() << endl;
        }
    }
    else//将两张牌之和排序
    {
        vector<Person> player;
        player.push_back(p1);
        player.push_back(p2);
        player.push_back(p3);
        player.push_back(p4);
        sort(player.begin(), player.end(), cmpTwo);
        cout << player[0].getName() << " Win!" << endl;
        player[0].addBet(deckAllBet);
        cout << player[0].getName() << ": " << player[0].getBet() << endl;
    }
}

int main()
{
    DeckOfCards adeck;
    adeck.PlayGame();
    return 0;
}
