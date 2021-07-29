/*网络流
求关键割边，求一次最大流后，对残余网络dfs，从s出发能到达的点
记为1，能到t的记为2，如果有单向边，起点标记为1，终点标记为2，
则关键割边数量加1。注意建的反向边实际上并不存在！！
http://poj.org/problem?id=3204
*/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<vector>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
const int maxn = 520;
struct node
{
    int to, flow, rev, fa;
    node(int a, int b, int c, int d):to(a),flow(b),rev(c), fa(d){
    }
};
vector<node> g[maxn];
int vis[maxn], dis[maxn], res[maxn];
void dfs(int s, int t);
void add(int fr, int to, int flow);
int dinic(int s, int t);
int bfs(int s, int t, int ans);
void dfst(int t);
void dfss(int s);

int main()
{
    int n, m, i, j, k;
    scanf("%d %d", &n, &m);
    while(m--)
    {
        scanf("%d %d %d", &i, &j, &k);
        add(i, j, k);
    }
    int ans = dinic(0, n-1), num = 0;
    memset(res, 0, sizeof(res));
    dfss(0);
    dfst(n-1);
    for(i=0;i<n;i++)
    {
        if(res[i] == 1)
            for(j=0;j<g[i].size();j++)
            {
                if(res[g[i][j].to] == 2 && g[i][j].fa == 1)
                    num++;
            }
    }
    printf("%d\n", num);
    return 0;
}

void add(int fr, int to, int flow)
{
    g[fr].push_back(node(to, flow, g[to].size(), 1));
    g[to].push_back(node(fr, 0, g[fr].size()-1, 0));
}

int dinic(int s, int t)
{
    int res = 0;
    while(1)
    {
        dfs(s, t);
        if(dis[t]<0)return res;
        int d;
        memset(vis, 0, sizeof(vis));
        while((d=bfs(s, t, INF))>0)
            res += d;
    }
}

void dfs(int s, int t)
{
    memset(dis, -1, sizeof(dis));
    queue<int> que;
    que.push(s);
    dis[s] = 0;
    while(!que.empty())
    {
        int u = que.front();que.pop();
        for(int i=0;i<g[u].size();i++)
        {
            node e = g[u][i];
            if(e.flow>0 && dis[e.to]<0)
            {
                dis[e.to] = dis[u]+1;
                que.push(e.to);
            }
        }
    }
}

int bfs(int s, int t, int ans)
{
    if(s == t)return ans;
    for(int &i=vis[s];i<g[s].size();i++)
    {
        node &e = g[s][i];
        if(e.flow>0 && dis[e.to] == dis[s]+1)
        {
            int d = bfs(e.to, t, min(ans, e.flow));
            if(d>0){
                e.flow -= d;
                g[e.to][e.rev].flow += d;
                return d;
            }
        }
    }
    return 0;
}

void dfss(int s)
{
    res[s] = 1;
    for(int i=0;i<g[s].size();i++)
    {
        node e = g[s][i];
        if(!res[e.to] && e.flow>0)
            dfss(e.to);
    }
}

void dfst(int t)
{
    res[t] = 2;
    for(int i=0;i<g[t].size();i++)
    {
        node e = g[t][i];
        if(!res[e.to] && g[e.to][e.rev].flow>0)
            dfst(e.to);
    }
}
