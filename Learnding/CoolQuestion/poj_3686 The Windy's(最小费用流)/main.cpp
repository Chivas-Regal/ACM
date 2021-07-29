//最小费用流
//将每个工作室拆为n个点，因为一个工作室最多可以进行n项任务
//然后将每个任务向工作室的各个点连边，流量为1，费用为k*a[i][j]
//因为一个任务在工作室的费用为a1+a2+...+ak，将费用分解一下
//等于a1加了k次 
//题目链接：http://poj.org/problem?id=3686 
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
const int maxn = 5000;
const int mod = 1000000007;
struct node
{
	int to, nex, cap, flow, cost;
}nex[900100];
int cnt, ed, dis[maxn], vis[maxn], hd[maxn], pre[maxn];
int a[64][64];
void init();
void add(int from, int to, int cap, int cost);
int minCostFlow(int s, int t, int &cost);

int main()
{
	int t, n, m, i, j;
	scanf("%d", &t);
	while(t--)
	{
		init();
		scanf("%d %d", &n, &m);
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				scanf("%d", &a[i][j]);
		ed = n*m + n+ 1;
		for(i=1;i<=n;i++){
			add(0, i, 1, 0);
			for(j=1;j<=m;j++){
				for(int k=1;k<=n;k++)
				//放入第j个工作室的第k步进行，花费为k*a[i][j] 
					add(i, n+(j-1)*n+k, 1, k*a[i][j]);
			}
		}
		for(i=1;i<=m;i++)
			for(j=1;j<=n;j++)
				add(n+(i-1)*n+j, ed, 1, 0);
		int ans = 0;
		int t = minCostFlow(0, ed, ans);
		printf("%.6f\n", ans*1.0/n);
	}
	return 0;
}

void init()
{
	memset(hd, -1, sizeof(hd));
	cnt = -1;
}

void add(int from, int to, int cap, int cost)
{
	nex[++cnt].to = to;
	nex[cnt].cap = cap;
	nex[cnt].flow = 0;
	nex[cnt].cost = cost;
	nex[cnt].nex = hd[from];
	hd[from] = cnt;
	nex[++cnt].to = from;
	nex[cnt].cap = 0;
	nex[cnt].flow = 0;
	nex[cnt].cost = -cost;
	nex[cnt].nex = hd[to];
	hd[to] = cnt;
}

bool spfa(int s, int t)
{
	for(int i=0;i<=t;i++){
		dis[i] = INF, vis[i] = 0, pre[i] = -1;
	}
	queue<int> que;
	que.push(s);
	dis[s] = 0, vis[s] = 1;
	while(!que.empty())
	{
		int u =que.front();que.pop();
		vis[u] = 0;
		for(int i=hd[u];i!= -1; i=nex[i].nex){
			int v = nex[i].to;
			if(nex[i].cap > nex[i].flow && dis[v] > dis[u]+nex[i].cost){
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
//cost：最小费用，flow：最大流 
int minCostFlow(int s, int t, int &cost)
{
	int flow = 0;
	cost = 0;
	while(spfa(s, t)){
		int mi = INF;
		for(int i=pre[t];i!=-1;i=pre[nex[i^1].to]){
			if(mi > nex[i].cap - nex[i].flow)
				mi = nex[i].cap - nex[i].flow;
		}
		for(int i=pre[t];i!=-1;i=pre[nex[i^1].to]){
			nex[i].flow += mi;
			nex[i^1].flow -= mi;
			cost += nex[i].cost * mi;
		}
		flow += mi;
	}
	return flow;
}
