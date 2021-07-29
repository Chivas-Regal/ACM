/*****************************************************
最大流
有一个序列，求序列的最长不下降子序列长度len,同时求序列中能取出多少个长度为len的不下降子序列。a1,an可以多次取的情况下可以取多少。

思路：求最长不下降子序列显然可以通过动态规划求解。求出长度len后，可以考虑对每个点拆为两个点i,i'，连接一条i->i'容量为1的边。对于dp[i]=1的点，连源点S到i，容量为1，对于dp[i]=len的点，连i'到汇点T，容量为1。
对于每个点i，如果存在j<i && a[j]<=a[i] && dp[j]+1 == dp[i]，则连j'->i容量为1的边。
然后求最大流即可。对于a1和an可以多次取，只需要在连接S到1，1到1’,n到n'，如果dp[n]==len，同时在连接n'到T即可，容量都为INF。

题目链接：https://www.luogu.com.cn/problem/P2766
**********************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 3020;
const int mod = 9901;
struct edge{
	int to, nex, cap, flow;
	edge(){}
	edge(int a, int b, int c, int d):to(a),nex(b),cap(c),flow(d){}
}eg[maxn*maxn];
int a[maxn], dp[maxn];
int tot, hd[maxn], dis[maxn], vis[maxn];
void init();
int dinic(int s, int t);
void bfs(int s, int t);
int dfs(int s, int t, int ans);
void add(int fr, int to, int cap);

int main()
{
	int n, m, i, j, k, s,ed, ans1, ans2;
	s = 1;
	scanf("%d", &n);
	for(i=1;i<=n;i++)
		scanf("%d", &a[i]);
	//求最长不下降子序列的长度
	for(i=1;i<=n;i++)
	{
		dp[i] = 1;
		for(j=1;j<i;j++)
		if(a[j] <= a[i])
			dp[i] = max(dp[i],dp[j]+1);
		s = max(s, dp[i]);
	}
	//建图
	ed = n+n+2;
	init();
	for(i=1;i<=n;i++)
	{
		add(i, i+n, 1);
		if(dp[i] == 1)add(0, i, 1);
		if(dp[i] == s)add(i+n, ed, 1);
		for(j=1;j<i;j++)
			if(a[j] <= a[i] && dp[j]+1 == dp[i])
				add(j+n, i, 1);
	}
	ans1 = dinic(0, ed);
	//a1和an能多次取
	add(0, 1, INF), add(1, 1+n, INF);
	if(dp[n] == s)add(n, n+n, INF), add(n+n, ed, INF);
	ans2 = ans1+dinic(0, ed);
	printf("%d\n%d\n%d\n", s, ans1, ans2);
	return 0;
}

void init()
{
	tot = 1;
	memset(hd, -1, sizeof(hd));
}

void add(int fr, int to, int cap)
{
	eg[++tot].to = to;
	eg[tot].cap = cap;
	eg[tot].flow = 0;
	eg[tot].nex= hd[fr];
	hd[fr] = tot;
	eg[++tot].to = fr;
	eg[tot].cap = eg[tot].flow = 0;
	eg[tot].nex = hd[to];
	hd[to] = tot;
}

int dinic(int s, int t)
{
	int res = 0;
	while(1)
	{
		bfs(s, t);
		if(dis[t]<0)return res;
		int d;
		for(int i=0;i<=t;i++)vis[i]=hd[i];
		while((d=dfs(s, t, INF))>0)
			res += d;
	}
}

void bfs(int s, int t)
{
	memset(dis, -1, sizeof(dis));
	dis[s] = 0;
	queue<int> que;
	que.push(s);
	while(!que.empty())
	{
		int u = que.front();que.pop();
		for(int i=hd[u];i!=-1;i=eg[i].nex)
		{
			if(eg[i].cap > eg[i].flow && dis[eg[i].to] == -1)
			{
				dis[eg[i].to]  = dis[u] + 1;
				que.push(eg[i].to);
			}
		}
	}
}

int dfs(int s, int t, int ans)
{
	if(s == t)return ans;
	for(int &i=vis[s];i!=-1;i=eg[i].nex)
	{
		edge e = eg[i];
		if(e.cap > e.flow && dis[e.to] == dis[s]+1)
		{
			int d = dfs(e.to, t, min(ans, e.cap-e.flow));
			if(d > 0)
			{
				eg[i].flow += d;
				eg[i^1].flow -= d;
				return d;
			}
		}
	}
	return 0;
}