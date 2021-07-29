//dfs，记忆化搜索 
//因起始点不确定，需要把每个点都作为起始点进行搜索
//搜索完成后将得到的值赋给状态数组，数组中的值即为从此点开始，
//最多可以滑行多少步，当从其他点滑行至已赋值的点，直接返回 
//数组中的值。 
// http://poj.org/problem?id=1088
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;
typedef pair<int,int> P;
typedef long long int ll;
int m, n, a[102][102], dp[102][102];
int dx[4]={-1,0,1,0}, dy[4]={0,-1,0,1};
int dfs(int x, int y);

int main()
{
	int num, i, j, maxi, maxj, maxx = -1;
	memset(dp, -1, sizeof(dp));
	scanf("%d %d", &m, &n);
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			scanf("%d", &a[i][j]);
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			//将得到的值存入数组 
			dp[i][j] = dfs(i, j);
			/*for(int e=0;e<m;e++)
			{
				for(int f=0;f<n;f++)
					printf("%d ", dp[e][f]);
				printf("\n");
			}
			printf("\n");*/ 
		}
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			maxx = max(dp[i][j], maxx);
	/*for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
			printf("%d ", dp[i][j]);
		printf("\n");
	}*/
		
	printf("%d\n", maxx);
	return 0;
}

int dfs(int x, int y)
{
	//maxx初始化为1，如果在(x,y)点无处可走，返回1 
	int i, nx, ny, maxx = 1;
	//如果该点已经搜索过，直接返回
	if(dp[x][y] != -1)
	{
		return dp[x][y];
	}
	for(i=0;i<4;i++)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		//如果可以下滑，搜索点(nx,ny)，将其返回的值加1 
		if(nx>=0 && nx<m && ny>=0 && ny<n && a[nx][ny] < a[x][y])
			maxx = max(dfs(nx,ny)+1, maxx);
	}
	return maxx;
 } 
