/************************************************************
最小费用流

有一棵树，有n个节点，每个节点上有ai个物品，物品可以移动，每条边移动单位物品的代价为ci,
希望移动后，节点上物品的方差尽量小，求最小代价。

思路一：设物品总和为sum,ave=sum/n,num=sum%n;方差尽量小，物品应尽量平均分配，
每个节点的物品数量都为ave或ave+1。num个数量为ave+1的点，可以将n个点连一条边，
i->po，容量为1，费用为0；点po到汇点t连容量为num，费用为0的边。这样num个为+1的问题
就解决了。
建图：
对于每个点连源点S到点i，容量为a[i],费用为0，点i到汇点T，容量为ave，费用为0；
对于每个点连i到特殊点po，容量为1，费用为0；po到汇点T，容量为num，费用为0；
将树的边连接，容量为INF，费用为ci，双向边。

题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827367987
****************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<set>
#include<queue>
#include<stack>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 120;
const int mod = 1000000007;
struct node{
    int to, nex, cap, flow, cost;
}eg[1020];
int a[maxn];
int cnt, dis[maxn], vis[maxn], hd[maxn], pre[maxn];
void init();
bool spfa(int s, int t);
int min_cost_flow(int s, int t, int &cost);
void add(int fr, int to, int cap, int cost);

int main()
{
    int n, i, j, k, ed, sum;
    while(~scanf("%d", &n))
    {
        init();
        sum = 0, ed = n+2;
        for(i=1;i<=n;i++){
            scanf("%d", &a[i]);
            add(0, i, a[i], 0);
            sum += a[i];
        }
        int ave = sum/n, yu = sum%n;
        add(ed-1, ed, yu, 0);
        for(i=1;i<=n;i++){
            add(i, ed, ave, 0);
            add(i, ed-1, 1, 0);
        }
        for(i=1;i<n;i++){
            int c;
            scanf("%d %d %d", &j, &k, &c);
            j++, k++;
            add(j, k, INF, c);
            add(k, j, INF, c);
        }
        int ans;
        min_cost_flow(0, ed, ans);
        printf("%d\n", ans);
    }
    return 0;
}

void init()
{
    memset(hd, -1, sizeof(hd));
    cnt = 1;
}

void add(int fr, int to, int cap, int cost)
{
    eg[++cnt].to = to;
    eg[cnt].cap = cap;
    eg[cnt].flow = 0;
    eg[cnt].cost = cost;
    eg[cnt].nex = hd[fr];
    hd[fr] = cnt;
    eg[++cnt].to = fr;
    eg[cnt].cap = eg[cnt].flow = 0;
    eg[cnt].cost = -cost;
    eg[cnt].nex = hd[to];
    hd[to] = cnt;
}

bool spfa(int s, int t)
{
    for(int i=0;i<=t;i++)
        dis[i] = INF, pre[i] = -1, vis[i] = 0;
    dis[s] = 0;
    vis[s] = 1;
    queue<int> que;
    que.push(s);
    while(!que.empty())
    {
        int u = que.front();que.pop();
        vis[u] = 0;
        for(int i=hd[u];i!=-1;i=eg[i].nex)
        {
            node e = eg[i];
            if(e.cap>e.flow && dis[e.to] > dis[u]+e.cost)
            {
                dis[e.to] = dis[u]+e.cost;
                pre[e.to] = i;
                if(!vis[e.to])
                {
                    vis[e.to] = 1;
                    que.push(e.to);
                } 
            }
        }
    }
    return dis[t] != INF;
}

int min_cost_flow(int s, int t, int &cost)
{
    int res = 0, mi;
    cost = 0;
    while(spfa(s, t))
    {
        mi = INF;
        for(int i=pre[t];i!=-1;i=pre[eg[i^1].to])
            if(mi > eg[i].cap - eg[i].flow)
                mi = eg[i].cap - eg[i].flow;
        for(int i=pre[t];i!=-1;i=pre[eg[i^1].to])
        {
            eg[i].flow += mi;
            eg[i^1].flow -= mi;
            cost += eg[i].cost * mi;
        }
        res += mi;
    }
    return res;
}