//dp 
//背包思想，dp数组表示用k个硬币组成j值的个数
//http://acm.hdu.edu.cn/showproblem.php?pid=2069 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
 
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
ll dp[780][120];
int coin[5] = {50,25,10,5,1};

int main()
{
	int i, j, k, n;
	dp[0][0] = 1;
	//背包思想， 
	for(i=0;i<5;i++)
		for(j=0;j<=750;j++)
			for(k=0;k<=100;k++)
			if(j >= coin[i] && k > 0) 
				dp[j][k] += dp[j-coin[i]][k-1];	
	/*for(i=0;i<50;i++)
	{
		printf("%-2d:  ", i); 
		for(j=0;j<20;j++)
			printf("%lld ", dp[i][j]);
		printf("\n");
	}*/ 
	while(scanf("%d", &n)!=EOF)
	{
		int sum = 0;
		for(i=0;i<=100;i++)
			sum += dp[n][i];
		printf("%d\n", sum);
	}
	return 0;
 } 
