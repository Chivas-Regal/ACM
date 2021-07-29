//最小割
//很典型的二式取一问题
//对于一个物品在A、B中又不同的权值
//同时特定物品组合在一个A或B内，有特定的值
//求最大的权值
//首先可以联想到最小割，建立基本的图，然后对于每个特定
//的组合，另设两点x和x'，然后连接0到x，流量为c1，连接x'
//到汇点，然后对于组内的元素ai连接x到ai容量为INF，ai到
//x'容量为INF的边，跑最大流，然后用总的权值和减去最小割
//就是结果
//题目链接：https://www.luogu.org/problem/P1361 
#include<clstdio>
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
#define eps 1e-6

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 5020;
const int mod = 1000000007;
struct node{
	int to, cap, flow, nex;
}eg[2020*2020];
int cnt, pmax, hd[maxn], dis[maxn], vis[maxn];
int a[maxn], b[maxn], c[maxn];
void init();
void add(int f, int t, int cap);
LL dinic(int s, int t);
void bfs(int s, int t);
int dfs(int s, int t, int ans);

int main()
{
	int n, m, i, j, ed, up1, up2, num;
	LL ans = 0;
	init();
	scanf("%d", &n);
	ed = n+1;
	num = ed+1;
	for(i=1;i<=n;i++){
		scanf("%d", &a[i]);
		ans += a[i];
		add(0, i, a[i]);
	}
	for(i=1;i<=n;i++){
		scanf("%d", &b[i]);
		ans += b[i];
		add(i, ed, b[i]);
	}
	scanf("%d", &m);
	while(m--)
	{
		int k, c1, c2;
		scanf("%d %d %d", &k, &c1, &c2);
		//设点x和x' 
		up1 = num+1, up2 = num+2;
		num+=2;
		//连接0->x,x'-ed，容量都为INF 
		add(0, up1, c1);
		add(up2, ed, c2);
		ans += c1+c2;
		for(i=1;i<=k;i++)
		{
			scanf("%d", &c[i]);
			add(up1, c[i], INF);
			add(c[i], up2, INF);
		}
	}
	pmax = num; 
	LL res = dinic(0, ed);
	printf("%lld\n", ans-res);
	return 0;
}

void init()
{
	memset(hd, -1, sizeof(hd));
	cnt = 1;
}

void add(int f, int t, int cap)
{
	eg[++cnt].to = t;
	eg[cnt].cap = cap;
	eg[cnt].flow = 0;
	eg[cnt].nex = hd[f];
	hd[f] = cnt;
	eg[++cnt].to = f;
	eg[cnt].cap = 0;
	eg[cnt].flow = 0;
	eg[cnt].nex = hd[t];
	hd[t] = cnt;
}

LL dinic(int s, int t)
{
	LL res = 0;
	while(1)
	{
		bfs(s, t);
		if(dis[t] < 0)return res;
		int d;
		for(int i=0;i<=pmax;i++)
			vis[i] = hd[i];
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
		int u = que.front();que.pop();
		for(int i=hd[u];i!=-1;i=eg[i].nex)
		{
			node e = eg[i];
			if(e.cap > e.flow && dis[e.to] == -1)
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
	for(int &i=vis[s];i!=-1;i=eg[i].nex)
	{
		if(eg[i].cap > eg[i].flow && dis[eg[i].to] == dis[s]+1)
		{
			int d = dfs(eg[i].to, t, min(ans, eg[i].cap-eg[i].flow));
			if(d>0)
			{
				eg[i].flow += d;
				eg[i^1].flow -= d;
				return d;
			}
		}
	}
	return 0;
}
