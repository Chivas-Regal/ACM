/********************************************************************************
贪心

有一个n个数的序列，其LIS已给出，同时给出了每个位置的数的范围[li,ri]，求一个合理的原序列。

思路：将所有位置按LIS的大小分组，然后依次考虑每个组内的元素。设原序列为b。
当考虑LIS为dpi的组，组内元素在原数组中位置依次为a1,a2,...am(ai<ai+1)。需要保证
组内靠前的元素大于等于靠前的元素，即对于任意的ai,b[ai]>=b[aj](i<j<=m)。
ai位置的数，还要大于一个ai之前的值为dpi-1的值。

题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827370262
***********************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<map>
#include<vector>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 100100;
const int mod = 1000000000;
struct node{
    int id, l, r;
    node(){}
    node(int a, int c, int d):id(a),l(c),r(d){}
};
int ans[maxn], a[maxn], up[maxn], lo[maxn];
vector<node> g[maxn];

int main()
{
    int t, n, i, j, k, m;
    scanf("%d", &t);
    while(t--)
    {
        m = 0;
        scanf("%d", &n);
        for(i=0;i<=n;i++)
            g[i].clear();
        for(i=1;i<=n;i++)
            scanf("%d", &a[i]);
        up[0] = 0, a[0] = ans[0] = -1;
        for(i=1;i<=n;i++){
            up[a[i]] = i;
            lo[i] = up[a[i]-1];
        }
        for(i=1;i<=n;i++)
        {
            scanf("%d %d", &j, &k);
            g[a[i]].push_back(node(i, j, k));
        }
        for(i=1;i<=n;i++)
        {
            int mx = 0;
            for(j=g[i].size()-1;j>=0;j--)
            {
                node e = g[i][j];
                mx = max(mx, e.l);
                mx = max(mx, ans[lo[e.id]]+1);
                ans[e.id] = mx;
            }
        }
        for(i=1;i<n;i++)
            printf("%d ", ans[i]);
        printf("%d\n", ans[n]);
    }
    return 0;
}