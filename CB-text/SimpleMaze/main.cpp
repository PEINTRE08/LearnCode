// �Թ��������.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
#include <iostream>
#include <set>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <stack>

#define INF 0xfff

using namespace std;

set<int> connected;                                  /*����һ�����������ж��Թ��Ƿ�ȫ��ͨ*/
int Edg_numbers = 0;                                /*�ߵ�����*/
int N;

typedef struct Node                                        /*������Ľṹ�壬����id��4�������ָ��*/
{
    int id;
    int right, left, up, down;
} Node;

void addEge_level(Node &n1, Node &n2, int type)      /*����Ӻ�ߵĺ���*/
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

void addEge_vertical(Node &n1, Node &n2, int type)    /*��������ߵĺ���*/
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
    n��           �������
    s��           Դ��
    G��           ͼ���ڽӾ���
    vis��         ��Ƕ����Ƿ��ѱ�����
    d��           �洢Դ��s���������������̾���
    pre��         �洢�����s���ﶥ��v�����·����v��ǰһ������ ������ӣ�
    */
    fill(d.begin(), d.end(), INF);                         //��ʼ����̾������ȫ��ΪINF

    d[s] = 0;                                              //���s��������ľ���Ϊ0

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
        //�Ҳ���С��INF��d[u]��˵��ʣ�µĶ�������s����ͨ
        if (u == -1)
            return;
        vis[u] = true;                                  //���u�ѱ�����
        for (int v = 0; v < n; ++v)
        {
            //�������ж��㣬���vδ������&&u�ܹ�����v&&��uΪ�н�����ʹd[v]����
            if (vis[v] == false && G[u][v] != INF)
            {
                if(d[u] + G[u][v] < d[v])
                {
                    d[v] = d[u] + G[u][v];             //����d[v]
                    //if(!pre[v].empty())
                    //{
                    pre[v].clear();                    //���֮ǰ����Ϣ
                    //}
                    pre[v].push_back(u);               //��¼v��ǰ������Ϊu������ӣ�
                }
                else if(d[u]+G[u][v] == d[v])
                {
                    pre[v].push_back(u);//���һ���µĽڵ�
                }
            }
        }
    }
}

vector<int> ans;//���ڴ洢���·��
stack<int> path;
//��������s������v�����·��
void DFSPrint(int s, int v, vector<int> pre[])
{
    for(int i = 0;i < pre[v].size();i++){
		ans.push_back(pre[v][i]);
		if(pre[v][i] == s){
			for(int j = 0; j < ans.size(); j++){
                path.push(ans[j]);
			}
		}
		DFSPrint(s, pre[v][i], pre);//����һ��
		ans.pop_back();//ɾ���ϸ�Ԫ��
	}
}

int main()
{
    vector<Node> nodes;                           /*����һ������������*/
    vector<vector<int> > G;
    cout << "Please enter a N to construct a N*N maze: ";
    cin >> N;                                    /*����һ��N������N*N���Թ�*/


    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            Node n;                             /*ѭ�����ɽ��*/
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
    while (connected.size() < N * N || Edg_numbers <= int(1.5*N*N-N-0.5))        /*whileѭ�����Թ�Ϊȫ��ͨ�ұߵ���������Ҫ��*/
    {
        //connected.clear();
        //Edg_numbers = 0;
        for (int i = 0; i < N; i++)                                  /*�᷽��������ӱ�*/
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
        for (int i = 0; i < N - 1; ++i)                             /*������������ӱ�*/
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

    for (int i = 0; i < N; i++)                               /*���Թ���ӡ����*/
    {
        for (int j = 0; j < N; j++)
        {
            if (nodes[i * N + j].id < 10)                     /*������ʮλ�����ֲ�0�����Թ�����*/
                cout << "0" << nodes[i * N + j].id;
            else
                cout << nodes[i * N + j].id;
            if ((i * N + j) % N != N - 1)                     /*���������ָ��ָ���ұߵ�������ô��ӡ��-���������ӡ�� ��*/
            {
                if (nodes[i * N + j].right == nodes[i * N + j + 1].id)
                    cout << "-";
                else
                    cout << " ";
            }
            if ((i * N + j) % N == N - 1)                     /*�������id��Nȡ�����N-1������Ҫ����*/
            {
                cout << endl;
                for (int m = 0; m < N; m++)                   /*����ѭ���ж���һ�ŵĽ�����ָ���Ƿ�ָ����һ�Ŷ�Ӧ�Ľ�㣬����У���ӡ��|  ����û�д�ӡ��   ����λ*/
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
                        if (m == N - 1)                        /*����жϵ���һ�е����һ����㣬��Ҫ����*/
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
    int a;                                            /*��������Ҫ�ҵ�����a��b*/
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
            cout << "Entered Character Overload!";         /*����������ֹ������ʾ*/
        }
    }
    cout << "The closest path from a to b is(are):" << endl;
    vector<bool> vis(N*N);
    vector<int> d(N*N);
    vector<int>* pre = new vector<int>[N*N];//·����Ϣ

    Dijkstra(N*N,a,G,vis,d, pre);

    //��������s������v�����·��
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
// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���:
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
