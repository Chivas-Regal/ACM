/**********************************************
网络流
有a机器人和b个出口，还有一个n*m的迷宫，机器人初始在迷宫的北方(地图上方)
运动方向是往南(即下方)，在迷宫中，有一些位置是屏障，这里并不能通行，还有
一些是空地，可以按原方向前进，同时空地可以被变为一个转向装置。问是否所有
机器人都能走出迷宫。

思路：可以发现所有机器人出去的路径是不能重叠的(但可以有交点)，所以可以考虑
将每个空地拆分为两个点，一个代表横向，一个代表纵向，两个点容量限制都为1，
然后将每个点向对应方向的下一个点连边(不转向，直接按原方向进行)，两个方向
的点之间再连一条边(代表安装了转向装置)，然后跑最大流即可，如果最大流等于
机器人的数量，则说明可以跑出去。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=6735
***********************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 40100;
const int mod = 772002;
struct node{
    int to, nex, cap, flow;
}eg[20*maxn];
int cnt, hd[maxn], dis[maxn], vis[maxn];
int id1[120][120], id2[120][120];
char str[120][120];
void init();
void add(int f, int t, int cap);
int dinic(int s, int t);
int dfs(int s, int t, int ans);
void bfs(int s, int t);

int main()
{
    int t, n, m, a, b, ed, i, j, k;
    scanf("%d", &t);
    while(t--)
    {
        init();
        int num = 1;
        scanf("%d %d %d %d", &n, &m, &a, &b);
        for(i=0;i<n;i++)
        {
            scanf(" %s", str[i]);
            for(j=0;j<m;j++){
                id1[i][j] = num++;
                id2[i][j] = num++;
            }
        }
        ed = num + num + 2;
        //printf("ed:%d num:%d\n", ed, num);
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
            if(str[i][j] == '0'){
                add(id1[i][j], id1[i][j]+num, 1);
                add(id2[i][j], id2[i][j]+num, 1);
                add(id1[i][j]+num, id2[i][j], 1);
                add(id2[i][j]+num, id1[i][j], 1);
                if(i != 0 && str[i-1][j] == '0')
                    add(id1[i][j]+num, id1[i-1][j], 1);
                if(i!=n-1 && str[i+1][j] == '0')
                    add(id1[i][j]+num, id1[i+1][j], 1);
                if(j != 0 && str[i][j-1] == '0')
                    add(id2[i][j]+num, id2[i][j-1], 1);
                if(j != m-1 && str[i][j+1] == '0')
                    add(id2[i][j]+num, id2[i][j+1], 1);
            }
        for(i=0;i<a;i++){
            scanf("%d", &j);
            add(0, id1[0][j-1], 1);
        }
        for(i=0;i<b;i++){
            scanf("%d", &j);
            add(id1[n-1][j-1], ed, INF);
        }
        int ans = dinic(0, ed);
        if(ans == a)printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

void init()
{
    cnt = 1;
    memset(hd, -1, sizeof(hd));
}

void add(int f, int t, int cap)
{
    eg[++cnt].to = t;
    eg[cnt].cap = cap;
    eg[cnt].flow = 0;
    eg[cnt].nex = hd[f];
    hd[f] = cnt;
    eg[++cnt].to = f;
    eg[cnt].cap = eg[cnt].flow = 0;
    eg[cnt].nex = hd[t];
    hd[t] = cnt;
}

int dinic(int s, int t)
{
    int res = 0;
    while(1)
    {
        bfs(s, t);
        if(dis[t] < 0)return res;
        for(int i=0;i<t;i++)
            vis[i] = hd[i];
        int d;
        while((d=dfs(s, t, INF))>0)
            res += d;
    }
    return res;
}

int dfs(int s, int t, int ans)
{
    if(s == t)return ans;
    for(int &i=vis[s];i!=-1;i=eg[i].nex)
    {
        if(eg[i].cap>eg[i].flow && dis[eg[i].to] == dis[s] + 1){
            int d = dfs(eg[i].to, t, min(ans, eg[i].cap-eg[i].flow));
            if(d >0){
                eg[i].flow += d;
                eg[i^1].flow -= d;
                return d;
            }
        }
    }
    return 0;
}

void bfs(int s, int t)
{
    for(int i=0;i<=t;i++)
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
            if(e.flow < e.cap && dis[e.to] == -1)
            {
                dis[e.to] = dis[u] + 1;
                que.push(e.to);
            }
        }
    }
}