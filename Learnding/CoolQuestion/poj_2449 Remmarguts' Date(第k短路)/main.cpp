//A*算法
//求s到t的第k短路
//先利用反向边求出t到其他点的最短路
//然后用Astar算法，求出到各点的路径长度
//然后估计其到t的距离，按照此为逐渐排序
//题目链接： http://poj.org/problem?id=2449
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1020;
int dis[maxn], vis[maxn];
//node:Astar所需结构体，edg：边 
struct node{
	int u;
	LL cost;
	//优先取出估计值较小的路径 
	bool operator <(const node b)const{
		return cost+dis[u]>b.cost+dis[b.u];
	}
	node(int a, int b):u(a),cost(b){
	}
};
struct edg{
	int to, dis;
	edg(int a, int b):to(a), dis(b){
	}
};
vector<edg> rg[maxn], pg[maxn];
void dijsktra(int s, int n);
int k_road(int k, int s, int t);

int main()
{
	int n, m, s, t, k, i, j;
	while(~scanf("%d %d", &n, &m))
	{
		for(i=0;i<=n;i++){
			rg[i].clear();
			pg[i].clear();
		}
		while(m--)
		{
			int fr, to, cs;
			scanf("%d %d %d", &fr, &to, &cs);
			pg[fr].push_back(edg(to, cs));
			rg[to].push_back(edg(fr, cs));
		}
		scanf("%d %d %d", &s, &t, &k);
		dijsktra(t, n);
		printf("%d\n", k_road(k, s, t));
	}
	
	return 0;
}
//求t到各点的最短路径 
void dijsktra(int s, int n)
{
	fill(dis, dis+n+1, INF);
	dis[s] = 0;
	priority_queue<P, vector<P>, greater<P> > que;
	que.push(P(0, s));
	while(!que.empty())
	{
		P p = que.top();que.pop();
		if(p.first > dis[p.second])continue;
		for(int i=0;i<rg[p.second].size();i++){
			edg e = rg[p.second][i];
			int ss = p.first+e.dis;
			if( ss < dis[e.to]){
				dis[e.to] = ss;
				que.push(P(dis[e.to], e.to));
			}
		}
	}
}
//Astar算法，当前结点u,已走路径为cost,
//继续往一下路径走，如果到达t，则为一条路径 
int k_road(int k, int s, int t)
{
	priority_queue<node> que;
	que.push(node(s, 0));
	//如果s==t，则实际需求的是第K+1条路径,因为初始
	//就在t算一条路径了，必须出去走几步才能算一条路径 
	if(s == t)k++;
	while(!que.empty())
	{
		node p = que.top(); que.pop();
		if(p.u == t){
			k--;
			if(!k)return p.cost;
		}
		for(int i=0;i<pg[p.u].size();i++){
			que.push(node(pg[p.u][i].to, p.cost+pg[p.u][i].dis));
		}
	}
	return -1;
}
