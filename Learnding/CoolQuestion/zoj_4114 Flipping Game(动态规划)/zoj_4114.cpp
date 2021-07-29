/*******************************************************************************
动态规划

有n个灯，每个灯对应一个开关，当按下开关后，灯若为开启(关闭)状态，则变为关闭(开启)状态。
共有k次操作，每一次必须选择m个开关按下。给出n个灯的最初状态和最后状态，求方案数。

思路：因为目标是将初始态变为最终态，所以只关心初始态与最终态有多少个位置不同即可。
设dp[i][j]代表进行i次操作后，有j个灯的状态与最终态不符。每次操作，枚举s，代表选择
s个与最终态不同的灯，m-s个与最终态相同的灯操作，操作后会有t=j-s+m-s个灯状态与最终态不同，
递推式如下
    dp[i+1][j-s+m-s] = dp[i+1][j-s+m-s]+C(j,s)*C(n-j,m-s)*dp[i][j](s>=0 && s<=min(m,j))
最后dp[k][0]即为方案数。 

题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827370509
*******************************************************************************/
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
const int maxn = 120;
const int mod = 998244353;
LL dp[maxn][maxn], C[maxn][maxn];
char s[maxn], t[maxn];

int main()
{
    int ca, n, m, i, j, k, tim; 
    C[1][0] = C[1][1] = C[0][0] = 1;
    for(i=2;i<=103;i++)
    {
        C[i][0] = C[i][i] = 1;
        for(j=1;j<i;j++)
            C[i][j] = (C[i-1][j]+C[i-1][j-1])%mod; 
    }
    scanf("%d", &ca);
    while(ca--)
    {
        scanf("%d %d %d", &n, &tim, &m);
        for(i=0;i<=tim;i++)
            memset(dp[i], 0, sizeof(dp[i]));
        scanf(" %s %s", s, t);
        int num = 0;
        for(i=0;i<n;i++)
            if(s[i] != t[i])num++;
        dp[0][num] = 1;
        for(i=0;i<tim;i++)
            for(j=0;j<=n;j++)
            if(dp[i][j])
            {
                for(k=0;k<=m;k++)
                    if(j>=k && n-j>=m-k)
                    {
                        int to = j-k + m-k;
                        dp[i+1][to] = (dp[i+1][to] + C[j][k]*C[n-j][m-k]%mod*dp[i][j]%mod)%mod;
                    }
            }
        printf("%lld\n", dp[tim][0]);
    }
    return 0;
}