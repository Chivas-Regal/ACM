/***************************************************************
动态规划

n棵树，每棵树上有ai个红果实和bi个蓝果实。有可以装k个果实的篮子，一个篮子只能
放同种颜色或同一棵树上的果实。求最多可以放满多少个篮子？

思路：显然大多数篮子内的果实都是同颜色的，最多只有n个篮子内的果实是不同色的。
所以需要考虑每棵树不同颜色的那个篮子的组成。
设dp[i][j]为考虑第i棵树果实装完后剩下的红果实数量为j能装满的最大篮子数。
(蓝果实呢？设dp[i][j][z]，z代表剩余蓝果实的话，复杂度为500^4，显然会超时，
实际上一个j对应的剩余蓝果实数量是唯一的，等于 果实总数-dp[i][j]*k-j)。

状态转移：设第i棵树之前的红蓝果实总数为sum；
依次枚举不同颜色的那个篮子的组成，由s1个红果实和k-s1个蓝果实组成。
则考虑之前的剩余，剩余未装篮的红果实有num1 = j+a[i]-s1个，为装篮的
蓝果实数量为num2 = b[i]-(k-s1)+sum-dp[i][j]*k-j。

所以递推式为
dp[i+1][num1%k] = max(dp[i+1][num1%k], dp[i][j]+1+num1/k+num2/k);

然后考虑一下s1=0的情况即可。

取dp[i][j]最大值即为所求。

题目链接：http://codeforces.com/problemset/problem/1348/E
***************************************************************/
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
const int maxn = 520;
const int mod = 1000000007;
LL dp[maxn][maxn];
int a[maxn], b[maxn];

int main()
{
    int n, k, i, j, k2, s1;
    LL sum = 0, mx = 0;
    memset(dp, -1, sizeof(dp));
    scanf("%d %d", &n, &k);
    k2 = 2*k;
    for(i=0;i<n;i++)
        scanf("%d %d", &a[i], &b[i]);
    dp[0][0] = 0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<k;j++)
        if(dp[i][j]>=0){
            int b1 = sum-dp[i][j]*k-j;
            for(s1=1;s1<=a[i] && s1<k;s1++)
            if(b[i]+s1>=k)
            {
                int b2 = b1+b[i]-(k-s1);
                int a2 = j+a[i]-s1;
                dp[i+1][a2%k] = max(dp[i+1][a2%k], dp[i][j]+b2/k+a2/k+1);
            }
            dp[i+1][(j+a[i])%k] = max(dp[i+1][(j+a[i])%k], dp[i][j]+(j+a[i])/k+(b1+b[i])/k);
        }            
        sum += a[i]+b[i];
    }
    for(i=0;i<=n;i++)
        for(j=0;j<=k;j++)
            mx = max(dp[i][j], mx);
    printf("%I64d\n", mx);
    return 0;
}