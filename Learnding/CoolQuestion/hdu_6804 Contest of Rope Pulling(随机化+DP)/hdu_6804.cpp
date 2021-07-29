/*************************************************************************
随机化+动态规划

有两个班级，第一个班级有n个人，第二个班级有m个人。每个人有两个值，实力wi和精彩值vi。
需要选择从每个班若干个人(不能全选)进行拔河比赛，要求两个班选取人的实力和相等。求最大的精彩值。

思路：将第二个班的人转化为实力-wi，精彩值vi。再将两个班的人放一起，进行01背包即可。
不过wi的和可以达到1e6,如果直接DP，则复杂度过高。可以将所有数据随机排列，并且将wi
的和范围只考虑[-2e4, 2e4]。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=6804
************************************************************************/
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
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-6
   
using namespace std;
typedef long long LL;  
typedef pair<int, int> P;
const int maxn = 8020;
const int mod = 1000000007;
struct node{
    int w, v;
}p[maxn];
LL dp1[10*maxn], dp2[10*maxn];
LL solve(int n);

int main()
{
    int t, n, m, i, j, k;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &m);
        for(i=0;i<n;i++)
            scanf("%d %d", &p[i].w, &p[i].v);
        for(i=0;i<m;i++){
            scanf("%d %d", &p[i+n].w, &p[i+n].v);
            p[i+n].w *= -1;
        }
        LL ans = 0;
        for(i=0;i<=1;i++)
            ans = max(ans, solve(n+m));
        printf("%lld\n", ans);
    }
    return 0;
}

LL solve(int n)
{
    random_shuffle(p, p+n);
    random_shuffle(p, p+n);
    int mx = 80000;
    for(int i=0;i<=mx;i++)
        dp1[i] = dp2[i] = -1;
    dp1[40000] = dp2[40000] = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<=mx;j++){
            if(dp1[j]>=0 && j+p[i].w >=0 && j+p[i].w <= mx)
                dp2[j+p[i].w] = max(dp2[j+p[i].w], dp1[j]+p[i].v);
        }
        for(int j=0;j<=mx;j++)
            dp1[j] = dp2[j];
    }
    return dp1[40000];
}