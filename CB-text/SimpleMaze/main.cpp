// 迷宫问题求解.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
#include <set>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <stack>

#define INF 0xfff

using namespace std;

set<int> connected;                                  /*定义一个集合用来判断迷宫是否全连通*/
int Edg_numbers = 0;                                /*边的数量*/
int N;

typedef struct Node                                        /*构造结点的结构体，包含id，4个方向的指针*/
{
    int id;
    int right, left, up, down;
} Node;

void addEge_level(Node &n1, Node &n2, int type)      /*定义加横边的函数*/
{
    switch (type)
    {
    case 0:
        break;
    case 1:
        Edg_numbers++;
        n1.right = n2.id;
        n2.left = n1.id;
        connected.insert(n1.id);
        connected.insert(n2.id);
        break;
    }
}

void addEge_vertical(Node &n1, Node &n2, int type)    /*定义加竖边的函数*/
{
    switch (type)
    {
    case 0:
        break;
    case 1:
        Edg_numbers++;
        n1.down = n2.id;
        n2.up = n1.id;
        connected.insert(n1.id);
        connected.insert(n2.id);
        break;
    }
}


void Dijkstra(int n, int s, vector<vector<int> > G, vector<bool>& vis, vector<int>& d, vector<int> pre[])
{
    /*
    param
    n：           顶点个数
    s：           源点
    G：           图的邻接矩阵
    vis：         标记顶点是否已被访问
    d：           存储源点s到达其它顶点的最短距离
    pre：         存储从起点s到达顶点v的最短路径上v的前一个顶点 （新添加）
    */
    fill(d.begin(), d.end(), INF);                         //初始化最短距离矩阵，全部为INF

    d[s] = 0;                                              //起点s到达自身的距离为0

    for (int i = 0; i < n; ++i)
    {
        int u = -1;
        int MIN = INF;
        for (int j = 0; j < n; ++j)
        {
            if (vis[j] == false && d[j] < MIN)
            {
                u = j;
                MIN = d[j];
            }
        }
        //找不到小于INF的d[u]，说明剩下的顶点和起点s不连通
        if (u == -1)
            return;
        vis[u] = true;                                  //标记u已被访问
        for (int v = 0; v < n; ++v)
        {
            //遍历所有顶点，如果v未被访问&&u能够到达v&&以u为中介点可以使d[v]更优
            if (vis[v] == false && G[u][v] != INF)
            {
                if(d[u] + G[u][v] < d[v])
                {
                    d[v] = d[u] + G[u][v];             //更新d[v]
                    //if(!pre[v].empty())
                    //{
                    pre[v].clear();                    //清除之前的信息
                    //}
                    pre[v].push_back(u);               //记录v的前驱顶点为u（新添加）
                }
                else if(d[u]+G[u][v] == d[v])
                {
                    pre[v].push_back(u);//添加一个新的节点
                }
            }
        }
    }
}

vector<int> ans;//用于存储结果路径
stack<int> path;
//输出从起点s到顶点v的最短路径
void DFSPrint(int s, int v, vector<int> pre[])
{
    for(int i = 0;i < pre[v].size();i++){
		ans.push_back(pre[v][i]);
		if(pre[v][i] == s){
			for(int j = 0; j < ans.size(); j++){
                path.push(ans[j]);
			}
		}
		DFSPrint(s, pre[v][i], pre);//往下一层
		ans.pop_back();//删除上个元素
	}
}

