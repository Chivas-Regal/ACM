//dfs
//一般搜索会将前进步数等作为条件，这题将转弯次数作为条件
//记录到达该点会经过几次转折，因为可能该点会在前面的搜索
//过程已赋值，但其实会有更少转折次数的方案，所以将
//b[nx][ny] > b[x][y]作为条件 
//http://acm.hdu.edu.cn/showproblem.php?pid=1175 
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
int m, n, num, a[1020][1020], b[1020][1020];
int x3, x2, y3, y2, answer;
int dx[4] = {-1,0,1,0}, dy[4] = {0,-1,0,1};
void dfs(int x, int y, int trup, int d);

int main()
{
	int q, i, j;
	while(scanf("%d %d", &m, &n), m!=0&&n!=0)
	{
		for(i=1;i<=m;i++)
			for(j=1;j<=n;j++)
				scanf("%d", &a[i][j]);
		scanf("%d", &q);
		while(q--)
		{
			scanf("%d %d %d %d", &x3, &y3, &x2, &y2);
			if(a[x3][y3] != a[x2][y2] || a[x3][y3]==0)
			{
				printf("NO\n");continue;
			}
			answer = 0;
			memset(b, -1, sizeof(b));
			dfs(x3, y3, 0, -1);
			if(answer)
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
	return 0;
}

void dfs(int x, int y, int trup, int d)
{
	if(x == x2 && y == y2)
	{
		answer = 1;return;
	}
	int i, nx, ny;
	for(int i=0;i<4 && answer==0;i++)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if(nx>=1 && nx<=m && ny>=1 && ny<=n && answer == 0 && (a[nx][ny] == 0 || nx == x2 && ny == y2))
		{
			if(d==-1 || d==i)
			{
				b[nx][ny] = trup;
				dfs(nx, ny, trup, i);
				if(answer)return;
			}
			else if(trup < 2 && (b[nx][ny] == -1 || b[nx][ny] > b[x][y]))
			{
				b[nx][ny] = min(b[nx][ny], trup);
				dfs(nx, ny, trup+1, i);
				if(answer)return;
			}
		} 
	}
}
