/***********************************
最小树形图
在一个三维空间内，有n个点，坐标为(x,y,z)，每个点都需要水，
每个点可以向部分点传递水(传递关系由输入确定)，或者向下打水
向下打水的代价为X*z，两者的曼哈顿距离dis=(|x1-x2|+|y1-y2|)，
一个点向另一个传水需要付出dis*Y的代价，如果由低处向比它高的
地方传，则需要额外付出Z的代价，求n个点全部通水需要的最少代价
题解：因为传递是单向的，所以可以加其看作为一个由n+1个点的有向
图，0号点为地下水，求0号点出发，可以到达所有点的最小代价和，
有向图以0为根的最小树形图就是结果。

最小树形图：
基于贪心的思想，对于每个点，尽量从到这个点代价最小的边过来(忽略根节点)，
如果某些边形成了环，则对其进行缩点，然后重复进行上述操作，直至无环或某
个根节点外的点不可达，具体流程如下：
1.求到达每个点需要的最小代价，如果除根节点外有点不可达，则不存在最小树形图
2.缩环，将选出的边缩环，如果存在环，则将其缩为一个点，不存在环，则为最小
树形图
3.对点和边进行重新编号，并回到步骤1

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=4009
************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<deque>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1020;
const int mod = 1000000007;
struct node
{
    int u, v, w;
}eg[maxn*maxn];
struct coor{
    int x,y,z;
}cr[maxn];
int in[maxn], id[maxn], vis[maxn], pre[maxn];
void addeg(int &m, int fr, int to, int w);
LL ZhuLiu(int n, int m, int root);

int main()
{
    int n, m, X, Y, Z, i, j, k;
    while(scanf("%d %d %d %d", &n, &X, &Y, &Z),n||X||Y||Z)
    {
        m = 0;
        for(i=1;i<=n;i++)
            scanf("%d %d %d", &cr[i].x, &cr[i].y, &cr[i].z);
        for(i=1;i<=n;i++)
        {
            scanf("%d", &k);
            //添加从地下打井的边
            addeg(m, 0, i, cr[i].z*X);
            while(k--)
            {
                scanf("%d", &j);
                int dis=abs(cr[i].x-cr[j].x)+abs(cr[i].y-cr[j].y)+abs(cr[i].z-cr[j].z);
                if(cr[i].z < cr[j].z)
                    addeg(m, i, j, dis*Y+Z);
                else
                    addeg(m, i, j, dis*Y);
            }
        }
        LL ans = ZhuLiu(n, m, 0);
        if(ans == -1)
            printf("poor XiaoA\n");
        else
            printf("%lld\n", ans);
    }
    return 0;
}
//添加边
void addeg(int &m, int fr, int to, int w)
{
    eg[m].u = fr, eg[m].v = to;
    eg[m].w = w;
    m++;
}
//朱刘算法求最小树形图
//n:点的数量，m：边的数量，root：根节点(就是求root开始的最小树形图)
LL ZhuLiu(int n, int m, int root)
{
    LL res = 0;
    int i, cnt;
    while(1)
    {
        for(i=0;i<=n;i++)
            in[i] = INF, id[i]=vis[i]=-1;
        //遍历m条边，对每个点求到其最近的那条边(根节点除外)
        for(i=0;i<m;i++)
        {
            int u=eg[i].u, v=eg[i].v;
            if(u!=v && eg[i].w<in[v])
                in[v] = eg[i].w, pre[v] = u;
        }
        //如果有点无法到达，则不存在最小树形图
        for(i=0;i<=n;i++)
            if(i!=root && in[i] == INF)return -1;
        cnt = -1;
        //将当前图里的环缩为一个点
        for(i=0;i<=n;i++)
        {
            if(i == root)continue;
            res += in[i];
            int v = i;
            while(id[v]==-1 && vis[v]!=i && v!=root)
            {
                vis[v] = i;
                v = pre[v];
            }
            if(v!=root && id[v] == -1)
            {
                id[v] = ++cnt;
                for(int u=pre[v];u!=v;u=pre[u])
                    id[u] = cnt;
            }
        }
        //如果没有环，则最小树形图存在，返回
        if(cnt == -1)break;
        //如果存在环，将其余不是环的点重新编号
        for(i=0;i<=n;i++)
        if(id[i] == -1)id[i] = ++cnt;
        //将边的点的编号更新为新的编号，以及将其边的权值减去离其最近的边
        //因为对于到这个点的边来说，最近的那个点权值已经加过了
        for(i=0;i<m;i++)
        {
            int u=eg[i].u, v=eg[i].v;
            if(id[u]!=id[v])
                eg[i].w -= in[v];
            eg[i].u = id[u], eg[i].v = id[v];
        }
        //更新点的数量和根节点的编号
        n = cnt;
        root = id[root];
    }
    return res;
}
