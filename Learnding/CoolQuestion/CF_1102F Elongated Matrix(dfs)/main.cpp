//dfs+剪枝
//题目给你一个n*m的矩阵，你可以任意交换矩阵的行
//交换完成后按第一列第一个元素，第一列第二个元素
//....第二列第一行......的顺序将矩阵中的元素放到一个数组中
//k = min(abs(a[i]-a[i-1])),求k的最大值
//思路：总共最多有16行，根据题意不难想到将两行之间的差的最小绝对 
//值先求出来，然后就相当于16个元素全排列，不过需要
//额外注意的就是第一行与最后一行的问题，这个也需要预处理一下
//题目链接： http://codeforces.com/problemset/problem/1102/F
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<queue>
#include<cstring>
#include<map>
#include<iostream>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
int head, n, m, maxx, vis[20], a[20][10020], b[20][20], c[20][20];
void dfs(int step, int j, int mid);

int main()
{
	int i, j, k;
	maxx = 0;
	scanf("%d %d", &n, &m);
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			scanf("%d", &a[i][j]);
	//预处理处非首尾行的值 
	for(i=0;i<n;i++)
		for(j=0;j<i;j++)
		{
			int minn = 2147480000; 
			for(k=0;k<m;k++)
				minn = min(minn, abs(a[i][k]-a[j][k]));
			b[i][j] = b[j][i] = minn;
		}
	//预处理处第一行和最后一行的情况 
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(i == j)continue;
			int minn = 2147480000; 
			for(k=1;k<m;k++)
				minn = min(minn, abs(a[j][k]-a[i][k-1]));
			c[i][j] = minn;
		}
	//生成全排列 
	memset(vis, 0, sizeof(vis));
	for(i=0;i<n;i++)
	{
		head = i;
		vis[i] = 1;
		dfs(1, i, 2147480000);
		vis[i] = 0;
	}
	printf("%d\n", maxx);
	return 0;
}

void dfs(int step, int j, int ans)
{
	if(ans <= maxx)return;
	if(step == n)
	{
		//printf("head:%d %d\n", head, j);
		if(step>1)
		ans = min(ans, c[head][j]);
		else
		for(int i=1;i<m;i++)
			ans = min(ans, abs(a[0][i]-a[0][i-1]));
		maxx = max(ans, maxx);
		return;
	}
	for(int i=0;i<n;i++)
	{
		if(!vis[i])
		{
			vis[i] = 1;
			dfs(step+1, i, min(b[j][i], ans));
			vis[i] = 0;
		}
	}
}
