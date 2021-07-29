//Ī���㷨+ST��
//��һ�����ݣ����ѯ�ʣ�[l,r]�������Ƿ�����
//�ж�[l,r]������Ԫ���Ƿ������������������ڵ�
//���ֵ����Сֵ��Ȼ���������ڲ�ֵͬ�����ĸ���
//������ֵ-��Сֵ+1�������䲻ֵͬ�ĸ�����������
//����ͨ��ST����O(1)��ʱ������������Сֵ
//Ī���㷨��ѯ�ʽ��зֿ����򼴿�
//Ī���㷨���ӣ�https://www.cnblogs.com/CsOH/p/5904430.html
//ST��https://www.cnblogs.com/YSFAC/p/7189571.html 
//��Ŀ���ӣ� http://acm.hdu.edu.cn/showproblem.php?pid=6483
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
		//��n���ռ�ֳ����ɿ飬ÿ�鳤sqrt(n) 
		len = (int)sqrt(n);
		for(i=1;i<=n;i++)
		{
			scanf("%d", &a[i]);
			b[i] = a[i];
		}
		//������ɢ����Ԥ�����a[i]������ɢ����λ�� 
		//���账����ֻᳬʱ 
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
			//��ǰһ��[l,r]�������Ƴ���ǰ������ 
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
			//st���ѯ 
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
//Ī���㷨����ѯ�ʰ����������ڿ����������ͬһ�飬������������ 
bool cmp(node a, node b)
{
	if(a.clk != b.clk)return a.l < b.l;
	return a.r < b.r;
}
//Ԥ����ST��[i][j]�����i��ʼ������Ϊ2^j���ݵ����������(С)ֵ�Ƕ��� 
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
