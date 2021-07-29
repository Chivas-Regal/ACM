/****************************************************************************
树的点分治

有一棵边带权的树，设dis(i,j)为i号点到j号点的最短距离，求dis(i,j)<=k的(i,j)(i<j)数量。

思路：只考虑当前子树，统计每棵个节点到根的距离，然后排序，统计方案数，因为可能两个点的
公共祖先不是根，所以需要减去每棵以儿子为根的子树中的方案数。
在树为链状时，会退化，所以每个树的方案数的统计，都从重心开始，最多logn层。

题目链接：http://poj.org/problem?id=1741
********************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<stack>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 10100;
const int mod = 10007;
struct node{
    int to, w;
    node(){}
    node(int a, int b):to(a),w(b){}
};
int mx, id, k, sz[maxn], vis[maxn];
LL ans;
vector<node> g[maxn];
vector<int> vr[maxn];
void init(int n);
LL getpair(int u);
void solve(int u, int pnum);
void getzh(int u, int fa, int pnum);
void dfs(int u, int fa, int lu, int rt);

int main()
{
    int n, i, j;
    while(scanf("%d %d", &n, &k), n||k)
    {
        init(n);
        for(i=1;i<n;i++)
        {
            int fr, to, w;
            scanf("%d %d %d", &fr, &to, &w);
            g[fr].push_back(node(to, w));
            g[to].push_back(node(fr, w));
        }
        solve(1, n);
        printf("%lld\n", ans);
    }
    return 0;
}

void init(int n)
{
    ans = 0;
    for(int i=0;i<=n;i++)
        g[i].clear();
    memset(vis, 0, sizeof(vis));
}
//递归求解，当前树
void solve(int u, int pnum)
{
    //求重心
    mx = INF;
    getzh(u, 0, pnum);
    u = id;
    vr[u].clear();
    vr[u].push_back(0);

    for(int i=0;i<g[u].size();i++)
        if(!vis[g[u][i].to]){
            int v = g[u][i].to;
            vr[v].clear();
            dfs(v, u, g[u][i].w, v);
            //减去属于同一棵子树的点对数量
            ans -= getpair(v);
            for(int j=0;j<vr[v].size();j++)
                vr[u].push_back(vr[v][j]);
        }
    //计算当前树点对数量
    ans += getpair(u);
    vis[u] = 1;
    for(int i=0;i<g[u].size();i++)
        if(!vis[g[u][i].to])
            solve(g[u][i].to, sz[g[u][i].to]);
}
//对当前树所有节点到根节点距离排序，求dis[i]+dis[j]<=k的点对数量
LL getpair(int u)
{
    sort(vr[u].begin(), vr[u].end());
    LL ans = 0, r=vr[u].size()-1;
    for(int i=0;i<vr[u].size();i++)
    {
        while(r>i && vr[u][r]+vr[u][i]>k)
            r--;
        if(r <= i)break;
        ans += (r-i);
    }
    return ans;
}
//求树的重心，pnum为当前树的节点数量
void getzh(int u, int fa, int pnum)
{
    sz[u] = 1;
    int maxx = 0, i;
    for(i=0;i<g[u].size();i++)
        if(g[u][i].to != fa && !vis[g[u][i].to]){
            getzh(g[u][i].to, u, pnum);
            maxx = max(maxx, sz[g[u][i].to]);
            sz[u] += sz[g[u][i].to];
        }
    maxx = max(maxx, pnum-sz[u]);
    if(maxx < mx){
        mx = maxx;
        id = u;
    }
}
//求每个点到点rt的距离
void dfs(int u, int fa, int lu, int rt)
{
    vr[rt].push_back(lu);
    for(int i=0;i<g[u].size();i++)
        if(g[u][i].to != fa && !vis[g[u][i].to])
            dfs(g[u][i].to, u, lu+g[u][i].w, rt);
}