//最小费用流，区间k覆盖
//有n个任务，每个任务需要使用[l,r)内的所有时间，完成任务可以得到 
//p积分，总共k天，求最大可以获得的积分
//首先将所有时间点离散化，然后对于对于每个时间点，建i->i+1，流量为k
//cost为0的边，对于每个任务，建起始时间到终止时间区间，流量为1，费用
//为-p的边(因为是求最大费用，将流量取反，求最小费用流后，结果取反就是)
//最大费用
//题目链接：http://poj.org/problem?id=3762 
#include<cstdio>
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
#define dbg(x) printf("debug:%d\n", x);
#define INF 0x3f3f3f3f
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 6000;
const int mod = 1000000007;
struct node{
	int nex, to, cap, flow, cost;
}nex[2000000];
struct pot{
	int a, id, up;
}b[maxn];
int ed, cnt, hd[maxn], dis[maxn], pre[maxn], vis[maxn];
int bg[maxn], ov[maxn], p[maxn];
void init();
bool spfa(int s, int t);
int minCostFlow(int s, int t, int &cost);
void add(int from, int to, int flow ,int cost);
int Find(int l, int r, int x, int a[]);
bool cmp(pot a, pot b);

int main()
{
	int n, k, i, l;
	while(~scanf("%d %d", &n, &k))
	{
		l = 0;
		init();
		ed = n+n+1;
		for(i=1;i<=n;i++){
			int h1, h2, m1, m2, d1, d2;
			scanf("%d:%d:%d %d:%d:%d %d", &h1, &m1, &d1, &h2, &m2, &d2, &p[i]);
			bg[i] = h1*3600+m1*60+d1, ov[i] = h2*3600+m2*60+d2;
			b[l].a = bg[i], b[l].id = i, b[l++].up = 0;
			b[l].a = ov[i];b[l].id = i, b[l++].up = 1;
		}
		//离散化，求出每个节点离散化的编号 
		sort(b, b+l, cmp);
		int r = 0, af = -1;
		for(i=0;i<l;i++){
			if(b[i].a != af){
				af = b[i].a;r++;
			}
			if(b[i].up == 0)
				bg[b[i].id] = r;
			else
				ov[b[i].id] = r;
		}
		//建i到i-1，容量为k，费用为0的边 
		for(i=1;i<=r;i++)
			add(i-1, i, k, 0);
		add(r, ed, k, 0);
		//对于每个时间，在起始点和终止点建边 
		for(i=1;i<=n;i++)
			add(bg[i], ov[i], 1, -p[i]);			
		int ans = 0;
		minCostFlow(0, ed, ans);
		printf("%d\n", -ans);
	}	
	return 0;
}

void add(int from, int to, int flow ,int cost)
{
	nex[cnt].nex = hd[from];;
	nex[cnt].to = to;
	nex[cnt].cap = flow;
	nex[cnt].flow = 0;
	nex[cnt].cost = cost;
	hd[from] = cnt++;
	nex[cnt].nex = hd[to];
	nex[cnt].to = from;
	nex[cnt].cap = 0;
	nex[cnt].flow = 0;
	nex[cnt].cost = -cost;
	hd[to] = cnt++;
}

void init()
{
	cnt = 0;
	memset(hd, -1, sizeof(hd));
}

bool spfa(int s, int t)
{
	for(register int i=0;i<=t;i++)
		dis[i] = INF;
	memset(pre, -1, sizeof(pre));
	memset(vis, false, sizeof(vis));
	queue<int> que;
	que.push(s);
	dis[s] = 0, vis[s] = 1;
	while(!que.empty())
	{
		int u =que.front();que.pop();
		vis[u] = 0;
		for(register int i=hd[u];i!=-1;i=nex[i].nex)
		{
			int v = nex[i].to;
			if(nex[i].cap > nex[i].flow && dis[v] > dis[u] + nex[i].cost)
			{
				dis[v] = dis[u] + nex[i].cost;
				pre[v] = i;
				if(!vis[v]){
					vis[v] = 1;
					que.push(v);
				}
			}
		}
	}
	if(dis[t] == INF)return false;
	else return true;
}

int minCostFlow(int s, int t, int &cost)
{
	int flow = 0;
	cost = 0;
	while(spfa(s, t))
	{
		int d = INF; 
		for(register int i=pre[t];i!=-1;i=pre[nex[i^1].to])
		if(d > nex[i].cap - nex[i].flow)
			 d = nex[i].cap-nex[i].flow;
		for(register int i=pre[t];i!=-1;i=pre[nex[i^1].to]){
			nex[i].flow += d;
			nex[i^1].flow -= d;
			cost += d * nex[i].cost;
		}
		flow += d;
	}
	return flow;
}

bool cmp(pot a, pot b)
{
	return a.a < b.a;
}
