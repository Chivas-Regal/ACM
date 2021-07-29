/****************************************************
最小费用流
有n*n的方格网络，一辆车初始在(1,1),目标为(n,n)，车的油箱大小为k，
初始油箱满的，每次可以往上下左右走一步，耗油1，部分格点上有加油站，
路过必须加油，代价A，同时如果汽车往上走或往左走，代价为B，可以在某些
格点增设加油站，需要代价C，求到达目标点的最小花费。

思路：下面提供两个建图思路(第二种思路较为方便，且复杂度较低)
solve1：因为有油箱的限制，到每个位置的油箱剩余的油量难以维护，
	因为k<=10，所以考虑将点的意义定义为处于当前位置，且油箱是满的。
	对于在当前位置i加满油能到达的所有位置(中途不加油)，对每个位置
	j，连接i到j，容量为1，费用为 i走到j，中途不加油，且在j处加满油
	的最小费用 的边。对于连边操作，可以BFS求出每条边的费用。
	然后连接(n,n)到汇点t，容量为1，费用为0。最后跑(1,1)到t点的最小
	费用流，将结果ans减去(A+C)即可，因为上面的建图在最后一个点(n,n)
	也会建加油站和加满油，会产生(A+C)的费用，实际上并不需要。
	这种建图当k=10时，每个点可能会找到200多个点，所以建图差不多会有
	100*100*221条边，复杂度较高。(因为这个图很多边实际上根本就没有必要加)

solve2：这个建图是参考大佬的思路。对于油箱剩余油量的信息的维护，采用分层
	建图的方式维护。将图分为k+1层，每层n*n个点，对于第1、2...k+1层，
	代表剩余油量为k、k-1...0。对于当前位置i(没有加油站)，考虑下一步走到j，
	如果油量有剩余，则连接当前层的i到下一层的j，容量为1，费用为走这
	步需要的费用，而对于油量为0，则费用需要额外加上建加油站和加满油的
	费用；对于当前位置i(有加油站)，因为强制消费，所以只能连接当前层
	到剩余油量为k-1那层的j(在当前点加满油，走一步，剩余油量为k-1)
	，容量为1，费用为此步的费用加上加满油的费用。这样建图差不多会有
	100*100*10*4条边，是上面那种建图的1/5，实际上对于最大的数据点，
	上面的建图跑了500+ms,这种建图跑了100+ms。
	
题目链接：https://www.luogu.org/problem/P4009
*****************************************************/
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
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1000010;
const int mod = 1e9+7;
struct node{
	int to, nex, flow, cap, cost;
}eg[60*maxn];
int tot, ed, pre[maxn], vis[maxn], hd[maxn], dis[maxn];
int n, A, B, C, a[120][120], id[120][120], b[120][120], c[120][120];
int dx[4]={-1,0,1,0}, dy[4]={0,-1,0,1};
void init();
bool spfa(int s, int t);
void add(int f, int t, int cost, int cap);
void bfs(int k, int x, int y);
int min_cost_flow(int s, int t, LL &cost);
LL solve1(int k);
LL solve2(int k);

