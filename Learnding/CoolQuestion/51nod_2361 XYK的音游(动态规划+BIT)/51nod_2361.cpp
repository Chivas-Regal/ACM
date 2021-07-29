/***************************************************************************
动态规划+BIT

一个音乐游戏共有n个按键，有m个事件，在ti时刻，点击按键xi可以获得wi的分数。玩家手速
较慢，每秒只能从第x个按键移动至[x-pos,x+pos]，求最高得分。

思路：显然需要DP，但n和m较大，n^2复杂度显然不可行。设第i个按键可以由第i个按键转移的
条件为 p*ti-p*tj>=|xi-xj|
=> p*ti-p*tj>=xi-xj,p*ti-p*tj>=xj-xi
=> p*ti-xi>=p*tj-xj , p*ti+xi >= p*tj+xj
将前面的排序处理，后面部分利用树状数组即可。

题目链接：http://www.51nod.com/Challenge/Problem.html#problemId=2361
******************************************************************************/
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
#define eps 1e-7
 
using namespace std;
typedef long long LL;   
typedef pair<LL, int> P;
const int maxn = 100100;
const int mod = 998244353;
struct node{
    int t, w, x;
}p[maxn];
int q, dp[maxn], a[maxn], b[maxn];
bool cmp(node a, node b);
int lowbit(int x);
int query(int x);
void Update(int x, int y, int n);

int main()
{
    int n, m, i, j, k, ans = 0;
    scanf("%d %d %d", &n, &m, &q);
    for(i=1;i<=m;i++){
        scanf("%d %d %d", &p[i].t, &p[i].w, &p[i].x);
        a[i] = p[i].t*q+p[i].x;
    }
    sort(a+1, a+1+m);
    sort(p+1, p+1+m, cmp);
    for(i=1;i<=m;i++){
        int pos = lower_bound(a+1, a+1+m, p[i].t*q+p[i].x)-a;
        dp[i] = p[i].w + query(pos);
        ans = max(ans, dp[i]);
        Update(pos, dp[i], m);
    }
    printf("%d\n", ans);
    return 0;
}

bool cmp(node a, node b)
{
    if(a.t*q-a.x != b.t*q-b.x)return a.t*q-a.x < b.t*q-b.x;
    else return a.t*q+a.x<b.t*q+b.x;
}

int lowbit(int x)
{
    return x&-x;
}

void Update(int x, int y, int n)
{
    for(int i=x;i<=n;i+=lowbit(i))
        b[i] = max(b[i], y);
}

int query(int x)
{
    int mx = 0;
    for(int i=x;i>0;i-=lowbit(i))
        mx = max(b[i], mx);
    return mx;
}
