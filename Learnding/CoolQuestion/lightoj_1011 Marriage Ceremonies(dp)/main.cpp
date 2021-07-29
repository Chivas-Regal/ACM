//KM匹配
//模板题
//完全匹配，所有人都能有匹配对象 
//参考博客：https://www.cnblogs.com/Lanly/p/6291214.html 
// http://lightoj.com/volume_showproblem.php?problem=1011
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
const int maxn = 20;
int n, a[maxn][maxn], line[maxn], cx[maxn], cy[maxn];
int ux[maxn], uy[maxn];
bool Find(int x);
int km();

int main()
{
	int t, i, j, k;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		memset(cx, 0, sizeof(cx));
		memset(cy, 0, sizeof(cy));
		memset(line, 0, sizeof(line));
		scanf("%d", &n);
		for(i=1;i<=n;i++)
		{
			int d = 0;
			for(j=1;j<=n;j++)
			{
				scanf("%d", &a[i][j]);
				d = max(d, a[i][j]);
			}
			cx[i] = d;
		}
		int ans = km();
		printf("Case %d: %d\n", z, ans);
	}
	return 0;
}

int km()
{
	int i, j, k, ans;
	for(i=1;i<=n;i++)
	{
		while(true)
		{
			int d = INF;
			memset(ux, 0, sizeof(ux));
			memset(uy, 0, sizeof(uy));
			//能匹配则进行下一个匹配
			if(Find(i))break;
			//不能匹配，则继续“加边”,只考虑
			//增广路上的点中未加入的边 
			for(j=1;j<=n;j++)
			if(ux[j])
			for(k=1;k<=n;k++)
			if(!uy[k])d=min(d,cx[j]+cy[k]-a[j][k]);
			//所有都已被加入 
			if(d == INF)return -1;
			for(j=1;j<=n;j++)
			if(ux[j])
				cx[j] -= d;
			for(j=1;j<=n;j++)
			if(uy[j])
				cy[j] += d; 
		}
	}
	ans = 0;
	for(i=1;i<=n;i++)
	ans += a[line[i]][i];
	return ans;
}

bool Find(int x)
{
	ux[x] = 1;
	for(int j=1;j<=n;j++)
	{ 
		if(!uy[j] && cx[x]+cy[j] == a[x][j])
		{
			uy[j] = 1;
			if(line[j] == 0 || Find(line[j]))
			{
				line[j] = x;
				return true;
			}
		}
	}
	return false;
}
