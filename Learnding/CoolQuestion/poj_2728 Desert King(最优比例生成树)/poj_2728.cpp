/****************************************************************************
最优比率生成树

在三维空间内，有n个点，第i个点的坐标为(xi,yi,zi)，保证z不同。现在需要修建n-1条水渠是n个点
相互连通，每两个点有一条边，第i个点与第j个点的距离为sqrt((xi-xj)^2+(yi-yj)^2)，花费为
abs(zi-zj)。求花费和/距离和最小。

思路：花费和/距离和最小，即距离和/花费和最大。处理出距离与花费，然后二分r，求最小生成树，
判断正负即可。

题目链接：http://poj.org/problem?id=2728
******************************************************************************/
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
#define eps 1e-7
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 1020;
const int mod = 998244353;
int vis[maxn], x[maxn], y[maxn], z[maxn];
double dis[maxn], d[maxn][maxn], w[maxn][maxn], b[maxn][maxn];
double gettree(int n);

int main()
{
    int n, i, j, k;
    while(scanf("%d", &n), n)
    {
        for(i=0;i<n;i++){
            scanf("%d %d %d", &x[i], &y[i], &z[i]);
        }
        for(i=0;i<n;i++)
            for(j=i+1;j<n;j++){
                w[i][j] = w[j][i] = sqrt((1.0*x[i]-x[j])*(x[i]-x[j])+(1.0*y[i]-y[j])*(y[i]-y[j]));
                b[i][j] = b[j][i] = abs(z[i]-z[j]);
            }
        double l = 0, r = 1e5;
        while(l+eps<r)
        {
            double mid = (l+r)/2;
            for(i=0;i<n;i++)
            {
                for(j=i+1;j<n;j++)
                    d[i][j] = d[j][i] = b[i][j]-mid*w[i][j];
                d[i][i] = 0;
            }
            if(gettree(n)<=0)r = mid;
            else l = mid;
        }
        printf("%.3f\n", l);
    }
    return 0;
}

double gettree(int n)
{
    int i, j, k;
    double sum = 0;
    memset(vis, 0, sizeof(vis));
    for(i=0;i<n;i++)dis[i] = d[0][i];
    vis[0] = 1;
    for(i=1;i<n;i++)
    {
        int u = -1;
        for(j=0;j<n;j++)
            if(!vis[j] && (u == -1 || dis[u] > dis[j]))
                u = j;
        if(u == -1)break;
        vis[u] = 1;
        sum += dis[u];
        for(j=0;j<n;j++)
            if(!vis[j])
                dis[j] = min(dis[j], d[u][j]);
    }
    return sum;
}