/********************************************************************
有源汇有上下界最大流

有m个女生，共有n天，每天可以选择给部分女生拍照，要求n天后，给第i个女生拍的照片数量
不少于Gi。在第i天，最多能拍Di张照片，可以选择给C个女生拍照，给第Tki个女生拍的照片数,
需要在[lki, rki]之中。求是否存在合适的拍照方案。如果存在，最多能拍多少张照片。

思路：有源汇有上下界最大流。首先判断是否有可行流。因为有源汇点，所以添加一条汇点到源点的
边，边界为[0,INF].然后问题就转化为了，无源汇有上下界可行流，建图即可。
若可行，则继续求最大流。判断可行流时，加的汇点到源点的边的流量，记为ans1。去除判定可行
流时添加的点和边，然后在残留网络中求源点到汇点的最大流ans2。ans1+ans2即为所求。

判断无源汇有上下界最大流：
对于一条边，u->v，边界为[l,r]。
另a[u] -= l, a[v] += l。
建边u->v，容量为r-l。

所有边处理完后，添加点ss,tt。
若a[i]>0，添加边ss->i，容量为a[i], sum+= a[i].
若a[i]<0，添加边i->tt，容量为-a[i].

建完图后，求ss到tt的最大流。若最大流 == sum，即存在可行流。

题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827367941
***********************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 2020;
const int mod = 1000000007;
struct node{
    int to, nex, cap, flow, id;
}eg[maxn*maxn];
int cnt, dis[maxn], vis[maxn], hd[maxn];
int tot, in[maxn], a[maxn], d[maxn], g[maxn], l[maxn*maxn], r[maxn*maxn];
void init();
bool bfs(int s, int t);
int dinic(int s, int t);
int dfs(int s, int t, int ans);
void add(int fr, int to, int cap, int id);

int main()
{
    int n, m, ed, i, j, k;
    while(~scanf("%d %d", &n, &m))
    {
        tot = 0;
        init();
        memset(a, 0, sizeof(a));
        ed = n+m+1;
        for(i=1;i<=m;i++){
            scanf("%d", &g[i]);
            a[ed] += g[i];
            a[n+i] -= g[i];
            add(n+i, ed, INF, 0);
        }
        for(i=1;i<=n;i++){
            int c;
            scanf("%d %d", &c, &d[i]);
            add(0, i, d[i], 0);
            while(c--){
                tot++;
                scanf("%d %d %d", &j, &l[tot], &r[tot]);
                j++;
                add(i, n+j, r[tot]-l[tot], tot);
                a[n+j] += l[tot];
                a[i] -= l[tot];
            }
        }
        add(ed, 0, INF, 0);
        int ss = ed+1, tt = ed+2, sum = 0;
        for(i=0;i<=ed;i++){
            if(a[i] > 0)add(ss, i, a[i], 0), sum += a[i];
            else if(a[i] < 0)add(i, tt, -a[i], 0);
        }
        int ans = dinic(ss, tt);
       if(ans == sum){
            ans = dinic(0, ed);
            for(i=1;i<=n;i++)
                for(j=hd[i];j!=-1;j=eg[j].nex)
                    if(j%2==0)
                        l[eg[j].id] += eg[j].flow;
            printf("%d\n", ans);
            for(i=1;i<=tot;i++)
                printf("%d\n", l[i]);
        }else printf("-1\n");
        printf("\n");
    }
    return 0;
}

void init()
{
    memset(hd, -1, sizeof(hd));
    cnt = 1;
}

void add(int fr, int to, int cap, int id)
{
    eg[++cnt].to = to;
    eg[cnt].cap = cap;
    eg[cnt].flow = 0;
    eg[cnt].nex = hd[fr];
    eg[cnt].id = id;
    hd[fr] = cnt;
    eg[++cnt].to = fr;
    eg[cnt].flow = eg[cnt].cap = 0;
    eg[cnt].nex = hd[to];
    eg[cnt].id = id;
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
    while(que.size())
    {
        int u = que.front();que.pop();
        for(int i=hd[u];i!=-1;i=eg[i].nex)
        {
            if(eg[i].cap > eg[i].flow && dis[eg[i].to] == -1){
                dis[eg[i].to] = dis[u]+1;
                que.push(eg[i].to);
            }
        }
    }
    return dis[t] != -1;
}

int dfs(int s, int t, int ans)
{
    if(s == t)return ans;
    for(int &i = vis[s];i!=-1;i=eg[i].nex)
    if(eg[i].cap > eg[i].flow && dis[eg[i].to] == dis[s]+1)
    {
        int d = dfs(eg[i].to, t, min(ans, eg[i].cap-eg[i].flow));
        if(d>0){
            eg[i].flow += d;
            eg[i^1].flow -= d;
            return d;
        }
    }
    return 0;
}