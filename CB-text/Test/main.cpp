#include <iostream>
#include <vector>

#define INF 0xfff

using namespace std;

vector<vector<int> > Mat;
int iMin = INF;

void dfs(int x, int y, int m, int sum)
{
    if(x < m && y < m)
    {
        sum += Mat[x][y];
        if(x == m-1 && y == m-1)
        {
            iMin = iMin < sum ? iMin : sum;
            return;
        }
        dfs(x+1, y, m, sum);
        dfs(x, y+1, m, sum);
    }
}

void print(int m)
{
//    print
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cout << Mat[i][j] << ' ';
        }
        cout << endl;
    }
}

int main()
{
    int opNum = 0;
    int sameNum = 0;
    string s1, s2;
    cin >> s1 >> s2;
    if(s1 != s2)
    {
        for(int i = 0; i < s1.length() && i < s2.length(); i++)
        {
            if(s1[s1.length() - i - 1] == s2[s2.length() - i - 1])
            {
                sameNum = i+1;
            }
            else{
                break;
            }
        }
        opNum = s1.length() - sameNum + s2.length() - sameNum;
    }
    cout << "sameNum:" << sameNum << endl;
    cout << opNum << endl;
}
