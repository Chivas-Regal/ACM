/**************************************************************************
树形DP

有一棵树，有n个节点，每个节点上有ai个物品，物品可以移动，每条边移动单位物品的代价为ci,
希望移动后，节点上物品的方差尽量小，求最小代价。

思路二：首先已知的是求方差最小，需要尽量平分，每个节点要不有ave个，要不有ave+1个。
对于每个节点来说，他的物品的移动一定是经过其父节点的，所以我们在DP时，只需要考虑将物品
移动至其父节点的代价，如果需要从外部移入，则同样只需考虑从其父节点移入的代价。
树形DP。设数组dp[i][j],代表考虑到节点u及其子树，存在j个物品数为ave+1的点的最小花费。
设当前处于节点u，那么初始化只考虑当前点，然后DFS合并子树。设数组sz代表结点所在子树的数量，
c为节点到其父节点的距离。
dp[u][j+k] = min(dp[u][j]+dp[v][k]+pnum*c);
其中pnum = abs(ave*(sz[u]+sz[v])+j+k-a[u]-a[v])-abs(ave*sz[u]+j-a[u]);(此时a[u]和sz[u]
的信息只是当前处理到的信息，并未合并v及其子树部分)。u节点中共有j+k个为ave+1的点，那么
总共移出到其父节点(从父节点移入)的物品数量为abs(ave*(sz[u]+sz[v])+j+k-a[u]-a[v])，因为
dp[u][j]已经统计过一部分移出(移入)的代价，所以需要将其减去abs(ave*sz[u]+j-a[u])。
同时因为在合并子树v时，dp[u]的值会被多次访问和更新，所以需要另外设数组记录更新的值，待所有
值计算完成后，在赋给dp[u].

题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827367987
***************************************************************************/
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
    int to, w;
    node(){}
    node(int a, int b):to(a),w(b){}
};
int ave, sum, yu, a[maxn], sz[maxn];
LL dp[maxn][maxn], dps[maxn][maxn];
vector<node> g[maxn];
void dfs(int u, int fa, LL c);

int main()
{
    int n, i, j, k;
    while(~scanf("%d", &n))
    {
        sum = 0;
        for(i=0;i<n;i++)
        {
            scanf("%d", &a[i]);
            sum += a[i];
            g[i].clear();
        }
        for(i=1;i<n;i++){
            int c;
            scanf("%d %d %d", &j, &k, &c);
            g[j].push_back(node(k, c));
            g[k].push_back(node(j, c));
        }
        ave = sum / n, yu = sum%n;
        dfs(0, -1, 0LL);
        printf("%lld\n", dp[0][yu]);
    }
    return 0;
}

void dfs(int u, int fa, LL c)
{
    sz[u] = 1;
    for(int i=0;i<=min(sz[u], yu);i++)
        dp[u][i] = abs(ave+i-a[u])*c;
    for(int i=0;i<g[u].size();i++)
        if(g[u][i].to != fa)
        {
            int v = g[u][i].to;
            dfs(v, u, (LL)g[u][i].w);
            //因为dp数组后面的会依赖前面的结果，不能直接更新
            for(int j=0;j<=min(sz[u]+sz[v], yu);j++)
                dps[u][j] = 1e16;
            for(int j=0;j<=sz[u];j++)
                for(int k=0;k<=sz[v];k++)
                    if(j+k <= yu)
                    {
                        int num1 = abs(ave*sz[u]+j-a[u]);
                        int num2 = abs(ave*(sz[u]+sz[v])+j+k-a[u]-a[v]);
                        LL sum = dp[u][j]-num1*c + num2*c + dp[v][k];
                        dps[u][j+k] = min(dps[u][j+k], sum);
                    }
            for(int j=0;j<=min(sz[u]+sz[v], yu);j++)
                dp[u][j] = dps[u][j];
            a[u] += a[v];
            sz[u] += sz[v];
        }
}