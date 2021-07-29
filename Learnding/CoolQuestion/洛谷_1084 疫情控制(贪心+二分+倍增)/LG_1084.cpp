/***********************************************************************
贪心+倍增+二分

有一棵n个节点，根为1的树，带边权。初始在一些节点有军队，求使所有根到叶节点的路径
都有军队，军队所需移动的最短时间。

思路：对答案进行二分，然后check在时限内，能否满足题目条件。
(若军队数目小于1号节点的子节点数，则无解)

check：显然在规定时间内，军队的移动越靠近根节点更好。所以可以先求出时限内，每支
军队能移动到的最靠近根节点的位置，可以利用倍增快速计算。将所有能移动至根节点的军队标记
为未驻扎状态，单独记录其到根节点已花费的时间，以及来自根节点的哪个子树。
DFS判断根节点每个子节点所在子树是否满足要求，若不满足，则记录该点到根节点距离。

对于子树不能满足条件的，要么考虑让本子树内能到达根节点的点停留在改子树，要么由
其他树内的军队过去。
先对每棵子树内能到根节点的(未驻扎)军队进行处理，记第i支军队到根节点后剩下的时间为ti,
节点u到根节点的距离为dis[u]。以t为关键字排序。第j支军队，其剩下tj的时间，来自
子节点v，若tj<dis[v]，则将军队j标记为以驻扎状态，节点v标记为已满足要求。

将剩下的未驻扎的军队按t排序，不满足要求的节点按dis排序，判断能否使所有的dis都能
有军队驻扎即可。

题目链接：https://www.luogu.com.cn/problem/P1084
*************************************************************************/
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
const int maxn = 100100;
const int mod = 1000000007;
struct node{
    int to;
    LL w;
    node(){}
    node(int a, LL b):to(a),w(b){}
};
int top1, top2, a[maxn], b[maxn], c[maxn], fa[maxn][22], dep[maxn];
LL dis[maxn], s1[maxn], s2[maxn];
vector<node> g[maxn], sx;
void bfs(int n);
bool dfs(int u);
bool cmp(node a, node b);
int goup(int v, int x);
bool check(LL mid, int n, int m);

int main()
{
    int n, i, j, k, m, w, num = 0;
    scanf("%d", &n);
    for(i=1;i<n;i++){
        scanf("%d %d %d", &j, &k, &w);
        g[j].push_back(node(k, (LL)w));
        g[k].push_back(node(j, (LL)w));
        if(j == 1 || k == 1)num++;
    }
    scanf("%d", &m);
    for(i=0;i<m;i++)
        scanf("%d", &a[i]);
    if(m < num)printf("-1\n");
    else{
        bfs(n);
        LL l = 0, r = 1e14;
        while(l<r)
        {
            LL mid = (l+r)/2;
            if(check(mid, n, m))r = mid;
            else l = mid+1;
        }
        printf("%lld\n", l);
    }
    return 0;
}

void bfs(int n)
{
    for(int i=0;i<=n;i++)dep[i] = 0;
    queue<int> que;
    que.push(1);
    dep[1] = 1;
    dis[1] = 0;
    while(!que.empty())
    {
        int u = que.front();que.pop();
        for(int i=0;i<g[u].size();i++)
        {
            int v = g[u][i].to;
            if(!dep[v]){
                dep[v] = dep[u]+1;
                fa[v][0] = u;
                dis[v] = dis[u] + g[u][i].w;
                for(int j=1;j<20;j++)
                    fa[v][j] = fa[fa[v][j-1]][j-1];
                que.push(v);
            }
        }
    }
}

bool check(LL mid, int n, int m)
{
    int i, j, k, l, r, x;
    top1 = top2 = 0;
    sx.clear();
    for(i=0;i<=n;i++)
        b[i] = c[i] = 0;
    for(i=0;i<m;i++){
        l = 2, r = dep[a[i]];
        while(l<r){
            int mid1 = (l+r)/2;
            x= goup(a[i], dep[a[i]]-mid1);
            if(dis[x]+mid>=dis[a[i]])r = mid1;
            else l = mid1+1;
        }
        x = goup(a[i], dep[a[i]]-l);
        if(l == 2){
            if(mid>dis[a[i]])sx.push_back(node(x, mid-dis[a[i]]));
            else b[x]++;
        }
        else b[x]++;
    }
    for(i=0;i<g[1].size();i++){
        int v = g[1][i].to;
        if(dfs(v))c[v] = 1;
    }
    sort(sx.begin(), sx.end(), cmp);
    for(i=0;i<sx.size();i++){
        if(!c[sx[i].to] && sx[i].w < dis[sx[i].to])
            c[sx[i].to] = 1;
        else s1[top1++] = sx[i].w;
    }
    for(i=0;i<g[1].size();i++)
        if(!c[g[1][i].to])s2[top2++] = dis[g[1][i].to];
    sort(s1, s1+top1);
    sort(s2, s2+top2);
    i = j = 0;
    while(i<top1 && j<top2)
        if(s1[i] >= s2[j])i++,j++;
        else i++;
    if(j >= top2)return true;
    else return false;
}

int goup(int v, int x)
{
    for(int i=17;i>=0;i--)
        if(x&(1<<i))v = fa[v][i];
    return v;   
}

bool dfs(int u)
{
    if(b[u])return true;
    if(g[u].size() == 1)return false;
    int sig = 1;
    for(int i=0;i<g[u].size();i++)
        if(dep[g[u][i].to] > dep[u])
            if(!dfs(g[u][i].to))sig = 0;
    return sig==1; 
}

bool cmp(node a, node b)
{
    return a.w < b.w;
}