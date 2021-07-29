/************************************************************************
费用流

思路：
预处理出素数表，对每个ai进行分解，求出其质因数数量。n^2枚举两元素能否配对。
若两点可以配对，则将其连一条边，可以看出最后的图可以是一个二分图的。因为这个图
是不会存在环的，所以肯定是一个二分图。将点分为两个集合，保证每条边的两个端点属于不同的集合。
因为需要满足ai%aj==0 && ai/aj为质数，所以可以利用分解后质数的个数的奇偶性分为两个集合。
构图：
连源点S到左边集合，费用为0，容量为bi的边；
连右边集合到汇点T，费用为0，容量为bi的边；
对于每条匹配边，连对应点，费用为-ci*cj，容量为INF。
对费用流稍加改进，每次从费用流中找费用最小的路径，求费用和<=0的最大流量,返回流量。
因为求出的是最短路，而题目实际上要求的是应该是每次求最大的路径，所以对费用求反。

题目链接：http://www.51nod.com/Challenge/Problem.html#problemId=2983
**************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<set>
#include<vector>
#include<queue>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-7
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 10020;
const int mod = 998244353;
struct node{
	int to, nex, flow, cap;
    LL cost;
}eg[30*maxn];
int tot, ed, pre[maxn], vis[maxn], hd[maxn];
int top, pri[1000000], d[1000100], a[maxn], b[maxn], id[maxn];
LL dis[maxn], c[maxn];
void init();
bool spfa(int s, int t);
void getprime();
int min_cost_flow(int s, int t, LL &cost);
void add(int f, int t, LL cost, int cap);

int main()
{
    init();
    getprime();
    int n, i, j, k, ed;
    scanf("%d", &n);
    ed = n+n+2;
    for(i=1;i<=n;i++)scanf("%d", &a[i]);
    for(i=1;i<=n;i++)scanf("%d", &b[i]);
    for(i=1;i<=n;i++)scanf("%lld", &c[i]);
    for(i=1;i<=n;i++){
        int num = 0, x= a[i];
        for(j=0;(LL)pri[j]*pri[j]<=x;j++){
            while(x%pri[j] == 0)
                x/=pri[j], num++;
        }
        if(x!=1)num++;
        if(num%2){
            id[i] = i;
            add(0, id[i], 0, b[i]);
        }
        else {
            id[i] = i+n;
            add(id[i], ed, 0, b[i]);
        }
    }
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        if(i!=j && a[i]>a[j] && a[i]%a[j] == 0)
        {
            int x = a[i]/a[j];
            for(k=0;pri[k]*pri[k]<=x;k++)
                if(x % pri[k] == 0)break;
            if(pri[k]*pri[k] > x){
                if(id[i]<id[j])add(id[i], id[j], -c[i]*c[j], INF);
                else add(id[j], id[i], -c[i]*c[j], INF);
           }
        }
    LL res;
    int ans = min_cost_flow(0, ed, res);
    printf("%d\n", ans);
    return 0;
}

void getprime()
{
    int n = 1000000, i, j;
    top = 0;
    for(i=2;i<=n;i++)
    {
        if(!d[i])pri[top++] = i;
        for(j=0;j<top && i*pri[j]<=n;j++){
            d[i*pri[j]] = 1;
            if(i%pri[j] == 0)break; 
        }
    }
}

void init()
{
	memset(hd, -1, sizeof(hd));
	tot = 1;
}

void add(int f, int t, LL cost, int cap)
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
		dis[i] = 1e18, vis[i] = 0, pre[i] = -1;
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
	if(dis[t] >= 1e17)return false;
	else return true;
}

int min_cost_flow(int s, int t, LL &cost)
{
	int flow = 0;
	cost = 0;
	while(spfa(s, t))
	{
		int mi = INF;
        LL sum = 0;
		for(int i=pre[t];i!=-1;i=pre[eg[i^1].to])
		{
			if(mi > eg[i].cap-eg[i].flow)
				mi = eg[i].cap - eg[i].flow;
		}
		for(int i=pre[t];i!=-1;i=pre[eg[i^1].to])
		{
			eg[i].flow += mi;
			eg[i^1].flow -= mi;
            sum += eg[i].cost;
		}
        if(cost+sum*mi<=0)
		    flow += mi, cost+=sum*mi;
        else{
            flow += llabs(cost)/llabs(sum);
            break;
        }
	}
	return flow;
}
