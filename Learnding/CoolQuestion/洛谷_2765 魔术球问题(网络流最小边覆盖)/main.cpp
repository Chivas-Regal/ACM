/*****************************************
网络流，最小边覆盖
n个柱子，一次放1，2，3...号球，要求同一柱子上，相邻的两个
球和为完全平方数
题解：分析题目，发现满足单调性，可以二分，只需检验n个柱子能否
将mid个球全部放进去。考虑各个球的关系，对球i，如果可以与
球j相邻，则连接i->j的边，建完图可以发现是一个DAG图。现在的目标
是寻找最少的路径覆盖所有边，边不能复用。可以发现这是最经典的最小边
覆盖问题，求出图的最小边覆盖，如果小于等于n，则当前mid个球即可全部
放到n个柱子上

路径不重复最小边覆盖：
在有向图中，设s为源点，t为汇点，将每个点分为x和x'，连边s->x容量为1，
x'->t容量为1,对于每条边i到j，连边i->j'容量为1。剪完图后：
最小边覆盖 = 点的总数 - 图的最大流(上面二分图的最大匹配)

题目链接：https://www.luogu.org/problem/P2765
*****************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 3200;
const int mod = 2015;
struct node{
    int to, nex, cap, flow;
}eg[maxn*maxn];
int ed, cnt, hd[maxn], dis[maxn], vis[maxn];
int xx[1020], b[1600][100], len[1600], c[maxn];
vector<int> g[100];
int solve(int n);
void getball(int l, int n);
void init();
int Find(int x);
void add(int from, int to, int cap);
int dinic(int s, int t);
bool bfs(int s, int t);
int dfs(int s, int t, int ans);
bool isok(int mid, int n);

int main()
{
    int n, l, r, i, j;
    //预处理，求能和i相邻的数
    for(i=0;i<=1000;i++)xx[i] = i*i;
    for(i=1;i<=1600;i++){
        for(j=1;xx[j] <= i+1600;j++){
            if(xx[j]-i > i && xx[j]-i<=1600){
                b[i][len[i]++] = xx[j]-i;
            }
        }
    }
    scanf("%d", &n);
    l = solve(n);
    printf("%d\n", l);
    getball(l, n);
    for(i=1;i<=n;i++)
    {
        for(j=0;j<g[i].size()-1;j++)
            printf("%d ", g[i][j]);
        printf("%d\n", g[i][g[i].size()-1]);
    }
    return 0;
}

int Find(int x)
{
    return c[x]=x==c[x]?x:Find(c[x]);
}
//获取方案
void getball(int l, int n)
{
    map<int,int> mp;
    isok(l, n);
    int i, j, k=0;
    for(i=1;i<=l;i++)c[i] = i;
    for(i=1;i<=l;i++){
        for(j=hd[i];j!=-1;j=eg[j].nex)
        if(eg[j].flow == eg[j].cap && eg[j].to > l){
            int x = Find(i), y = Find(eg[j].to-l);
            if(c[x] != y)c[x] = y;
        }
    }
    for(i=1;i<=l;i++){
        c[i] = Find(i);
        if(mp[c[i]] == 0)mp[c[i]] = ++k;
        g[mp[c[i]]].push_back(i);
    }
}
/*
利用残留网络，继续跑网络流
int solve(int n)
{
    int i, j, k, res = 0;
    init();
    ed = 1599*2;
    for(i=1;;i++)
    {
        add(0, 2*i, 1);
        add(2*i+1, ed, 1);
        for(j=1;xx[j]-i<i;j++)
        {
            if(xx[j] - i > 0){
                add(2*i, 2*(xx[j]-i)+1, 1);
            }
        }
        res += dinic(0, ed);
        if(i-res > n)break;
    }
    return i-1;
}
*/
//二分答案
int solve(int n)
{
    int l, r;
    l = n, r = 1600;
    while(l<r)
    {
        int mid = (l+r+1)/2;
        if(isok(mid, n))
            l = mid;
        else r = mid-1;
    }
    return l;
}
//检验mid个球能否全部放到n个柱子上
bool isok(int mid, int n)
{
    init();
    int ed = mid + mid + 1;
    for(int i=1;i<=mid;i++)
    {
        //将入点向源点连边，出点向汇点连边
        add(0, i, 1);
        add(i+mid, ed, 1);
        for(int j=0;j<len[i] && b[i][j] <= mid;j++)
            add(i, b[i][j]+mid, 1);
    }
    int ans = dinic(0, ed);
    return mid-ans <= n;
}

void init()
{
    cnt = 1;
    memset(hd, -1, sizeof(hd));
}

void add(int from, int to, int cap)
{
    eg[++cnt].to = to;
    eg[cnt].cap = cap;
    eg[cnt].flow = 0;
    eg[cnt].nex = hd[from];
    hd[from] = cnt;
    eg[++cnt].to = from;
    eg[cnt].cap = 0;
    eg[cnt].flow = 0;
    eg[cnt].nex = hd[to];
    hd[to] = cnt;
}

int dinic(int s, int t)
{
    int res = 0;
    while(bfs(s, t))
    {
        for(int i=0;i<=t;i++)
            vis[i] = hd[i];
        int d;
        while((d=dfs(s, t, INF))>0)
            res += d;
    }
    return res;
}

bool bfs(int s, int t)
{
    for(int i=0;i<=t;i++)
        dis[i] = -1;
    queue<int> que;
    que.push(s);
    dis[s] = 0;
    while(!que.empty())
    {
        int u = que.front();que.pop();
        for(int i=hd[u];i!=-1;i=eg[i].nex)
        {
            node e = eg[i];
            if(e.cap>e.flow && dis[e.to] == -1)
            {
                dis[e.to] = dis[u]+1;
                que.push(e.to);
            }
        }
    }
    return dis[t] != -1;
}

int dfs(int s, int t, int ans)
{
    if(s == t)return ans;
    for(int &i=vis[s];i!=-1;i=eg[i].nex)
    {
        node e = eg[i];
        if(e.cap > e.flow && dis[e.to] == dis[s]+1)
        {
            int d = dfs(e.to, t, min(ans, e.cap-e.flow));
            if(d>0)
            {
                eg[i].flow += d;
                eg[i^1].flow -= d;
                return d;
            }
        }
    }
    return 0;
}