int main()
{
	init();
	int k, i, j, num = 0;
	scanf("%d %d %d %d %d", &n, &k, &A, &B, &C);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++){
			scanf("%d", &a[i][j]);
			id[i][j] = ++num;
			b[i][j] = -1, c[i][j] = INF;
		}
	LL ans = solve2(k);
	printf("%lld\n", ans);
	return 0;
}
//分层建图
LL solve2(int k)
{
	int i, j, sp, ce = n*n;
	ed = k*ce+ce+3;
	for(i=0;i<=k;i++)
		add(i*ce+id[n][n], ed-1, 0, 1);
	add(ed-1, ed, 0, 1);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			for(int z=0;z<4;z++)
			{
				if(z < 2)sp = B;
				else sp = 0;
				int nx = i+dx[z], ny = j+dy[z];
				if(nx>=1 && nx<=n && ny>=1 && ny<=n)
				{
					if(a[i][j] == 1)
					{
						//如果当前点是加油站，则向第2层(代表剩余油量为k-1)连边
						sp += A;
						for(int y=0;y<=k;y++)
							add(id[i][j]+y*ce, id[nx][ny]+ce, sp, 1);
					}
					else
					{
						//如果当前不是加油站且有油，则向下一层的点连边
						for(int y=0;y<k;y++)
							add(id[i][j]+y*ce, id[nx][ny]+y*ce+ce, sp, 1);
						//没油，则向第2层连边
						add(id[i][j]+k*ce, id[nx][ny]+ce, sp+C+A, 1);
					}
				}
			}
	LL ans;
	min_cost_flow(1, ed, ans);
	return ans;
}
//第一种建图方式
LL solve1(int k)
{
	int i, j;
	ed = n*n+1;
	add(n*n, ed, 0, 1);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			bfs(k, i, j);
	LL ans;
	min_cost_flow(1, ed, ans);
	return ans-A-C;
}
//求(x,y)走k步能到达的位置
void bfs(int k, int x, int y)
{
	int i, j, z;
	queue<P> que;
	que.push(P(x, y));
	b[x][y] = c[x][y] = 0;
	while(!que.empty())
	{
		P p = que.front();que.pop();
		if(b[p.first][p.second] >= k)continue;
		for(i=0;i<4;i++){
			int nx = p.first+dx[i], ny = p.second+dy[i];
			if(nx >= 1&& nx<=n && ny>=1 && ny<=n)
			{
				int sp = c[p.first][p.second];
				if(i < 2)sp += B;
				if(a[nx][ny] == 1)sp += A;
				if(b[nx][ny] == -1 || c[nx][ny] > sp)
				{
					b[nx][ny] = b[p.first][p.second]+1;
					c[nx][ny] = sp;
					if(a[nx][ny]!=1) que.push(P(nx,ny));
				}
			}
		}
	}
	for(i=-k;i<=k;i++)
		for(j=-k;j<=k;j++)
		{
			int nx = x+i, ny = y+j;
			if(abs(i)+abs(j)<=k && nx>=1 && nx<=n && ny>=1 && ny<=n)
			{
				if(a[nx][ny] != 1)c[nx][ny] += C+A;
				add(id[x][y], id[nx][ny], c[nx][ny], 10);
				b[nx][ny] = -1;
				c[nx][ny] = INF;
			}
		}
}

void init()
{
	memset(hd, -1, sizeof(hd));
	tot = 1;
}

void add(int f, int t, int cost, int cap)
{
	eg[++tot].to = t;
	eg[tot].cost = cost;
	eg[tot].cap = cap;
	eg[tot].nex = hd[f];
	eg[tot].flow = 0;
	hd[f] = tot;
	eg[++tot].to = f;
	eg[tot].cost = -cost;
	eg[tot].cap = 0;
	eg[tot].nex = hd[t];
	eg[tot].flow = 0;
	hd[t] = tot;
}

bool spfa(int s, int t)
{
	for(int i=0;i<=t;i++)
		dis[i] = INF, vis[i] = 0, pre[i] = -1;
	queue<int> que;
	que.push(s);
	dis[s] = 0, vis[s] = 1;
	while(!que.empty())
	{
		int u = que.front();que.pop();
		vis[u] = 0;
		for(int i=hd[u];i!=-1;i=eg[i].nex)
		{
			int v = eg[i].to;
			if(eg[i].cap > eg[i].flow && dis[v]>dis[u]+eg[i].cost)
			{
				dis[v] = dis[u] + eg[i].cost;
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
//返回最大流，cost：最小费用 
int min_cost_flow(int s, int t, LL &cost)
{
	int flow = 0;
	cost = 0;
	while(spfa(s, t))
	{
		int mi = INF;
		for(int i=pre[t];i!=-1;i=pre[eg[i^1].to])
		{
			if(mi > eg[i].cap-eg[i].flow)
				mi = eg[i].cap - eg[i].flow;
		}
		for(int i=pre[t];i!=-1;i=pre[eg[i^1].to])
		{
			eg[i].flow += mi;
			eg[i^1].flow -= mi;
			cost += eg[i].cost * mi; 
		}
		flow += mi;
	}
	return flow;
}
