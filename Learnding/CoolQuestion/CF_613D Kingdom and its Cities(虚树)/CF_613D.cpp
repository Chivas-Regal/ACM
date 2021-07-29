/*******************************************************************************
虚树

有一棵n个点的数，m次询问，每次询问有k个点，求最少删除多少个这k个点之外的点，使这k个点不连通。

思路：对于每次询问若有k个点中有两个点为父子关系，无解。否则，构造虚树。
首先对每个点按DFS序排序。
依次将每个点放入栈中，
   设lca为栈顶元素和当前点u的LCA，
   若lca==栈顶元素，将放入栈中
   否则弹出栈中深度大于lca的元素，并连st[top-1]->st[top]。
若lca不在栈中，将其入栈
将u入栈。
所有点都处理后，依次将栈中元素弹出，并连边

建树后，DFS虚树，
当前节点为u，
若u为标记点，依次访问其子节点v，若子节点v为标记点，ans++。
若u不为标记点，统计v为标记点的个数num，若num>=2，ans++，若num==1，则u变为标记点。
在DFS时，对树中节点清除信息，以便下次询问。

题目链接：http://codeforces.com/contest/613/problem/D
*********************************************************************************/
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
const int maxn = 100100;
const int mod = 998244353;
int top, ans, dep[maxn], fa[maxn][30], a[maxn], vis[maxn], st[maxn];
int tot, cnt, dfn[maxn], hd1[maxn], hd2[maxn], nex[maxn*10], to[maxn*10];
void init(int n);
void Insert(int u);
void solve(int u);
int LCA(int u, int v);
void add(int f, int t, int hd[]);
void dfs(int u, int d, int f);
bool cmp(int a, int b);

int main()
{
    tot = cnt = 1;
    memset(hd1, -1, sizeof(hd1));
    memset(hd2, -1, sizeof(hd2));
    int t, n, i, j, k, q, m;
    scanf("%d", &n);
    for(i=1;i<n;i++){
        scanf("%d %d", &j, &k);
        add(j, k, hd1);
        add(k, j, hd1);
    }
    init(n);
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d", &m);
        for(i=0;i<m;i++){
            scanf("%d", &a[i]);
            vis[a[i]] = 1;
        }
        int sig = 1;
        for(i=0;i<m;i++)
            if(vis[fa[a[i]][0]])
            {
                sig = 0;break;
            }
        if(!sig){
            printf("-1\n");
            for(i=0;i<m;i++)
                vis[a[i]] = 0;
            continue;
        }
        sort(a, a+m, cmp);
        top = ans = 0;
        if(a[0] != 1)st[++top] = 1;
        for(i=0;i<m;i++)
            Insert(a[i]);
        while(top>1){
            add(st[top-1], st[top], hd2);
            top--;
        }
        solve(1);
        vis[1] = cnt = 0;
        printf("%d\n", ans);
    }
    return 0;
}

bool cmp(int a, int b)
{
    return dfn[a]<dfn[b];
}

void Insert(int u)
{
    if(top == 0){
        st[++top] = u;
        return;
    }
    int lca = LCA(u, st[top]);
    while(top>1 && dep[lca]<dep[st[top-1]])
    {
        add(st[top-1], st[top], hd2);
        top--;
    }
    if(dep[lca]<dep[st[top]])add(lca, st[top--], hd2);
    if((!top) || st[top]!=lca)st[++top] = lca;
    st[++top] = u;
}

void solve(int u)
{
    if(vis[u]){
        for(int i=hd2[u];i!=-1;i=nex[i]){
            solve(to[i]);
            if(vis[to[i]]){
                ans++;
                vis[to[i]] = 0;
            }
        }
    }else{
        for(int i=hd2[u];i!=-1;i=nex[i]){
            solve(to[i]);
            vis[u] += vis[to[i]];
            vis[to[i]] = 0;
        }
        if(vis[u]>=2)
        {
            ans++;
            vis[u] = 0;
        }
    }
    hd2[u] = -1;
}

void add(int f, int t, int hd[])
{
    to[++cnt] = t;
    nex[cnt] = hd[f];
    hd[f] = cnt;
}

void dfs(int u, int d, int f)
{
    dep[u] = d;
    fa[u][0] = f;
    dfn[u] = tot++;
    for(int i=hd1[u];i!=-1;i=nex[i])
        if(to[i] != f)dfs(to[i], d+1, u);
}

void init(int n)
{
    dfs(1, n, 0);
    for(int j=1;j<=20;j++)
        for(int i=1;i<=n;i++)
            fa[i][j] = fa[fa[i][j-1]][j-1];
}

int LCA(int u, int v)
{
    if(dep[u] > dep[v])swap(u, v);
    int i, j, k = dep[v]-dep[u];
    for(i=18;i>=0;i--)
        if(k&(1<<i))v = fa[v][i];
    if(u == v)return u;
    for(i=18;i>=0;i--)
        if(fa[u][i] != fa[v][i])
            v = fa[v][i], u = fa[u][i];
    return fa[u][0];
}