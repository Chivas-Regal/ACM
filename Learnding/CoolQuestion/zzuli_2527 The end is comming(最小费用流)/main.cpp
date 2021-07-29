//最小费用流+拆点 
//关键在于解决下面的问题：每种元素只有在从初始位置
//流出时才计算费用，而且使用后开可以0费用给其他机关使用 
//设超级源点S与超级汇点T，将每个点拆为两个点，一个用于
//接收流量，一个用于流出流量，构图如下： 
//连接S点到接收流量的点，容量为机关需要元素数量，费用为1
//连接S点到流出流量的点，容量为机关需要元素数量，费用为0
//连接接收流量的点到T点，容量为机关需要元素数量，费用为0
//如果元素在i使用完后能在j启动前到达j，则连接i的流出
//点到j的接收点，容量为INF，费用为0
//以上构图可保证最大流为所有需要元素之和，求最小费用
//如果可以从其他点接受流量，则从其他点接收(相当于i用完后
//将元素传递给j)，如果不能或不够，则在从S补发需要的元素
//此时最小费用即为最少需要的元素
//PS：比赛的时候不知道为什么，可能是没看样例和提示吧，
//没注意到k只能作用于一定不能到达的点，然后就。。。。 
//题目连接：http://202.196.1.136/problem.php?id=2527 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1010;
const int mod = 1e9;
struct node
{
	int to, cap, cost, rev;
	node(int a, int b, int c, int d):to(a),cap(b),cost(c),rev(d){
	}
};
int n, dis[maxn], prevv[maxn], preve[maxn];
int x[maxn], y[maxn], bg[maxn], ed[maxn], na[maxn], a[maxn][8];
vector<node> g[8][3*maxn];
void add(int i, int from, int to, int cost, int flow);
int min_cost_flow(int ks, int s, int t, int f);

int main()
{
	int T, n, m, k, i, j;
	scanf("%d %d %d", &n, &m, &k);
	T = 2*n+1;
	scanf("%d %d", &x[0], &y[0]);
	memset(na, 0, sizeof(na));
	ed[0] = 0;
	for(i=1;i<n;i++){
		scanf("%d %d %d %d", &x[i], &y[i], &bg[i], &ed[i]);
		ed[i] += bg[i];
		for(j=0;j<m;j++)
			scanf("%d", &a[i][j]);
	}
	int sum = 0;
	for(i=1;i<n;i++){
		int d = abs(x[i]-x[0])+abs(y[i]-y[0]);
		if(d > bg[i]){
			sum++;
			na[i] = 1;
		}
	}
	if(sum > k)
		printf("THE END IS COMING!!!!!\n");
	else{
		for(i=1;i<n;i++)
			for(j=1;j<n;j++){
				if(i==j || na[i] || na[j])continue;
				int d = abs(x[i]-x[j])+abs(y[i]-y[j]);
				if(d+ed[i]<=bg[j]){
					for(k=0;k<m;k++)
					add(k, 2*i+1, 2*j, 0, INF);
				}
			}
		for(i=1;i<n;i++){
			for(j=0;j<m;j++)
			if(!na[i]){
				add(j, 2*i, T, 0, a[i][j]);
				add(j, 0, 2*i+1, 0, a[i][j]);
				add(j, 0, 2*i, 1, a[i][j]);
			}
		}
		int ans = 0;
		for(i=0;i<m;i++)
			ans += min_cost_flow(i, 0, T, 1000000);
		printf("%d\n", ans);
	}
	return 0;
}


void add(int i, int from, int to, int cost, int flow)
{
	g[i][from].push_back(node(to, flow, cost, g[i][to].size()));
	g[i][to].push_back(node(from, 0, -cost, g[i][from].size()-1));
}

int min_cost_flow(int ks, int s, int t, int f)
{
	int res = 0;
	//memset(h, 0, sizeof(h));
	while(f>0)
	{
		priority_queue<P, vector<P>, greater<P> > que;
		fill(dis, dis+t+1, INF);
		dis[s] = 0;
		que.push(P(0, s));
		while(!que.empty())
		{
			P p = que.top();que.pop();
			int v = p.second;
			if(dis[v]<p.first)continue;
			int ss = g[ks][v].size();
			for(int i=0;i<ss;i++)
			{
				node &e = g[ks][v][i];
				if(e.cap>0 && dis[e.to]>dis[v]+e.cost)
				{
					dis[e.to] = dis[v]+e.cost;
					prevv[e.to] = v;
					preve[e.to] = i;
					que.push(P(dis[e.to], e.to));
				}
			}
		 }
		if(dis[t] == INF)return res;
		//for(int i=1;i<=n;i++)h[i] += dis[i];
		int d = f;
		for(int v=t;v!=s;v=prevv[v])
		{
			d = min(d, g[ks][prevv[v]][preve[v]].cap);
		}
		f -= d;
		res += d * dis[t];
		for(int v=t;v!=s; v=prevv[v])
		{
			node &e = g[ks][prevv[v]][preve[v]];
			e.cap -= d;
			g[ks][v][e.rev].cap += d;
		}
	}
	return res;
}

