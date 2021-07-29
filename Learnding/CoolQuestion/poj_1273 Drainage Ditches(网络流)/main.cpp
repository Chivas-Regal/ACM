//网络流：Ford_Fulkerson算法 
//入门题目，主要就是加每个边时加的反向边用处
//如果没有反向边，得到结果是10，就如书上210也所说的一样
//有反向边，如果反向边之前走过，则反向边也可以作为正常边使用
//因为如果使用了反向边可以找到到达汇点的流，将反向边的值也减去流值
//就相当于那些流量在反向边的终点分流了出去。 
//《挑战程序设计竞赛》p210页 
//http://poj.org/problem?id=1273
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<queue>
#include<cstring>
#include<vector>
#include<iostream>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
struct node
{
	int to, cap, rev;
	node(int a, int b, int c):to(a),cap(b),rev(c){
	}
};
vector<node> g[248];
int m, vis[248];
int dfs(int s, int t, int cap);
void add(int from, int to, int flow);
int max_flow();

int main()
{
	int n, i, j;
	while(scanf("%d %d", &n, &m)!=EOF)
	{
		for(i=1;i<=m;i++)
			g[i].clear();
		for(i=0;i<n;i++)
		{
			int f, t, flow;
			scanf("%d %d %d", &f, &t, &flow);
			add(f, t, flow);
		}
		int ans = max_flow();
		printf("%d\n", ans);
	}
	return 0;
}

void add(int from, int to, int flow)
{
	g[from].push_back(node(to, flow, g[to].size()));
	g[to].push_back(node(from, 0, g[from].size()-1));
}

int max_flow()
{
	int res = 0;
	for(;;)
	{
		memset(vis, 0, sizeof(vis));
		int d = dfs(1, m, INF);
		if(d == 0)return res;
		res += d;
	}
}

int dfs(int s, int t, int cap)
{
	if(s == t)return cap;
	vis[s] = 1;
	for(int i=0;i<g[s].size();i++)
	{
		node &e = g[s][i];
		if(!vis[e.to] && e.cap > 0)
		{
			int d = dfs(e.to, t, min(e.cap, cap));
			if(d>0)
			{
				e.cap -= d;
				//他的反向边加1 
				g[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}
