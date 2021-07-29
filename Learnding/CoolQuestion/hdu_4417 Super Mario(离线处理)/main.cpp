//�߶������ߴ���
//������[l,r]��С�ڵ���h��ֵ�ж��� 
//�ܹ�m��ѯ�ʣ��޸��ģ����Խ����е�ѯ�ʴ洢�ڽṹ����
//Ȼ��h��С�����������Ƚ��ÿ������ڴ���˴�ѯ��֮ǰ
//�����и߶�С�ڵ���h�ı߶��������У�Ȼ��洢�������
//��Ŀ���ӣ� http://acm.hdu.edu.cn/showproblem.php?pid=4417
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<set>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100010;
struct node
{
	int l, r, sum;
}p[maxn*4];
struct pro
{
	int l, r, h, num;
}q[maxn];
int a[maxn], ans[maxn];
P b[maxn];
int query(int l, int r, int k);
void update(int k, int x);
void creat(int l, int r, int k);
bool cmp1(pro a, pro b);
bool cmp2(P a, P b);

int main()
{
	int t, n, m, i, j, k, l;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		scanf("%d %d", &n, &m);
		//���յ��߶��� 
		creat(1, n, 1);
		for(i=1;i<=n;i++)
		{
			scanf("%d", &a[i]);
			b[i].first = a[i], b[i].second = i;
		}
		sort(b+1, b+1+n, cmp2);
		for(i=0;i<m;i++)
		{
			scanf("%d %d %d", &q[i].l, &q[i].r, &q[i].h);
			q[i].l++, q[i].r++;
			q[i].num = i;
		}
		sort(q, q+m, cmp1);
		l = 1;
		for(i=0;i<m;i++)
		{
			//�����и߶�С�ڵ���h�ļ������� 
			while(l<=n && b[l].first<=q[i].h)
			{
				update(1, b[l].second);
				l++;
			}
			ans[q[i].num] = query(q[i].l, q[i].r, 1);
		}
		printf("Case %d:\n", z);
		for(i=0;i<m;i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}

bool cmp1(pro a, pro b)
{
	return a.h < b.h;
}

bool cmp2(P a, P b)
{
	return a.first<b.first;
}

void creat(int l, int r, int k)
{
	p[k].l = l, p[k].r = r, p[k].sum = 0;
	if(l==r)return;
	int mid = (l+r)>>1;
	creat(l, mid, 2*k);
	creat(mid+1, r, 2*k+1);
}

void update(int k, int x)
{
	p[k].sum++;
	if(p[k].l == p[k].r)return;
	int mid = (p[k].l + p[k].r)>>1;
	if(x<=mid)
		update(2*k, x);
	else
		update(2*k+1, x);
}

int query(int l, int r, int k)
{
	if(p[k].l == l && p[k].r == r)
		return p[k].sum;
	int mid = (p[k].l + p[k].r)>>1;
	if(r<=mid)
		return query(l, r, 2*k);
	else if(l>mid)
		return query(l, r, 2*k+1);
	else
		return query(l, mid, 2*k)+query(mid+1, r, 2*k+1);
}
