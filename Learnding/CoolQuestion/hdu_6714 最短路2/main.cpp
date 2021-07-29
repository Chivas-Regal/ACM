//���·
//��Ŀ����˼��������i��j�����·���������Ľڵ���
//��ߵĺ͡�
//��Ϊֻ����ǧ���ߣ����Զ�ÿ������һ��dijsktra
//��¼��j������Ҫ�������������С����
//��Ŀ���ӣ� http://acm.hdu.edu.cn/showproblem.php?pid=6714
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
    //pre������ǰ�ڵ��������С�Ƕ��� 
    //���preӦ�ó�ʼ��ΪINF����ʼ��Ϊ0��WA 
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
        //���������������ı�Ӧ����0 
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
