/*******************************************************************************
动态规划

长度为n的排列，如果相邻的两者，前者小于后者，则为'I',如果前者大于后者，则为'D'，如果未知
，则为'?'。给出字符串，求满足该字符串的排列有多少个。

思路：动态规划。dp[i][j]代表第i位以j结尾的方案数。这里的大小其实可以理解为相对大小，
对于j之前的方案，如果大于等于j，则将其+1，这样就是一个1~i的全排列。
对于'I'，dp[i][j] = dp[i-1][1]+dp[i-1][2]+...+dp[i-1][j-1];
对于'D'，dp[i][j] = dp[i-1][j]+dp[i-1][j+1]+...+dp[i-1][i-1];
对于'?'，dp[i][j] = dp[i-1][1]+dp[i-1][2]+...+dp[i-1][i-1];
利用前缀和优化，复杂度为n^2

题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827368997
****************************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 1020;
const int mod = 1000000007;
LL dp[maxn][maxn], sum[maxn][maxn];
char str[maxn];

int main()
{
    int len, i, j, k;
    while(~scanf(" %s", str+2))
    {
        len = strlen(str+2);
        len++;
        dp[1][1] = sum[1][1] = 1;
        for(i=2;i<=len;i++)
        {
            for(j=1;j<=i;j++)
            {
                if(str[i] == 'I')
                    dp[i][j] = sum[i-1][j-1];
                else if(str[i] == 'D')
                    dp[i][j] = (sum[i-1][i-1]-sum[i-1][j-1])%mod+mod;
                else 
                    dp[i][j] = sum[i-1][i-1];
                dp[i][j]%=mod;
            }
            sum[i][0] = 0;
            for(j=1;j<=i;j++)
                sum[i][j] = (sum[i][j-1]+dp[i][j])%mod;
        }
        printf("%lld\n", sum[len][len]);
    }
    return 0;
}