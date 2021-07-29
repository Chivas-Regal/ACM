/***************************************************************************
DP

初始位置在(0,0)，在点(x0,y0)有一个炸弹，有n个向量(xi,yi)，对于每个向量可以从(x,y)->(x+xi,y+yi);
可以任意调整向量的顺序，并且可以将(xi,yi)变为(-xi,-yi)。求n步移动完成后，最大化与炸弹的距离。

思路：我觉得这题是贪心，可惜它不是。可以发现的是向量的顺序并不影响最终结果，所以关键在于
向量是否需要向反方向移动的问题。
设置数组dp[i][j][k],代表考虑第i个向量后，横坐标为j时，最大最小的y坐标，k=0或1，分别代表最大
最小的y坐标。因为会有负的坐标，所以将所有坐标偏移(10000,10000)，方便及时。然后DP就完事了。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=4216
********************************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<set>
#include<queue>
#include<stack>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, string> P;
const int maxn = 200100;
const int mod = 1000000007;
int x[maxn], y[maxn];
int dp[120][20100][2];
double dis(int a1, int b1, int a2, int b2);

int main()
{
	int t, n, i, j, x0, y0, mid = 10000;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		scanf("%d %d %d", &n, &x0, &y0);
		x0+=mid, y0+=mid;
		for(i=0;i<=n;i++)
			memset(dp[i], -1, sizeof(dp[i]));
		dp[0][mid][0] = dp[0][mid][1] = mid;
		for(i=1;i<=n;i++)
			scanf("%d %d", &x[i], &y[i]);
		for(i=1;i<=n;i++)
			for(j=0;j<=mid+mid;j++)
				if(dp[i-1][j][0]>=0){
					if(dp[i][j+x[i]][0] == -1){
						dp[i][j+x[i]][0] = dp[i-1][j][0]+y[i];
						dp[i][j+x[i]][1] = dp[i-1][j][1]+y[i];
					}
					else{
						dp[i][j+x[i]][0] = max(dp[i][j+x[i]][0], dp[i-1][j][0]+y[i]);
						dp[i][j+x[i]][1] = min(dp[i][j+x[i]][1], dp[i-1][j][1]+y[i]);
					}

					if(dp[i][j-x[i]][0] == -1){
						dp[i][j-x[i]][0] = dp[i-1][j][0]-y[i];
						dp[i][j-x[i]][1] = dp[i-1][j][1]-y[i];
					}
					else{
						dp[i][j-x[i]][0] = max(dp[i][j-x[i]][0], dp[i-1][j][0]-y[i]);
						dp[i][j-x[i]][1] = min(dp[i][j-x[i]][1], dp[i-1][j][1]-y[i]);
					}
				}
		double ans = 0;
		for(i=0;i<=mid+mid;i++){
			if(dp[n][i][0] != -1)ans = max(ans, dis(x0, y0, i, dp[n][i][0]));
			if(dp[n][i][1] != -1)ans = max(ans, dis(x0, y0, i, dp[n][i][1]));
		}
		printf("Case %d: %.3f\n", z, ans);
	}
	return 0;
}

double dis(int a1, int b1, int a2, int b2)
{
	return sqrt((a1-a2)*(a1-a2)+(b1-b2)*(b1-b2));
}