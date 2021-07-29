//网络流：dinic算法，入门
//就是有几个发电站，几个中转站，几个用户，问最多
//能传到用户家里多少点
//题解：设个超级源点，超级汇点，因为发电站、用户
//本身都有流量限制，在读取时，加一条从超级点到发电站或用户的边
//即可转化为经典的网络流模型问题，此题对效率要求
//较高，使用Ford_Fulkerson算法会超时，所以需要使用dinic
// http://poj.org/problem?id=1459
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
int n, a[120][120], dist[120], vis[120];
int dinic_dfs(int s, int t, int ans);
int dinic();
void dinic_bfs();

int main()
{
	int l1, l2, m, i, j;
	while(~scanf(" %d %d %d %d", &n, &l1, &l2, &m))
	{
		int fl, fr, to;
		memset(a, 0, sizeof(a));
		for(i=0;i<m;i++)
		{
			scanf(" ( %d, %d ) %d", &fr, &to, &fl);
			a[fr+1][to+1] = fl;
		}
		for(i=0;i<l1;i++)
		{
			scanf(" ( %d ) %d", &fr, &fl);
			a[0][fr+1] = fl;
		}
		for(i=0;i<l2;i++)
		{
			scanf(" ( %d ) %d", &to, &fl);
			a[to+1][n+1] = fl;
		}
		/*for(i=0;i<=n+1;i++)
		{
			for(j=0;j<=n+1;j++)
				printf("%d ", a[i][j]);
			printf("\n");
		}*/
		int ans = dinic();
		printf("%d\n", ans);
	}
	return 0;
}

int dinic()
{
	int res = 0;
	for(;;)
	{
		dinic_bfs();
		if(dist[n+1]<0)return res;
		memset(vis, 0, sizeof(vis));
		int d;
		//printf("res:  %d %d\n", res, d);
		while((d=dinic_dfs(0, n+1, 100000))>0)
		res += d;
	}
}

//bfs将每个节点标记层数。 
void dinic_bfs()
{
	memset(dist, -1, sizeof(dist));
	queue<int> que;
	dist[0] = 0;
	que.push(0);
	while(!que.empty())
	{
		int u = que.front();
		que.pop();
		for(int i=1;i<=n+1;i++)
		{
			if(a[u][i]>0 && dist[i]<0)
			{
				dist[i] = dist[u]+1;
				que.push(i);
			}
		}
	}
}

int dinic_dfs(int s, int t, int ans)
{
	//printf("%d %d %d\n", s, t, ans);
	if(s == t)return ans;
	for(int &i=vis[s];i<=n+1;i++)
	{ 
		if(dist[s]<dist[i] && a[s][i] > 0){
			int d = dinic_dfs(i, t, min(ans, a[s][i]));
			if(d>0){
				a[s][i] -= d;
				a[i][s] += d;
				return d;
			}
		}
	}
	return 0;
}
