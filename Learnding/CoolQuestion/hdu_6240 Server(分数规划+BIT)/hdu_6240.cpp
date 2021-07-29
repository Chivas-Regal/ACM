/*******************************************************************
分数规划

有n个物品，每个物品有四个值si，ti，Ai和Bi，代表si~ti时刻可用。需要选择
部分物品，使时间1~t内都有物品可用，同时使所有物品的(Ai和)/(Bi和)最小。

思路：sum(ai)/sum(bi)最小，显然是分数规划类问题，利用二分求解。在
求出di = ai-mid*bi后，求出满足条件的最大和。
显然若di>0,则必选，将sum+=di,且另该物品di为0。
将所有的物品排序，以ti为关键字，
需满足所有点都被覆盖。若一个物品可以覆盖[l,r]，
则dp[r] = max(dp[r], dp[i])，i属于[l-1,r]。
求区间最大值，可以利用树状数组来维护(线段树慎用，可能会T)。
因为该问题的特殊性，若不将di>0的提前取出，可能会导致dp出错。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=6240
***************************************************************/
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
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 100100;
const int mod = 3000001;
struct node{
    int s, t, a, b;
    double d;
}p[maxn];
double a[maxn], h[maxn];
int lowbit(int x);
bool isok(int n, int t);
bool cmp(node a, node b);
double query(int l, int r);
void Update(int x, double y, int n);

int main()
{
    int n, t, i, j, k, cas;
    scanf("%d", &cas);
    while(cas--)
    {
        scanf("%d%d", &n, &t);
        for(i=0;i<n;i++)
            scanf("%d %d %d %d", &p[i].s, &p[i].t, &p[i].a, &p[i].b);
        sort(p, p+n, cmp);
        double l = 0.00001, r = 1e3;
        while(l+eps<r)
        {
            double mid = (l+r)/2;
            for(i=0;i<n;i++)
                p[i].d = p[i].b-mid*p[i].a;
            if(isok(n, t))l = mid;
            else r = mid;
        }
        printf("%.3f\n", 1.0/l);
    }
    return 0;
}

bool isok(int n, int t)
{
    double x, sum = 0.0;
    for(int i=1;i<=t;i++)a[i] = h[i] = -1e10;
    for(int i=0;i<n;i++){
        if(p[i].d >0)sum += p[i].d, p[i].d = 0.0;
        if(p[i].s == 1)x = max(0.0, query(p[i].s, p[i].t));
        else x = query(p[i].s-1, p[i].t);
        Update(p[i].t, x+p[i].d, t);
        a[p[i].t] = max(a[p[i].t], x+p[i].d);
    }
    return a[t]+sum>=0.0;
}

int lowbit(int x)
{
    return x&(-x);
}

void Update(int x, double y, int n)
{
    for(int i=x;i<=n;i+=lowbit(i))
        h[i] = max(h[i], y);
}

double query(int l, int r)
{
    double mx = -1e10;
    while(r>=l){
        if(r-lowbit(r)>=l-1){
            mx = max(mx, h[r]);
            r -= lowbit(r);
        }else{
            mx = max(mx, a[r]);
            r--;
        }
    }
    return mx;
}

bool cmp(node a, node b)
{
    return a.t < b.t;
}