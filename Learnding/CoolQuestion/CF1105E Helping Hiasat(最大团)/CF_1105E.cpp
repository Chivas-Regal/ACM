/****************************************************
最大团

题意：Hiasat有m个好友，有n个事件，事件有两种类型：
1 Hiasat改变账号昵称， 2 s，Hiasat的好友s访问Hiasat的主页。
当Hiasat的好友每次访问其主页时，Hiasat的昵称若与好友名相同，则好友是快乐的。
求Hiasat最多另多少个好友是快乐的？

思路： 两个相邻1之间有若干个2操作，这些人只能保证其中的一个人开心。将事件以1为界，
分为几段。每段之间的2操作涉及到的人两两连边。得到图后，求该图的最大独立集即为所求。
可以通过求原图的补图求最大独立团，DFS剪枝。

题目链接：http://codeforces.com/contest/1105/problem/E
******************************************************/
#include<cstdio>
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
const int maxn = 100100;
const int mod = 998244353;
char str[maxn][48];
int mx, op[maxn], a[52][52], b[52], cnt[52], vis[52];
vector<int> g;
map<string,int> mp;
void solve(int m);
int dfs(int u, int step, int m);

int main()
{
    int n, m, i, j, k, cnt = 0;
    scanf("%d %d", &n, &m);
    for(i=1;i<=n;i++){
        scanf("%d", &op[i]);
        if(op[i] == 2){
            scanf(" %s", str[i]);
            if(mp.count(str[i]) == 0)mp[str[i]] = ++cnt;
        }
    }
    op[n+1] = op[n+2] = op[n+3] = 1;
    i = 1;
    while(i<=n){
        memset(vis, 0, sizeof(vis));
        while(op[i] != 1)i++;
        j = i+1;
        while(op[j] != 1)
            vis[mp[str[j++]]] = 1;
        g.clear();
        i = j;
        for(j=1;j<=m;j++)if(vis[j])g.push_back(j);
        for(j=0;j<g.size();j++)
            for(k=j+1;k<g.size();k++)
                a[g[j]][g[k]] = a[g[k]][g[j]] = 1;
    }
    solve(m);
    printf("%d\n", max(0, mx));
    return 0;
}

void solve(int m)
{
    mx = -1;
    for(int i=m;i>0;i--){
        vis[0] = i;
        dfs(i, 1, m);
        cnt[i] = mx;
    }
}

int dfs(int u, int step, int m)
{
    int i, j;
    for(i=u+1;i<=m;i++){
        if(cnt[i]+step<=mx)return 0;
        if(a[u][i]==0){
            for(j=0;j<step;j++)if(a[i][vis[j]])break;
            if(j == step){
                vis[step] = i;
                if(dfs(i, step+1, m))return 1;
            }
        }
    }
    if(step > mx){
        for(i=0;i<step;i++)b[i] = vis[i];
        mx = step;
        return 1;
    }
    return 0;
}