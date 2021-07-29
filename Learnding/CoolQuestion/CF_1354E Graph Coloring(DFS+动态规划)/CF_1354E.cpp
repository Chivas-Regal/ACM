/*******************************************************************
DFS+动态规划

n个点m条边的无向图，要求给n个点赋值，每个点可以赋为1、2、3中的一个，n个点共有
n1个为1的点，n2个为2的点，n3个为3的点。且每条边的两个顶点的值满足|valu-valv| = 1;
求是否存在合适的赋值方案。

思路:每条边的两个顶点的值满足|valu-valv| = 1，所以赋值为2的点很重要，而1,3实际上
并无区别(1,3之间不会有边，且都只与2连边)。实际上就是求能否变为一个二分图，且二分图
的一个集合的大小为n2。
二分图：DFS判断是否存在奇环即可。在DFS的同时，对于每个连通块，求出两个集合的大小。
分别计做sz1,sz2。

赋值为2的点：在DFS后，共有cnt个连通块，第i连通块二分图两边集合的大小为sz1i和sz2i。
动态规划，求sz1和sz2的组合能否存在方案使和为n2即可。

若存在奇环或不存在方案使和为n2，则无解。否则利用动态规划的记录，优先标记赋值
为2的点，剩下的点赋值为1、3即可。 

题目链接：http://codeforces.com/problemset/problem/1354/E
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
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 5020;
const double pi = acos(-1.0);
const int mod = 1000000007;
int cnt, sig, col[maxn], dp[maxn][maxn];
char ans[maxn];
vector<int> g[maxn], po[maxn][4];
void dfs(int u, int f, int cl);

int main()
{
    int n, m, i, j, k, n1, n2, n3;
    sig = 1;
    memset(col, -1, sizeof(col));
    scanf("%d %d %d %d %d", &n, &m, &n1, &n2, &n3);
    for(i=0;i<m;i++){
        scanf("%d %d", &j, &k);
        g[j].push_back(k);
        g[k].push_back(j);
    }
    cnt = 0;
    for(i=1;i<=n;i++)
        if(col[i] == -1){
            dfs(i, 0, 1);
            cnt++;
        }
    if(!sig)printf("NO\n");
    else{
        dp[0][0] = 1;
        for(i=0;i<cnt;i++){
            int a1 = po[i][0].size(), a2 = po[i][1].size();
            for(j=0;j<=n2;j++)
            if(dp[i][j])
            {
                if(j+a1<=n2)dp[i+1][j+a1] = 1;
                if(j+a2<=n2)dp[i+1][j+a2] = 1;
            }
        }
        if(dp[cnt][n2] == 0)printf("NO\n");
        else{
            k = n2;
            for(i=cnt;i>0;i--){
                int v;
                if(dp[i-1][k-po[i-1][0].size()])
                    v = 0;
                else v = 1;
                k -= po[i-1][v].size();
                for(j=0;j<po[i-1][v].size();j++)
                    ans[po[i-1][v][j]] = '2';
            }
            for(i=1;i<=n;i++){
                if(ans[i] != '2'){
                    if(n1)ans[i] = '1', n1--;
                    else ans[i] = '3', n3--;
                }
            }
            printf("YES\n%s\n", ans+1);
        }
    }
    return 0;
}

void dfs(int u, int f, int cl)
{
    col[u] = cl;   
    po[cnt][cl].push_back(u);
    for(int i=0;i<g[u].size();i++)
        if(g[u][i] != f){
            int v = g[u][i];
            if(col[v] == -1)dfs(v, u, !cl);
            else if(col[v] == col[u])sig = 0;
        }
}