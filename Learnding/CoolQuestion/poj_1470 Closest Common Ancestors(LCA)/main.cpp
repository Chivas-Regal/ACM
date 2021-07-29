//lca
//倍增思想求LCA，复杂度nlog2n， 
//《挑战程序设计竞赛》p329
//题目链接：http://poj.org/problem?id=1470
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 920;
const int maxv = 12;
vector<int> g[maxn];//图的邻接表示
//root:根节点;dep:深度;par[i][j]:j往上走2^i步的节点
//(超过根节点为-1) 
int root, dep[maxn], vis[maxn], par[maxv+1][maxn];
map<int, int> mp;
int lca(int u, int v);
void init(int n);
void dfs(int v, int p, int d);

int main()
{
	int n, m, i, j, k;
	while(~scanf("%d", &n))
	{
		memset(vis, -1, sizeof(vis));
		for(i=1;i<=n;i++)g[i].clear();
		mp.clear();
		for(i=1;i<=n;i++)
		{
			scanf("%d : ( %d )", &j, &k);
			while(k--)
			{
				int to;
				scanf("%d", &to);
				vis[to] = 1;
				g[j].push_back(to);
			}
		}
		for(i=1;i<=n;i++)if(vis[i]==-1){
			root = i;break;
		}
		init(n);
		scanf("%d", &m);
		while(m--)
		{
			scanf(" ( %d %d )", &i, &j);
			k = lca(i, j);
			mp[k]++;
		}
		map<int,int>::iterator it;
		for(it=mp.begin();it!=mp.end();it++){
			printf("%d:%d\n", it->first, it->second);
		}
	}
	return 0;
}
//初始化深度和往上走2^0步的点 
void dfs(int v, int p, int d){
	par[0][v] = p;
	dep[v] = d;
	for(int i=0;i<g[v].size();i++)
		if(g[v][i] != p)dfs(g[v][i], v, d+1);
}

void init(int n)
{
	dfs(root, -1, 0);
	for(int k=0;k<maxv;k++)
	{
		for(int v=1;v<=n;v++)
			if(par[k][v] < 0)par[k+1][v] = -1;
			else par[k+1][v] = par[k][par[k][v]];
	}
}

int lca(int u, int v)
{ 
	if(dep[u]>dep[v])
	{
		int t=u;
		u=v;
		v=t;
	}
	//设dep[v]-dep[u] = x, 往上走x步，即可保证
	//两点在同一深度，v=par[k][v]即v向上走2^k步 
	for(int k=0;k<maxv;k++){
		if((dep[v]-dep[u]) >> k & 1)
			v = par[k][v];
	}
	if(u == v)return u;
	for(int k=maxv-1;k>=0;k--)
	if(par[k][u] != par[k][v]){
		u = par[k][u];
		v = par[k][v];
	}
	return par[0][u];
}
