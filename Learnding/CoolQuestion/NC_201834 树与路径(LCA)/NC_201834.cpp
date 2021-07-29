/**********************************************************************
LCA+差分

思路：以r为根可以O(n)计算出结果。依次计算结果，若已知点u时的结果，当计算u的子节点
v时的结果时。只有经过边(u,v)的路径，根的变化才会影响这部分结果。设路径s->t经过
边(u,v)，设x = dis(s,u), y = dis(s, t)，则以u为根该路径贡献为x*(y-x)，以v为根
该路径贡献为(x+1)*(y-(x+1))，两者相减可得-2x+y-1。
树上差分即可。

题目链接：https://ac.nowcoder.com/acm/problem/201834
********************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#include<bitset>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-8
   
using namespace std;
typedef long long LL;  
typedef pair<int, int> P;
const int maxn = 300100;
const int mod = 998244353;
int dep[maxn], fa[maxn][20];
LL ans[maxn], b[maxn];
vector<int> g[maxn];
void init(int n);
int LCA(int u, int v);
void dfs(int u, int d);
void dfs1(int u, int fa);
void dfs2(int u, int fa);
int main()
{
    int n, m, i, j, k, u, v;
    LL res = 0;
    scanf("%d %d", &n, &m);
    for(i=1;i<n;i++){
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    init(n);
    while(m--)
    {
        scanf("%d %d", &u, &v);
        int lc = LCA(u, v);
        ans[u]-=2, b[u] += 2*dep[lc]-dep[v]+dep[u]+1;
        ans[v]-=2, b[v] += 2*dep[lc]-dep[u]+dep[v]+1;
        ans[lc]+=4, b[lc] -= 4*dep[lc]+2;
        res += 1LL*(dep[u]-dep[lc])*(dep[v]-dep[lc]);
    }
    dfs1(1, 0);dfs2(1, 0);
    for(i=1;i<=n;i++)
        printf("%lld\n", res+ans[i]);
    return 0;
}

void init(int n)
{
    dfs(1, 1);
    for(int j=1;j<20;j++) 
        for(int i=1;i<=n;i++)
            fa[i][j] = fa[fa[i][j-1]][j-1];  
}

void dfs(int u, int d)
{
    dep[u] = d;
    for(int i=0;i<g[u].size();i++)
        if(g[u][i] != fa[u][0]){
            fa[g[u][i]][0] = u;
            dfs(g[u][i], d+1);
        }
}

int LCA(int u, int v)
{
    if(dep[u] > dep[v])swap(u, v);
    int k = dep[v]-dep[u];
    for(int i=19;i>=0;i--)
        if(k&(1<<i))v = fa[v][i];
    if(u == v)return u;
    for(int i=19;i>=0;i--)
        if(fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];

}

void dfs1(int u, int fa)
{
    for(int i=0;i<g[u].size();i++)
        if(g[u][i] != fa){
            dfs1(g[u][i], u);
            ans[u] += ans[g[u][i]];
            b[u] += b[g[u][i]]; 
        }
}

void dfs2(int u, int fa)
{
    ans[u] = ans[u]*dep[u]+b[u]+ans[fa];
    for(int i=0;i<g[u].size();i++)
        if(g[u][i] != fa)dfs2(g[u][i], u);
}