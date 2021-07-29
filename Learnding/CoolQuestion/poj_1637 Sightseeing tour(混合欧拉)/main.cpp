//混合欧拉
//首先判断图是否连通。然后将无向边任意定向,
//在网络流图中加入该边，流量为1(原点s,汇点t)。 
//求每个点的入度与出度，然后两者相减为奇数，则不是欧拉图
//如果点入度in大于出度out，则加一条i到t，容量为(in-out)/2的边
//如果点入度in小于出度out，则加一条s到i，容量为(out-in)/2的边
//图若满流，则是欧拉图
//欧拉路径(摘自kuangbin)：
//先把图中的无向边随便定向，然后求每个点的D值，
//若有且只有两个点的初始D值为奇数，其余的点初始D值都为偶数，
//则有可能存在欧拉路径（否则不可能存在）。
//进一步，检查这两个初始D值为奇数的点，设为点i和点j，
//若有D[i]>0且D[j]<0，则i作起点j作终点（否则若D[i]与D[j]同号则不存在欧拉路径），
//连边<j, i>，求是否存在欧拉环即可（将求出的欧拉环中删去边<j, i>即可）。这样只需求一次最大流。
//参考博客： https://www.cnblogs.com/kuangbin/p/3537525.html
//题目链接： http://poj.org/problem?id=1637
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
struct edg{
	int f, t;
}p[1020];
struct node
{
	int to, flow, rev;
	node(int a, int b, int c):to(a),flow(b),rev(c){
	}
};
vector<node> g[2020];
int vis[2020], dis[2020], a[220];
void add(int from, int to, int flow);
int dinic(int s, int t);
void bfs(int s, int t);
int dfs(int s, int t, int ans);
int Find(int x);
bool ishui(int n, int m);

int main()
{
	int t, n, m, i, j, ans, num, in[220], out[220];
	scanf("%d", &t);
	while(t--)
	{
		memset(in, 0, sizeof(in));
		memset(out, 0, sizeof(out));
		ans = 1, num = 0;
		scanf("%d %d", &n, &m);
		for(i=0;i<=n+1;i++)g[i].clear();
		for(i=0;i<m;i++)
		{
			int dir;
			scanf("%d %d %d", &p[i].f, &p[i].t, &dir);
			if(!dir)add(p[i].f, p[i].t, 1);
			in[p[i].t]++, out[p[i].f]++;
		}
		//判断图是否连通 
		if(!ishui(n, m))ans = 0;
		for(i=1;i<=n;i++)
		{
			if(abs(in[i]-out[i])&1)ans = 0;
			//建边 
			if(in[i]<out[i])add(0, i, (out[i]-in[i])/2);
			if(in[i]>out[i])add(i, n+1, (in[i]-out[i])/2);
			num += abs(in[i]-out[i])/2;
		}
		//判断满流 
		if(dinic(0, n+1)!=num/2)
			ans = 0;
		if(ans)printf("possible\n");
		else printf("impossible\n");
	}
	return 0;
}

bool ishui(int n, int m)
{
	int i, j, num = 0;
	for(i=1;i<=n;i++)
		a[i] = i;
	for(i=0;i<m;i++)
	{
		int x = Find(p[i].f), y = Find(p[i].t);
		if(x!=y){
			a[x] = y;
			num++;
		}
		if(num == n-1)return true;
	}
	return false;
}

int Find(int x)
{
	return a[x]=(a[x]==x?x:Find(a[x]));
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
