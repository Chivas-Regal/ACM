/******************************************
概率DP
一个由n个位置的环，初始在1号位，共走m步，每步可能随机向左或向右
走w步，求w步后，在[l,r]位置内的概率
题解：对概率dp,对于当前在i位置，概率为
dp[id][i] = 0.5*dp[id-1][(i+w)%n]+0.5*dp[id-1][(i-w+n)%n];
设置两个数组，不断的暴力，滚动数组即可。
PS：这题时间卡的特别紧，多加一次取余操作都会超时。
题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=4576
*******************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1000010;
const int mod = 1000000007;
double dp[2][220];
int TO(int j, int n);

int main()
{
    int n, m, l, r, i, j, k, id, up;
    double sum1, sum2;
    while(scanf("%d %d %d %d", &n, &m, &l, &r),n||m||l||r)
    {
        l--, r--;
        id = 1;
        for(i=0;i<n;i++)dp[id][i] = 0;
        dp[id][0] = 1;
        while(m--)
        {
            scanf("%d", &up);
            for(i=0;i<n;i++)
                dp[id^1][i] = 0.5*dp[id][(i+up)%n]+0.5*dp[id][(i-up+n)%n];
            id ^= 1;
        }
        sum2 = 0;
        for(i=l;i<=r;i++)
            sum2+=dp[id][i];
        printf("%.4f\n", sum2);
    }
    return 0;
}