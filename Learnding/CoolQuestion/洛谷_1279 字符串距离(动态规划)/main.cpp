//DP
//有两个字符串，字符串可以在任意补空字符，任意字母与空格
//的代价为k，字母之间代价为两字母的差，求补任意空格使
//两串对应的代价和最小
//题解：考虑动态规划，dp[i][j]代表第一个串的第i个字符与
//第二个串的第j个字符对应，状态转移： 
//dp[i][j]可以由dp[i-1][j]+i对应空格，dp[i][j-1]+j对应空格
//dp[i-1][j-1]+i,j对应，dp[i-1][j-1]+i,j分别对应一个空格转移
//所以dp[i][j]=min{dp[i-1][j]+k,dp[i][j-1]+k
//     dp[i-1][j-1]+abs(s1[i]-s2[j]),dp[i-1][j-1]+k+k}
//题目链接：https://www.luogu.org/problem/P1279 
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
const int maxn = 4020;
const int mod = 998244353;
char str1[maxn], str2[maxn];
int dp[maxn][maxn];

int main()
{
	int len1, len2, i, j, k;
	scanf(" %s %s %d", str1+1, str2+1, &k);
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	len1 = strlen(str1+1), len2 = strlen(str2+1);
	for(i=1;i<=len1;i++)
		dp[i][0] = dp[i-1][0]+k;
	for(i=1;i<=len2;i++)
		dp[0][i] = dp[0][i-1]+k;
	for(i=1;i<=len1;i++)
		for(j=1;j<=len2;j++)
		{
			//i，j可以考虑i,j分别对应空格，i,j同时对应
			//空格，i,j相互对应进行状态转移 
			dp[i][j] = min(dp[i][j-1]+k, dp[i-1][j]+k);
			dp[i][j] = min(dp[i][j], dp[i-1][j-1]+min(2*k, abs((int)str1[i]-str2[j])));
		}
	printf("%d\n", dp[len1][len2]);
	return 0;
}
