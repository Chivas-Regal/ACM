/************************************************************************
最小割

有n*m大小的区域，每块区域可以是工业区或商业区，若为工业区，则有aij的收益，若
为商业区，则有bij的收益。对于第i行第j列的功能区，若与其相邻的有k块区域的功能区
与其不同，则会额外获得k*cij的收益。求最大收益。

思路：对于aij和bij，可以直接向S,T连边即可。
因为本题是不同的时候有额外的收益，而不同的区域一定是相邻的，所以可以考虑黑白染色。
将其中的一种色块，a和b互换，然后就转化为相同的时候有额外收益了。
对于相邻的,若块id1与块id2相同，则有y=c[id1]+c[id2]的额外收益。
额外建点x,连(0->x, y),(x->id1, INF), (x->id2, INF).
额外建点x,连(id1->x, INF), (id2->x,INF), (x->ed, y).

题目链接：https://www.luogu.com.cn/problem/P1935
***************************************************************************/
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
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-6
   
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 1000100;
const int mod = 998244353;
struct node{
    int to, nex, cap, flow;
}eg[maxn*20];
int ed, cnt, tot, hd[maxn], dis[maxn], vis[maxn];
int id[120][120], a[120][120];

void init()
{
    cnt = tot = 1;
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


bool bfs(int s, int t)
{
	int x = max(s, t);
    for(int i=0;i<=x;i++)
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

int dinic(int s, int t)
{
    int res = 0, x=max(s,t);
    while(bfs(s, t))
    {
        for(int i=0;i<=x;i++)
            vis[i] = hd[i];
        int d;
        while((d=dfs(s, t, INF))>0)
            res += d;
    }
    return res;
}

void add1(int id1, int id2, int y)
{
    int x = tot++;
    add(0, x, y);
    add(x, id1, INF);
    add(x, id2, INF);
}

void add2(int id1, int id2, int y)
{
    int x = tot++;
    add(id1, x, INF);
    add(id2, x, INF);
    add(x, ed, y);
}

int main()
{
    int n, m, i, j, k, sum = 0;
    init();
    scanf("%d %d", &n, &m);
    ed = n*m*8+1;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++){
            id[i][j] = tot++;
            scanf("%d", &k);
            if((i+j)%2)add(0, id[i][j], k);
            else add(id[i][j], ed, k);
            sum += k;
        }
    for(i=0;i<n;i++)
        for(j=0;j<m;j++){
            scanf("%d", &k);
            if((i+j)%2 == 0)add(0, id[i][j], k);
            else add(id[i][j], ed, k);
            sum += k;
        }
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d", &a[i][j]);
    for(i=0;i<n;i++)
        for(j=0;j<m;j++){
            if(i!=n-1){
                sum += 2*(a[i][j] + a[i+1][j]);
                add1(id[i][j], id[i+1][j], a[i][j]+a[i+1][j]);
                add2(id[i][j], id[i+1][j], a[i][j]+a[i+1][j]);
            }
            if(j!=m-1){
                sum += 2*(a[i][j] + a[i][j+1]);
                add1(id[i][j], id[i][j+1], a[i][j]+a[i][j+1]);
                add2(id[i][j], id[i][j+1], a[i][j]+a[i][j+1]);
            }
        }
    int ans = dinic(0, ed);
    printf("%d\n", sum-ans);
    return 0;
}