//dp
//可以将原串的任一连续子串乘以x(也可以不乘),求最大连续子段和
//结果所选的答案可以分为三段，前段和后段是没有乘x的，中段是
//乘x的，这三段包含的元素个数都可以为0，
//dp[i][0]为第i个元素作为前段部分能得到的最大值
//dp[i][1]为第i个元素作为中段部分能得到的最大值
//dp[i][2]为第i个元素作为后段部分能得到的最大值
//题目链接：http://codeforces.com/problemset/problem/1155/D 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<set>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 3000;
LL ans, a, dp[300100][3];

int main()
{
	int n, i, x;
	scanf("%d %d", &n, &x);
	for(i=1;i<=n;i++)
	{
		scanf("%I64d", &a);
		//作为前段元素只需考虑同为前段的部分 
		dp[i][0] = max(dp[i-1][0], 0LL)+a;
		//作为中段元素需考虑将连接作为前段、还是中段的前一个元素 
		dp[i][1] = max(0LL, max(dp[i-1][0], dp[i-1][1]))+a*x;
		//作为后段元素需考虑将前一个元素作为前段部分，中段部分或后段部分 
		dp[i][2] = max(0LL, max(dp[i-1][0], max(dp[i-1][1], dp[i-1][2])))+a;
		ans = max(ans, max(dp[i][0], max(dp[i][1], dp[i][2])));
	}
	printf("%I64d\n", ans);
	return 0;
}