int main()
{
    vector<Node> nodes;                           /*定义一个向量储存结点*/
    vector<vector<int> > G;
    cout << "Please enter a N to construct a N*N maze: ";
    cin >> N;                                    /*输入一个N，生成N*N的迷宫*/


    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            Node n;                             /*循环生成结点*/
            n.id = i * N + j;
            nodes.push_back(n);
        }
    }

    for(int i = 0; i < N*N; i++)
    {
        vector<int> temp;
        for(int j = 0; j < N*N; j++)
        {
            if(i == j)
            {
                temp.push_back(0);
            }
            else
            {
                temp.push_back(INF);
            }
        }
        G.push_back(temp);
    }

    srand(unsigned(time(0)));
    while (connected.size() < N * N || Edg_numbers <= int(1.5*N*N-N-0.5))        /*while循环至迷宫为全连通且边的数量满足要求*/
    {
        //connected.clear();
        //Edg_numbers = 0;
        for (int i = 0; i < N; i++)                                  /*横方向上随机加边*/
        {
            for (int j = 0; j < N - 1; j++)
            {
                if(nodes[i*N+j].right != nodes[i*N+j+1].id)
                {
                    int c = rand()%2;
                    int x1 = i * N + j, x2 = i * N + j + 1;
                    addEge_level(nodes[x1], nodes[x2], c);
                    if(c)
                    {
                        G[x1][x2] = 1;
                        G[x2][x1] = 1;
                    }
                }
            }
        }
        for (int i = 0; i < N - 1; ++i)                             /*竖方向上随机加边*/
        {
            for (int j = 0; j < N; ++j)
            {
                if(nodes[i*N+j].down != nodes[(i+1)*N+j].id)
                {
                    int v = rand()%2;
                    int x1 = i * N + j, x2 = (i+1) * N + j;
                    addEge_vertical(nodes[i * N + j], nodes[(i+1) * N + j], v);
                    if(v)
                    {
                        G[x1][x2] = 1;
                        G[x2][x1] = 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < N; i++)                               /*将迷宫打印出来*/
    {
        for (int j = 0; j < N; j++)
        {
            if (nodes[i * N + j].id < 10)                     /*将不足十位的数字补0，让迷宫对齐*/
                cout << "0" << nodes[i * N + j].id;
            else
                cout << nodes[i * N + j].id;
            if ((i * N + j) % N != N - 1)                     /*如果结点的右指针指向右边的数，那么打印“-”，否则打印“ ”*/
            {
                if (nodes[i * N + j].right == nodes[i * N + j + 1].id)
                    cout << "-";
                else
                    cout << " ";
            }
            if ((i * N + j) % N == N - 1)                     /*如果结点的id对N取余等于N-1，则需要换行*/
            {
                cout << endl;
                for (int m = 0; m < N; m++)                   /*利用循环判断上一排的结点的下指针是否指向下一排对应的结点，如果有，打印“|  ”，没有打印“   ”补位*/
                {
                    if (i < N - 1)
                    {
                        if (m < N - 1)
                        {
                            if (nodes[m + i * N].down == nodes[m + i * N + N].id)
                                cout << "|  ";
                            else
                                cout << "   ";
                        }
                        if (m == N - 1)                        /*如果判断到了一行的最后一个结点，需要换行*/
                        {
                            if (nodes[m + i * N].down == nodes[m + i * N + N].id)
                                cout << "|  ";
                            else
                                cout << "   ";
                            cout << endl;
                        }

                    }
                }
            }
        }
    }

    cout << endl;
    int a;                                            /*定义两个要找的数字a和b*/
    int b;
    while(1)
    {
        cout << "Enter a and b (a<b) to find the closest path :" << endl;
        cout << "a: ";
        cin >> a;
        cout << "b: " ;
        cin >> b;
        if(a >= 0 && a < N * N && b >= 0 && b < N * N)
            break;
        else
        {
            cout << "Entered Character Overload!";         /*如果输入数字过大的提示*/
        }
    }
    cout << "The closest path from a to b is(are):" << endl;
    vector<bool> vis(N*N);
    vector<int> d(N*N);
    vector<int>* pre = new vector<int>[N*N];//路径信息

    Dijkstra(N*N,a,G,vis,d, pre);

    //输出从起点s到顶点v的最短路径
    ans.push_back(b);
    DFSPrint(a, b, pre);

    while(!path.empty())
    {
        cout << path.top() << ' ';
        if(path.top() == b)
        {
            cout << endl;
        }
        path.pop();
    }

    return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
