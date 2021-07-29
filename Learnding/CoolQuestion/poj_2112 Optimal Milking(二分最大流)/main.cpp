//二分+网络流最大流
//设置超级源点s和超级汇点t，将s与各挤奶机添加
//流量为m的边(限制挤奶机的使用次数)，将奶牛与t
//添加流量为1的边，然后用Floyed_Warshall跑出奶牛
//到各挤奶机的最短路。将奶牛最远的最小距离作为
//二分的条件，跑dinic，如果流量等于奶牛数量，则
//代表可以完成
//题目链接：http://poj.org/problem?id=2112
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
struct node
{
	int to, flow, rev;
	node(int a, int b, int c):to(a),flow(b),rev(c){
	}
};
vector<node> g[2020];
int a[260][260], vis[2020], dis[2020];
void add(int from, int to, int flow);
int dinic(int s, int t);
void bfs(int s, int t);
int dfs(int s, int t, int ans);

int main()
{
	int K, C, m, i, j, k, ed;
	scanf("%d %d %d", &K, &C, &m);
	ed = K+C+1;
	for(i=1;i<ed;i++)
		for(j=1;j<ed;j++)
		{
			scanf("%d", &a[i][j]);
			if(a[i][j] == 0)a[i][j] = INF;
		}
	for(k=1;k<ed;k++)
		for(i=1;i<ed;i++)
			for(j=1;j<ed;j++)
			a[i][j] = min(a[i][j],a[i][k]+a[k][j]);
	int l = 0, r = 220*ed;
	while(l<r)
	{
		int mid = (l+r)/2;
		//清除vector 
		for(i=0;i<=ed;i++)g[i].clear(); 
		for(i=1;i<=K;i++)add(0, i, m);
		for(i=1;i<=C;i++)add(K+i, ed, 1);
		for(i=1;i<=K;i++)
			for(j=K+1;j<ed;j++)
			//如果可以距离小于等于mid，则添加边 
			if(a[i][j]<=mid)
					add(i, j, mid);
		int ans = dinic(0, ed); 
		if(ans == C)
			r = mid;
		else
			l = mid+1;
	}
	printf("%d", l);
	return 0;
}

void add(int from, int to, int flow)
{
	g[from].push_back(node(to, flow, g[to].size()));
	g[to].push_back(node(from, 0, g[from].size()-1));
}

int dinic(int s, int t)
{
	int res = 0;
	while(1)
	{
		bfs(s, t);
		if(dis[t]<0)return res;
		memset(vis, 0, sizeof(vis));
		int d;
		while((d=dfs(s, t, INF))>0)
			res += d;
	}
}

void bfs(int s, int t)
{
	memset(dis, -1, sizeof(dis));
	queue<int> que;
	que.push(s);
	dis[s] = 0;
	while(!que.empty())
	{
		int u = que.front();
		que.pop();
		for(int i=0;i<g[u].size();i++)
		{
			node &e = g[u][i];
			if(e.flow > 0 && dis[e.to]<0)
			{
				dis[e.to] = dis[u]+1;
				que.push(e.to);
			}
		}
	}
}

int dfs(int s, int t, int ans)
{
	if(s == t)return ans;
	for(int &i=vis[s];i<g[s].size();i++)
	{
		node &e = g[s][i];
		if(e.flow>0 && dis[e.to] == dis[s]+1)
		{
			int d = dfs(e.to, t, min(ans, e.flow));
			if(d>0){
				e.flow -= d;
				g[e.to][e.rev].flow += d;
				return d;
			}
		}
	}
	return 0;
}
