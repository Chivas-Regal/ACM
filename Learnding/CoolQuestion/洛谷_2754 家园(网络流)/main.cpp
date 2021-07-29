/*********************************************************
网络流
有n个空间站和地球、月球共n+2个点，有m艘飞船，每艘飞船会依次停放在
某些点，初始在地球上有k个人，求最少多少天能让所有人都到月球上。

题解：分层建图，将每天各个空间站作为一层，在通过题目关系建图。
将每个空间站(包括地球，月球)拆点，按照天拆点，对于第i天的空间
站，连接到i+1天的同一空间容量为INF的边(代表人在该空间站停留)，月球
的位置需要保证其通往汇点(毕竟到终点了，没必要再在月球停留了)。对于
飞船，如果昨天在fr，今天飞到to，则连接一条昨天的fr到今天的to，容量
为h[i]的边(代表有最多h[i]可以从fr到to点)，然后依次按照天数建图，
跑最大流，当总的最大流>=k时，则所有人都能到达月球。

题目链接：https://www.luogu.org/problem/P2754
************************************************************/
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
const int maxn = 10000;
const int mod = 2015;
struct node{
    int to, nex, cap, flow;
}eg[maxn*100];
int ed, cnt, hd[maxn], dis[maxn], vis[maxn];
int h[100], b[100][100], len[100], a[100];
int Find(int x);
void init();
int dinic(int s, int t);
bool bfs(int s, int t);
int dfs(int s, int t, int ans);
void add(int from, int to, int cap);

int main()
{
	init();
	int n, m, k, i, j, ed = 9998, res = 0;
	scanf("%d %d %d", &n, &m, &k);
	//加上地球、月球两个点，共n+2个点
	n += 2;
	for(i=1;i<=n;i++)
		a[i] = i;
	for(i=1;i<=m;i++)
	{
		scanf("%d %d", &h[i], &len[i]);
		for(j=0;j<len[i];j++)
		{
			scanf("%d", &b[i][j]);
			if(b[i][j] == -1)b[i][j] = n-1;
			//并查集判断地球与月球是否连通
			int x = Find(b[i][j]), y = Find(b[i][0]);
			if(x != y)a[x] = y;
		}
	}
	if(Find(0) != Find(n-1))
		printf("0\n");
	else{
		int up = 0;
		add(ed-2, 0, INF);
		add(n-1, ed, INF);
		i = 1;
		while(1)
		{
			//对每个空间站向后一天连一条边
			for(j=0;j<n-1;j++)
				add(j+up, j+up+n, INF);
			//对月球的点向汇点连边
			add(n-1+up+n, n-1+up, INF);
			//考虑飞船的路径
			for(j=1;j<=m;j++)
			{
				int to = b[j][i%len[j]];
				int fr = b[j][(i-1+len[j])%len[j]];
				add(fr+up, to+up+n, h[j]);
			}
			res += dinic(ed-2, ed);
			if(res >= k)break;
			i++;
			up += n;
		}
		printf("%d\n", i);
	}
	return 0;
}

int Find(int x)
{
	return a[x]=x==a[x]?x:Find(a[x]);
}

void init()
{
    cnt = 1;
    memset(hd, -1, sizeof(hd));
}

void add(int from, int to, int cap)
{
    eg[++cnt].to = to;
    eg[cnt].cap = cap;
    eg[cnt].flow = 0;
    eg[cnt].nex = hd[from];
    hd[from] = cnt;
    eg[++cnt].to = from;
    eg[cnt].cap = 0;
    eg[cnt].flow = 0;
    eg[cnt].nex = hd[to];
    hd[to] = cnt;
}

int dinic(int s, int t)
{
    int res = 0;
    while(bfs(s, t))
    {
        for(int i=0;i<=t;i++)
            vis[i] = hd[i];
        int d;
        while((d=dfs(s, t, INF))>0)
            res += d;
    }
    return res;
}

bool bfs(int s, int t)
{
    for(int i=0;i<=t;i++)
        dis[i] = -1;
    queue<int> que;
    que.push(s);
    dis[s] = 0;
    while(!que.empty())
    {
        int u = que.front();que.pop();
        for(int i=hd[u];i!=-1;i=eg[i].nex)
        {
            node e = eg[i];
            if(e.cap>e.flow && dis[e.to] == -1)
            {
                dis[e.to] = dis[u]+1;
                que.push(e.to);
            }
        }
    }
    return dis[t] != -1;
}

int dfs(int s, int t, int ans)
{
    if(s == t)return ans;
    for(int &i=vis[s];i!=-1;i=eg[i].nex)
    {
        node e = eg[i];
        if(e.cap > e.flow && dis[e.to] == dis[s]+1)
        {
            int d = dfs(e.to, t, min(ans, e.cap-e.flow));
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
