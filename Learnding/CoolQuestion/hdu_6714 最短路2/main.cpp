//最短路
//题目的意思就是让求i到j的最短路中所经过的节点编号
//最高的和。
//因为只有两千条边，所以对每个边跑一遍dijsktra
//记录到j点所需要经过的最大编号最小即可
//题目链接： http://acm.hdu.edu.cn/showproblem.php?pid=6714
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) printf("debug:%d\n", x);
#define INF 0x3f3f3f3f
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<LL, int> P;
const int maxn = 100100;
const LL mod = 998244353;
struct node{
    int to;
    LL p;
    node(int a, LL b):to(a),p(b){}
};
bool vis[maxn];
int pre[maxn];
LL ans, dis[maxn];
vector<node> g[maxn];
void solve(int u, int n);

int main()
{
    int t, n, m, i, j;
    scanf("%d", &t);
    while(t--){
        ans = 0;
        scanf("%d %d", &n, &m);
        for(i=0;i<=n+10;i++)g[i].clear();
        for(i=0;i<m;i++){
            int f, t;
            LL p;
            scanf("%d %d %I64d", &f, &t, &p);
            g[f].push_back(node(t, p));
            g[t].push_back(node(f, p));
        }
        for(i=1;i<=n;i++){
            solve(i, n);
        }
        printf("%I64d\n", ans%mod);
    }
    return 0;
}

void solve(int s, int n)
{
    int i, u;
    priority_queue<P, vector<P>, greater<P> > que; 
    //pre：到当前节点最大编号最小是多少 
    //这边pre应该初始化为INF，初始化为0会WA 
    for(i=0;i<=n+10;++i)
        dis[i] = 1e15, pre[i] = INF, vis[i] = false;
    dis[s] = 0, pre[s] = 0;
    que.push(P(0LL, s));
    while(!que.empty())
    {
        P p = que.top();que.pop();
        if(vis[p.second])continue;
        u = p.second;
        vis[u] = 1;
        ans +=pre[u];
        //本身就与起点相连的边应该是0 
        if(u != s)pre[u] = max(u, pre[u]);
        for(i=0;i<g[u].size();i++){
            int v = g[u][i].to;
            if(dis[v] > dis[u] + g[u][i].p){
                dis[v] = dis[u] + g[u][i].p;
                pre[v] = pre[u];
                que.push(P(dis[v], v)); 
            }
            else if(dis[v] == dis[u] + g[u][i].p)
                pre[v] = min(pre[v], pre[u]);
        }
    }
    ans %= mod;
}
