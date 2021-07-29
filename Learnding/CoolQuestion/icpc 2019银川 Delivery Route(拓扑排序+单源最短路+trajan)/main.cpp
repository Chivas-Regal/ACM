/***************************************************
拓扑排序+单源最短路
有x条双向边和y条单向边，双向边权值一定为正，单向边权值可能为负，单向边从i到j，则保证j不能到i，求s点到其他点的最短距离。

思路：带负权，不能用dijsktra，点数过多，用spfa会超时。因为题目要求限制，只有单向边会有负权值，所以将双向边作为一个图，求强连通分量，然后缩点。再连接单向边，则新的图肯定是一个DAG图。拓扑排序，对新图的点内更新使用dijsktra更新最短路，新点与新点之间暴力以下所有边，更新最短路即可。

题目链接：https://www.jisuanke.com/contest/6038/327719
****************************************************/
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
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 30000;
const int mod = 1e9+7;
struct node{
	int to, nex, cost;
}eg[7*maxn];
struct oed{
	int fr, to, cost;
}oy[2*maxn];
struct qued{
	int u;
	LL p;
	qued(){}
	qued(int a, LL b){
		u = a, p = b;
	}
	bool operator <(qued b)const{
		return p>b.p;
	}
};
int n, tot, top, cnt, sum, hd1[maxn], hd2[maxn], vis[maxn];
LL dis[maxn];
int col[maxn], st[maxn], in[maxn], dfn[maxn], low[maxn];
vector<int> g[maxn];
void init();
void spfa(int s);
void dfs(int u);
void trajan(int u);
void solve(int s);
void dijsktra(int u);
void add(int fr, int to, int cost, int hd[]);

int main()
{
	init();
	int x, y, i, j, s, k, c, num = 1;
	scanf("%d %d %d %d", &n, &x, &y, &s);
	for(i=1;i<=x;i++){
		scanf("%d %d %d", &j, &k, &c);
		add(j, k, c, hd1);
		add(k, j, c, hd1);
	}
	for(i=1;i<=y;i++){
		scanf("%d %d %d", &oy[i].fr, &oy[i].to, &oy[i].cost);
		add(oy[i].fr, oy[i].to, oy[i].cost, hd2);
	}
	//缩点
	for(i=1;i<=n;i++)
		if(dfn[i] == -1)
			trajan(i);
	for(i=1;i<=y;i++){
		in[col[oy[i].to]]++;
	}
	solve(s);
	for(i=1;i<=n;i++)
		if(dis[i]>= 1000000000000LL)
			printf("NO PATH\n");
		else
			printf("%lld\n", dis[i]);
	return 0;
}

void init()
{
	tot = 0, top = cnt = sum = 0;
	memset(dfn, -1, sizeof(dfn));
	memset(hd1, -1, sizeof(hd1));
	memset(hd2, -1, sizeof(hd2));
	memset(col, -1, sizeof(col));
	memset(in, 0, sizeof(in));
	memset(vis, 0, sizeof(vis));
}

void add(int fr, int to, int cost, int hd[])
{
	eg[++tot].to = to;
	eg[tot].cost = cost;
	eg[tot].nex= hd[fr];
	hd[fr] = tot;
}

void trajan(int u)
{
	dfn[u] = low[u] = ++cnt;
	st[++top] = u;
	vis[u] = 1;
	for(int i=hd1[u];i!=-1;i=eg[i].nex)
	{
		if(dfn[eg[i].to] == -1)
		{
			trajan(eg[i].to);
			low[u] = min(low[u], low[eg[i].to]);
		}
		else if(vis[eg[i].to])
			low[u] = min(low[u], dfn[eg[i].to]);
	}
	for(int i=hd2[u];i!=-1;i=eg[i].nex)
	{
		if(dfn[eg[i].to] == -1)
		{
			trajan(eg[i].to);
			low[u] = min(low[u], low[eg[i].to]);
		}
		else if(vis[eg[i].to])
			low[u] = min(low[u], dfn[eg[i].to]);
	}
	if(dfn[u] == low[u])
	{
		col[u] = ++sum;
		g[sum].push_back(u);
		while(top && st[top] != u)
		{
			col[st[top]] = sum;
			vis[st[top]] = 0;
			g[sum].push_back(st[top]);
			top--;
		}
		top--;
		vis[u] = 0;
	}
}
//拓扑排序
void solve(int s)
{
	int i, j, k, u, top;
	for(i=0;i<=n;i++)
		dis[i] = LLINF;
	dis[s] = 0;
	queue<int> que;
	for(i=1;i<=sum;i++)
		if(in[i] == 0)
			que.push(i);
	while(!que.empty())
	{
		int u = que.front();que.pop();
		//dbg(u);
		//求点内的单源最短路。
		dijsktra(u);
		for(i=0;i<g[u].size();i++)
		{
			for(j=hd2[g[u][i]];j!=-1;j=eg[j].nex)
			{
				in[col[eg[j].to]]--;
				if(in[col[eg[j].to]] == 0)
					que.push(col[eg[j].to]);
			}
		}
	}
}

void dijsktra(int u)
{
	priority_queue<qued> que;
	for(int i=0;i<g[u].size();i++)
	{
		que.push(qued(g[u][i],dis[g[u][i]]));
	}
	while(!que.empty())
	{
		qued p = que.top();que.pop();
		if(p.p > dis[p.u])continue;
		//printf("p.u:%d %d\n", p.u, p.p);
		for(int i=hd1[p.u];i!=-1;i=eg[i].nex)
		{
			if(dis[eg[i].to] > dis[p.u] + eg[i].cost)
			{
				dis[eg[i].to] = dis[p.u] + eg[i].cost;
				que.push(qued(eg[i].to, dis[eg[i].to]));
			}
		}
	}
	//printf("----------------\n");
	for(int i=0;i<g[u].size();i++)
	{
		for(int j=hd2[g[u][i]];j!=-1;j=eg[j].nex)
		{
			dis[eg[j].to] = min(dis[eg[j].to], dis[g[u][i]]+eg[j].cost);
		}
	}
}