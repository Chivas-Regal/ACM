//floyd算法
//有些点在固定时间点后才能使用，问某个时间点两个点
//的最短路
//题解：因为题目没有说固定起点或终点，并且N<=200
//很容易想到floyd，但由于部分结点可能不可用，所以
//此题考的就是floyd的细节理解
//floyd有三层循环，最外层的k代表考虑经过k点中转
//的情况(不一定走k点)，i、j代表从i到j的当前最短距离，
//k的循环结束，表示经过k可以改变的最短路都已更新 
//ps：写的乱七八糟的，看书吧，白书P103 
//题目链接：https://www.luogu.org/problemnew/show/P1119 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<string>
#include<ctype.h>
#include<cstring>
#include<stack>
#include<queue>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 220;
int a[maxn][maxn], tim[maxn];

int main()
{
    int n, m, q, t, i, j, k, l, r;
    scanf("%d %d", &n, &m);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
    	if(i == j)a[i][i] = 0;
    	else a[i][j] = INF;
    for(i=0;i<n;i++)
        scanf("%d", &tim[i]);
    while(m--)
    {
        scanf("%d %d %d", &i, &j, &k);
        a[i][j] = a[j][i] = k;
    }
    l = r = 0;
    scanf("%d", &q);
    while(q--)
    {
        int f, t, d;
        scanf("%d %d %d", &f, &t, &d);
        while(l<n && tim[l]<=d)l++;
        for(k=r;k<l;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                a[i][j] = min(a[i][j], a[i][k]+a[k][j]);
        if(d < tim[f] || d < tim[t] || a[f][t] == INF)
            printf("-1\n");
        else
            printf("%d\n", a[f][t]);
        r = l;
    }
    return 0;
}

