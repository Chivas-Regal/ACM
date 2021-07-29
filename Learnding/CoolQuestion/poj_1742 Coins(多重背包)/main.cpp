//dp,多重背包
//dp数组的意义为第i个物品时，价值为j是i最多能剩几个 
//《挑战程序设计竞赛》P63
//参考博客: http://www.hankcs.com/program/cpp/poj-1742-coins.html
//题目链接: http://poj.org/problem?id=1742
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#include<iterator>
#include<queue>
#include<iostream>
#include<ctime>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
int dp[100010];

int main()
{
	int n, m, i, j, k, a[120], b[120];
	LL sum;
	while(scanf("%d %d", &n, &m), n||m)
	{
		memset(dp, -1, sizeof(dp));
		sum = 0;
		dp[0] = 1;
		for(i=0;i<n;++i)scanf("%d", &a[i]);
		for(i=0;i<n;++i)scanf("%d", &b[i]);
		for(i=0;i<n;++i)
		{
			for(j=0;j<=m;j++)
			{
				//如果dp[j]>=0则代表之前已经可以
				//达到这种值，所以可以剩下b[i]个 
				if(dp[j]>=0)
				{
					dp[j] = b[i];
				}
				//如果a[i]太大了，或者j-a[i]并不能在之前 
				//的状态中出现，则j也无法出现 
				else if(j<a[i] || dp[j-a[i]]<=0)
				{
					dp[j] = -1;
				}
				//如果之前没有到达过此状态，且也可以正常放置
				//则将i的数量减少一个 
				else 
					dp[j] = dp[j-a[i]]-1;
			}
		}
		for(i=1;i<=m;i++)if(dp[i]>=0)sum++;
		printf("%d\n", sum);
	}
	return 0;
}
