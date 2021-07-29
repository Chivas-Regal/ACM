//状压dp
//dp[i][j],j二进制下1表示此为已被匹配
//题目链接：http://lightoj.com/volume_showproblem.php?problem=1011
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
const int maxn = 210;
int dp[17][(1<<16)+4];

int main()
{
	int t, n, i, j, k, a[18][18];
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		memset(dp, -1, sizeof(dp));
		scanf("%d", &n);
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			scanf("%d", &a[i][j]);
		for(i=0;i<n;i++)
			dp[0][1<<i] = a[0][i];
		for(i=0;i<n-1;i++)
			for(j=0;j<1<<n;j++)
			//如果这种情况出现过 
				if(dp[i][j] != -1)
				{
					for(k=0;k<n;k++)
					if((j&1<<k) == 0)//j中第k位未被匹配过
					//匹配最大值 
						dp[i+1][j|1<<k] = max(dp[i+1][j|1<<k], dp[i][j]+a[i+1][k]);
				}
		printf("Case %d: %d\n", z, dp[n-1][(1<<n)-1]);
	}
	return 0;
}
