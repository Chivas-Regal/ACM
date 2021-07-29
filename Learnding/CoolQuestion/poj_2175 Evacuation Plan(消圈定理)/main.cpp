//消圈定理
//给出一种解决方案，为是否存在一种更为优秀的方案
//假设是让求最优方案的话，可以直接跑网络流，但此题会超时
//所以需要从他给的方案，进行优化，因为他给的方案是符合
//网络流规则的，所以可以将网络流的图建为他所给的方案
//即建一个网络流的残余网络，然后看其中是否有负圈，如果
//有则存在更优的方案，没有则当前最优
//PS：网上好像也没什么好多资料，就本题来说，好像就是
//把残余网络建出来，然后从超级汇点T开始跑，找负环 
//题目链接：http://poj.org/problem?id=2175 
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
#define eps 1e-6

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 220;
struct node{
	int x, y, num;
}b[maxn], a[maxn];
struct edge{
	int to, nex, flow, cap, cost;
}eg[maxn*maxn];
int cnt, hd[maxn], c[maxn][maxn], out[maxn];
int ed, preee[maxn], vis[maxn], dis[maxn], tim[maxn];
void init();
int solve(int n, int m);
void add(int f, int t, int cap, int flow, int cost);

int main()
{
	int n, m, i, j;
	init();
	scanf("%d %d", &n, &m);
	for(i=1;i<=n;i++)
		scanf("%d  %d %d", &a[i].x, &a[i].y, &a[i].num);
	for(i=1;i<=m;i++)
		scanf("%d %d %d", &b[i].x, &b[i].y, &b[i].num);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++){
			scanf("%d", &c[i][j]);
			out[j] += c[i][j];
			//求花费 
			int d = abs(a[i].x-b[j].x)+abs(a[i].y-b[j].y)+1;
			add(i, n+j, a[i].num, c[i][j], d);
		}
	//将点向超级汇点连的边建出来 
	for(i=1;i<=m;i++)
		add(i+n, 0, b[i].num, out[i], 0);
	//SPFA找负环 
	int ans = solve(n, m);
	if(ans == -1)
		printf("OPTIMAL\n");
	else{
		printf("SUBOPTIMAL\n");
		memset(vis, 0, sizeof(vis));
		//找出负环上的点 
		while(!vis[ans]){
			vis[ans] = 1;
			ans = preee[ans];
		}
		int ls = ans;
		do{
			int xx = preee[ans];
			if(xx > n && ans<=n)c[ans][xx-n]--;
			if(xx<=n && ans>n)c[xx][ans-n]++;
			ans = xx;
		}while(ans != ls);
		for(i=1;i<=n;i++){
			printf("%d", c[i][1]);
			for(j=2;j<=m;j++)
				printf(" %d", c[i][j]);
			printf("\n");
		}
	}
	return 0;
}

void init()
{
	memset(out, 0, sizeof(out));
	memset(hd, -1, sizeof(hd));
	cnt = 1;
}
//建立边
//因为是残留图的边，所以一条边其正向边流量为flow
//反向边流量就为-flow 
void add(int f, int t, int cap, int flow, int cost)
{
	eg[++cnt].to = t;
	eg[cnt].cost = cost;
	eg[cnt].cap = cap;
	eg[cnt].flow = flow;
	eg[cnt].nex = hd[f];
	hd[f] = cnt;
	eg[++cnt].to = f;
	eg[cnt].cost = -cost;
	eg[cnt].flow = -flow;
	eg[cnt].cap = 0;
	eg[cnt].nex = hd[t];
	hd[t] = cnt;
}
//SPFA找负环 
int solve(int n, int m)
{
	int i, t = n+m+1;
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	memset(tim, 0, sizeof(tim));
	queue<int> que;
	que.push(0);
	dis[0] = 0;
	vis[0] = 1;
	while(!que.empty())
	{
		int u = que.front();que.pop();
		for(i=hd[u];i!=-1;i=eg[i].nex)
		{
			if(eg[i].cap>eg[i].flow && dis[eg[i].to] > dis[u]+eg[i].cost)
			{
				dis[eg[i].to] = dis[u] + eg[i].cost;
				preee[eg[i].to] = u;
				tim[eg[i].to]++;
				if(!vis[eg[i].to]){
					que.push(eg[i].to);
					vis[eg[i].to] = 1;		
				}
				if(tim[eg[i].to] > t)
					return eg[i].to;
			}
		}
		vis[u] = 0;
	}
	return -1;
}
