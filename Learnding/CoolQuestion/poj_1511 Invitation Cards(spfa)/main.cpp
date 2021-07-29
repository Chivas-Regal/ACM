//spfa算法，
//单源最短路，先求1到其余点的最短路，然后求其余点到1的最短路
//求后者时，可以将图中的边求反，然后再从1节点求一遍单源
//最短路即可，此题用未优化的dijkstra会超时，而且还会爆int 
//博客链接：https://blog.csdn.net/rentenglong2012/article/details/78483662
//题目： http://poj.org/problem?id=1511
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<set>
#include<vector>
#include<queue>
#include<iostream>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
struct node
{
	int f, t, p, s;
	node(int a, int b, int c, int d):f(a),t(b),p(c),s(d){
	}
};
vector<node> edge;
vector<int> g[1000010];
int n, dis[1000010], vis[1000010];
void spfa(int n, int s);

int main()
{
	int t, p, i, j, num;
	scanf("%d", &t);
	while(t--)
	{
		num = 0;
		edge.clear();
		scanf("%d %d", &n, &p);
		for(i=0;i<=n;i++)g[i].clear();
		while(p--)
		{
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			a--, b--;
			g[a].push_back(num);
			g[b].push_back(num+1);
			edge.push_back(node(a, b, c, 0));
			edge.push_back(node(b, a, c, 1));
			num+=2;
		}
		spfa(n, 0);
		LL sum = 0;
		for(i=0;i<n;i++)
			sum += dis[i];
		spfa(n, 1);
		for(i=0;i<n;i++)
			sum += dis[i];
		printf("%lld\n", sum);
	}
	return 0;
}

void spfa(int n, int s)
{
	int i;
	for(i=0;i<n;i++)
		dis[i] = INF, vis[i] = 0;
	vis[0] = 1;
	dis[0] = 0;
	queue<int> que;
	que.push(0);
	while(!que.empty())
	{
		int u = que.front();que.pop();
		vis[u] = 0;
		for(int i=0;i<g[u].size();i++)
		{
			node e = edge[g[u][i]];
			if(e.s != s)continue;
			//printf("%d %d %d\n", e.f, e.t, e.p);
			if(dis[e.t] > dis[u] + e.p)
			{
				dis[e.t] = dis[u]+e.p;
				if(!vis[e.t])
				{
					que.push(e.t);
					vis[e.t] = 1;
				}
			}
		}
	}
}
