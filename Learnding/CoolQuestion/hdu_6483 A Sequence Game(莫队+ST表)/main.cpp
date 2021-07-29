//莫队算法+ST表
//有一组数据，多个询问，[l,r]内数据是否连续
//判断[l,r]内所有元素是否连续，可以求区间内的
//最大值和最小值，然后求区间内不同值的数的个数
//如果最大值-最小值+1等于区间不同值的个数，即连续
//可以通过ST表，在O(1)的时间内求出最大最小值
//莫队算法对询问进行分块排序即可
//莫队算法链接：https://www.cnblogs.com/CsOH/p/5904430.html
//ST：https://www.cnblogs.com/YSFAC/p/7189571.html 
//题目链接： http://acm.hdu.edu.cn/showproblem.php?pid=6483
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
typedef unsigned long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
struct node
{
	int l, r, id, clk;
}g[maxn];
int len, a[maxn], ans[maxn], d[maxn];
int b[maxn], c[maxn], si[maxn][20], sx[maxn][20];
void st(int n);
bool cmp(node a, node b);


int main()
{
	int t, n, m, q, l, r, i, j;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d", &n, &m);
		//将n个空间分成若干块，每块长sqrt(n) 
		len = (int)sqrt(n);
		for(i=1;i<=n;i++)
		{
			scanf("%d", &a[i]);
			b[i] = a[i];
		}
		//数据离散化，预处理出a[i]所在离散化的位置 
		//不予处理二分会超时 
		sort(b+1, b+n+1);
		for(i=1;i<=n;i++)
		{
			d[i] = lower_bound(b+1, b+1+n, a[i])-b;
			c[i] = 0;
		}
		st(n);
		for(i=0;i<m;i++)
		{
			scanf("%d %d", &g[i].l, &g[i].r);
			g[i].id = i;
			g[i].clk = g[i].l / len;
		}
		sort(g, g+m, cmp);
		l = 1, r = 0;
		int un = 0;
		for(i=0;i<m;i++)
		{
			//有前一个[l,r]区间结果推出当前区间结果 
			if(r<g[i].r)
			{
				while(r<g[i].r)
				{
					r++;
					c[d[r]]++;
					if(c[d[r]] == 1)
						un++;
				}
			}
			else if(r>g[i].r)
			{
				while(r>g[i].r)
				{
					c[d[r]]--;
					if(c[d[r]] == 0)un--;
					r--;
				}
			}
			if(l>g[i].l)
			{
				while(l>g[i].l)
				{
					l--;
					c[d[l]]++;
					if(c[d[l]] == 1)un++;
				}
			}
			else if(l<g[i].l)
			{
				while(l<g[i].l)
				{
					c[d[l]]--;
					if(c[d[l]] == 0)un--;
					l++;
				}
			}
			//st表查询 
			int k = log(1.0*g[i].r-g[i].l+1)/log(2.0);
			int ans1 = max(sx[g[i].l][k], sx[g[i].r-(1<<k)+1][k]);
			int ans2 = min(si[g[i].l][k], si[g[i].r-(1<<k)+1][k]);
			if(ans1-ans2+1 == un)
				ans[g[i].id] = 1;
			else
				ans[g[i].id] = 0;
		}
		for(i=0;i<m;i++)
		if(ans[i])printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
//莫队算法，将询问按左区间所在块排序，如果在同一块，则按右区间排序 
bool cmp(node a, node b)
{
	if(a.clk != b.clk)return a.l < b.l;
	return a.r < b.r;
}
//预处理ST表，[i][j]代表从i开始，长度为2^j次幂的区间内最大(小)值是多少 
void st(int n)
{
	int i, j;
	for(i=1;i<=n;i++)
		si[i][0] = sx[i][0] = a[i];
	for(j=1;j<19;j++)
	for(i=1;i<=n;i++)
	if(i+(1<<j)-1<=n)
	{
		si[i][j] = min(si[i][j-1], si[i+(1<<(j-1))][j-1]);
		sx[i][j] = max(sx[i][j-1], sx[i+(1<<(j-1))][j-1]);
	}
	else break;
}
