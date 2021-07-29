/*********************************************************
状压dp+容斥原理

有一个n*m的地图,每个点都有一个1~n*m间高度值，且每个点的高度值不同，
如果一个点的高度值小于周围所有点，则称其为谷底，地图上将该点标记为'X',
否则则将地图上该点标记为'.'。

思路：首先考虑对于原地图，可以发现谷底的数量其实是有限的(最多9个)，而且
谷地之间是不能相邻的。所以需要先检查原图是否合法。对于合法的图，考虑从
小到大往图里填高度。对于一个高度，可以考虑填在谷地，叶可以考虑填在空地，
但有限制，设数组dp[i][j]，i表示将要填入的数字，j代表每个谷底是否已经
赋值的状态(状压dp)，设cnt=谷地数量。
对于i+1这个高度，可以考虑赋给未赋过值的谷底，此时dp[i+1][j|(1<<k)]+=dp[i][j]
也可以考虑赋给非谷地，总共有n*m-cnt种选择，但这之中有一些点是不合适的，
比如已经赋过值的点，和未赋过值的谷地的周边(如果给分配在未赋值的谷地周边)，
那之后谷地无论如何高度都比它高，那么那个谷地就不是谷地了。
综上考虑，赋过非谷底dp[i+1][j]+= dp[i][j]*(pos-i+mou)
其中pos为j状态下其能放的位置，mou表示j状态下已放过的山谷的数量，

但如果仅是这样考虑显然会多统计一些情况，就是没有保证非谷地一定是非谷地，
所以需要将这些减去，考虑容斥原理，将这些情况减去。具体实现，可以dfs，将
一些非谷地在合法的前提下变为谷地，然后减去或加上这样的情况数量即可。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=5834
*************************************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
const int mod = 772002;
char str[10][10], st[10][10];
int n, m, dx[8]={-1,-1,-1,0,0,1,1,1}, dy[8]={1,0,-1,1,-1,-1,0,1};
int pos[1020], x[10], y[10], mou[1020];
LL ans, dp[30][1020];
bool check();
LL solve(int num);
void dfs(int step, int num);

int main()
{
	int z=1, i, j;
	while(~scanf("%d %d", &n, &m))
	{
		for(i=0;i<n;i++)
			scanf(" %s", str[i]);
		if(!check())
			printf("Case #%d: 0\n", z);
		else{
			ans = 0LL;
			dfs(0, 0);
			printf("Case #%d: %lld\n", z, ans);
		}
		z++;
	}
	return 0;
}

bool check()
{
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(str[i][j] == 'X')
			for(int k=0;k<8;k++){
				int nx = i+dx[k], ny = j+dy[k];
				if(nx>=0 && nx<n && ny>=0 && ny<m && str[nx][ny] == 'X')
					return false;
			}
	return true;
}

LL solve(int num)
{
	int i, j, k, ks=n*m, kn, cnt = 0;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			if(str[i][j] == 'X'){
				x[cnt] = i, y[cnt] = j;
				cnt++;
			}
	kn = 1<<cnt;
	memset(st, '.', sizeof(st));
	for(i=0;i<kn;i++){
		mou[i] = 0;
		//统计j状态已放过的谷底的数目
		for(j=0;j<cnt;j++)
			if( !(i&(1<<j)))st[x[j]][y[j]] = 'Y';
			else mou[i]++;
		//求'.'能放的位置，即不在空白的谷底的周围的空地的数量
		pos[i] = ks-cnt;
		for(int a1=0;a1<n;a1++)
			for(int a2=0;a2<m;a2++){
				//如果一个非空地周围是一个未放过的谷地，则不能放在这个位置
				if(str[a1][a2]=='X')continue;
				for(k=0;k<8;k++){
					int nx = a1+dx[k], ny=a2+dy[k];
					if(nx>=0 &&nx<n &&ny>=0 &&ny<m && st[nx][ny] == 'Y'){
						pos[i]--;break;
					}
				}
			}
		for(j=0;j<cnt;j++)
			if( !(i&(1<<j)))st[x[j]][y[j]] = '.';
	}
	for(i=0;i<=ks;i++)
		for(j=0;j<=kn;j++)
			dp[i][j] = 0;
	/*for(i=0;i<kn;i++)
		printf("%d %d %d\n", i, pos[i], mou[i]);
	printf("\n");*/
	dp[0][0] = 1;
	for(i=0;i<ks;i++)
		for(j=0;j<kn;j++){
			if(!dp[i][j])continue;
			for(k=0;k<cnt;k++)
				if(!(j&(1<<k)))
					dp[i+1][j|(1<<k)] = (dp[i+1][j|(1<<k)]+dp[i][j])%mod;
			//pos[j]-i+mou[j]表示可以放的位置数量，减去已经放过的数量
			//再加上放在谷底的数的数量
			dp[i+1][j] = (dp[i+1][j] + dp[i][j]*(pos[j]-i+mou[j]) % mod)%mod;
		}
	return dp[ks][kn-1];
}
//容斥求状态数
void dfs(int step, int num)
{
	if(step == n*m){
		if(num%2==0)ans = (ans + solve(num))%mod;
		else ans = (ans-solve(num)+mod)%mod;
		return ;
	}
	int i, x = step/m, y = step%m;
	for(i=0;i<8;i++)
	{
		int nx = x+dx[i], ny = y+dy[i];
		if(nx>=0 && nx<n && ny>=0 && ny<m && str[nx][ny] == 'X')break;
	}
	if(i==8 && str[x][y] != 'X'){
		str[x][y] = 'X';
		dfs(step+1, num+1);
		str[x][y] = '.';
	}
	dfs(step+1, num);
}