/******************************* 
最大权闭合图
有m个实验,n个仪器，每个实验需要一定的仪器，每个实验
能获得代价ai,购买一个仪器需要代价bi(可在多个实验使用),
求能获得的最大代价
题解：最大权闭合图模板题，建图可以考虑设置源点s和汇点t
对于每个实验i连s到i容量为ai的边，对于每个仪器j，
连j到t容量为bi的边，对于每个实验需要用到仪器，连接实验
到仪器容量为INF的边，跑最大流，然后拿ai的和减去最大流
就是能获得的最大代价。
对于上面的建图，每个实验可以获得的利益为ai，这个实验会
买仪器的代价会形成增广路，所以用实验利益总和减去最大流
即是可以获得的最多利益。对于输出方案，对残留网络从源点
开始进行bfs，能到达的点即是需要的点(dinic最后一遍bfs的数组
可以直接使用)。 
题目链接：https://www.luogu.org/problem/P2762
***********************************/ 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 150;
const int mod = 998244353;
struct node{
	int to, cap, flow, nex;
}eg[maxn*maxn];
int cnt, hd[maxn], vis[maxn], dis[maxn];
char str[10010];
vector<int> g[maxn];
void init();
void bfs(int s, int t);
int dinic(int s, int t);
int dfs(int s, int t, int ans);
void add(int from, int to, int cap);

int main()
{
	int n, m, i, j, sum = 0, ed;
	init();
	scanf("%d %d", &m, &n);
	ed = n+m+1;
	for(i=1;i<=m;i++)
	{
		scanf("%d", &j);
		sum += j;
		add(0, i, j);
		cin.getline(str, 10000);
		int ulen=0,tool;
		while (sscanf(str+ulen,"%d",&tool)==1)
		{
			add(i, m+tool, INF);
			if (tool==0) 
				ulen++;
			else {
				while (tool) {
					tool/=10;
					ulen++;
				}
			}
			ulen++;
		}
	}
	for(i=1;i<=n;i++)
	{
		scanf("%d", &j);
		add(m+i, ed, j);
	}
	int ans = dinic(0, ed);
	//残留网络中从s能到达的点即为需要的点 
	for(i=1;i<=m;i++)
	if(dis[i]!=-1)printf("%d ", i);
	printf("\n");
	for(i=1;i<=n;i++)
	if(dis[i+m]!=-1)printf("%d ", i);
	printf("\n");
	printf("%d\n", sum-ans);
	return 0;
}

void init()
{
	memset(hd, -1, sizeof(hd));
	cnt = 1;
}

void add(int from, int to, int cap)
{
	eg[++cnt].to = to;
	eg[cnt].cap = cap;
	eg[cnt].flow = 0;
	eg[cnt].nex = hd[from];
	hd[from] = cnt;
	eg[++cnt].to = from;
	eg[cnt].cap = eg[cnt].flow = 0;
	eg[cnt].nex = hd[to];
	hd[to] = cnt;
}

int dinic(int s, int t)
{
	int flow = 0;
	while(1)
	{
		bfs(s, t);
		if(dis[t] == -1)return flow;
		int d;
		for(int i=0;i<=t;i++)
			vis[i] = hd[i];
		while((d=dfs(s, t, INF))>0)
			flow += d; 
	}
}

void bfs(int s, int t)
{
	queue<int> que;
	memset(dis, -1, sizeof(dis)); 
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
				eg[i^1].flow -=d;
				return d;
			}
		}
	}
	return 0;
}
