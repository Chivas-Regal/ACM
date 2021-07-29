/***************************************
动态规划
对于n*m的地图，有'.'代表空地，'R'代表石头，人在左上角
人可以往下或右走，目的地为右下角，人在走时可以把石头往
人走的方向推，但不能推出地图，求有多少种不同的路线到右下角
题解：显然考虑动态规划，dp[i][j]代表i，j到右下角有多少
种不同的路径，其中将dp[i][j]分为dx[i][j]和dy[i][j]，
分别代表(i,j)向下走和向右有多少种方法，不考虑石头的话，
显然		dx[i][j] = dx[i+1][j]+dy[i+1][j],
如果(i+1,j)处有石头，向下会把石头推向不能在推的位置k，
此时(i,j)向下到(k,j)，然后(k,j)向右走的那种方案显然是
不行的，但dx[i][j]计算时把上面那些路径计算上了，所以在
减去这种路径就行了
对于dy[i][j]也可以这样考虑
注意处理n=m=1的情况，还有此题没有起点为R的样例，如果有
下面的代码是错的(可能题目限制了把，我没看见那句)
 
题目链接：https://codeforces.com/contest/1247/problem/E
*****************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<deque>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 2020;
const int mod = 1000000007;
//dp[i][j][0]代表dx[i][j],dp[i][j][1]代表dy[i][j]
//cnt[i][j][0]代表第j列从下往上数到i，共有多少个石头 
LL dp[maxn][maxn][2], cnt[maxn][maxn][2];
char str[maxn][maxn];

int main()
{
	int n, m, i, j;
	scanf("%d %d", &n, &m);
	for(i=0;i<n;i++)
		scanf(" %s", str[i]);
	if(n == 1 && m == 1)
		printf("1");
	else if(str[n-1][m-1] == 'R' || str[0][0] == 'R')
		printf("0");
	else
	{
		//对"石头"求后缀和，以方便求上文的k 
		for(i=n-1;i>=0;i--)
			for(j=m-1;j>=0;j--)
			{
				cnt[i][j][0] = cnt[i+1][j][0]+(str[i][j] == 'R');
				cnt[i][j][1] = cnt[i][j+1][1]+(str[i][j] == 'R');
			}
		//计算边缘的信息 
		for(i=n-2;i>=0;i--)
			if(!cnt[i][m-1][0])dp[i][m-1][0] = 1;
		for(i=m-2;i>=0;i--)
			if(!cnt[n-1][i][1])dp[n-1][i][1] = 1;
		for(i=n-2;i>=0;i--)
			for(j=m-2;j>=0;j--)
			{
				//求(i,j)向下一步和向右一步有多少种不同的路径到(n,m) 
				dp[i][j][0] = (dp[i+1][j][0]+dp[i+1][j][1])%mod;
				//如果下面为石头减去不能到达的路径 
				if(str[i+1][j] == 'R')
					dp[i][j][0] = (dp[i][j][0]-dp[n-cnt[i+1][j][0]][j][1]+mod)%mod;
				dp[i][j][1] = (dp[i][j+1][0]+dp[i][j+1][1])%mod;
				if(str[i][j+1] == 'R')
					dp[i][j][1] = (dp[i][j][1]-dp[i][m-cnt[i][j+1][1]][0]+mod)%mod;
			}
		printf("%lld\n", (dp[0][0][0]+dp[0][0][1])%mod);
	}
	return 0;
}
