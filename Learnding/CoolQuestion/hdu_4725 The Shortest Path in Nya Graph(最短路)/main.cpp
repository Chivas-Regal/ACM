/*******************************************************
单源最短路

有n个点，每个点都属于某一层，从第x层的点可以到第x+1层的任意点，花费为c，边为双向边，
所以x+1层的点到x层的点花费也为c。另外有额外m条双向边，求1号点到n号点的最小花费。

思路：直接相邻层直接暴力所有点建边显然不行。所以考虑对每一层额外建两个点，分别代表入点和出点
对于层内点，由入点向所有层内点连边，花费0；
所有层内点向出点连边，花费0,；
入点向出点连边，花费0；
每层出点连向相邻层的入点，花费为c;
额外边直接建边即可。
需要注意的是，如果一层是空的，就不要向其相邻层建边了。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=4725
**************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<map>
#include<queue>
#include<stack>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 600100;
const int mod = 1000000007;
struct node{
	int to, w;
	node(){}
	node(int a, int b):to(a),w(b){}
};
vector<node> g[maxn];
int dis[maxn], b[maxn];
void init(int n);
void dijkstra();

int main()
{
	int t, n, m, c, i, j, k;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		scanf("%d %d %d", &n, &m, &c);
		init(n);
		
		for(i=1;i<=n;i++){
			scanf("%d", &j);
			b[j] = 1;
			g[n+j].push_back(node(i, 0));
			g[i].push_back(node(n+n+j, 0));
		}
		for(i=1;i<=n;i++){
			if(b[i]) g[n+i].push_back(node(n+n+i, 0));
			if(b[i] && b[i-1]) g[n+n+i].push_back(node(n+i-1, c));
			if(b[i] && b[i+1]) g[n+n+i].push_back(node(n+i+1, c));
		}
		for(i=1;i<=m;i++){
			int fr, to, nex;
			scanf("%d %d %d", &fr, &to, &nex);
			g[fr].push_back(node(to, nex));
			g[to].push_back(node(fr, nex));
		}
		dijkstra();
		if(dis[n] == INF)printf("Case #%d: -1\n", z);
		else printf("Case #%d: %d\n", z, dis[n]);
	}
	return 0;
}


void init(int n)
{
	for(int i=0;i<3*n+30;i++)
		g[i].clear(), dis[i] = INF, b[i] = 0;
}

void dijkstra()
{
	priority_queue<P, vector<P>, greater<P> > que;
	que.push(P(0, 1));
	dis[1] = 0;
	while(!que.empty())
	{
		P p = que.top();que.pop();
		if(p.first>dis[p.second])continue;
		for(int i=0;i<g[p.second].size();i++)
		{
			node e = g[p.second][i];
			if(dis[e.to] > p.first + e.w)
			{
				dis[e.to] = p.first+e.w;
				que.push(P(dis[e.to], e.to));
			}
		}
	}
}








