//线段树 
//先将线段树中的值变为0，值的意义为在此区间已有多少元素
//当插入数a[i]时，先检查(a[i]+1,n)有多少个元素，即逆序数 
//http://acm.hdu.edu.cn/showproblem.php?pid=1394
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
#define INF 0x3f3f3f3f
  
using namespace std;
typedef long long int ll;
typedef pair<int,int> P;
typedef struct
{
	int l, r, n;
}node;
node p[50200];
int a[50200];
int purey(int l, int r, int k);
void creat(int l, int r, int k);
void insert(int i, int k);

int main()
{
	int n, i, sum, ans;
	while(scanf("%d", &n)!=EOF)
	{
		sum = 0;
		creat(1, n, 1);
		for(i=0;i<n;i++)
		{
			scanf("%d", &a[i]);
			sum += purey(a[i]+1, n, 1);
		//	printf("jiesu");
		//	printf("全集：%d %d\n", sum, p[3].n);
		}
		ans = sum;
		for(i=0;i<n;i++)
		{
			sum = sum - a[i] + n - 1 - a[i];
			ans = min(ans, sum);
		}
		printf("%d\n", ans);
	}
	return 0;
}

void creat(int l, int r, int k)
{
	p[k].l = l;
	p[k].r = r;
	p[k].n = 0;
	if(l == r)return;
	int mid = (l + r) / 2;
	creat(l, mid, 2*k);
	creat(mid+1, r, 2*k+1);
}

//更新i为已存在 
void insert(int i, int k)
{
	if(p[k].l == p[k].r && p[k].l == i)
	{
		p[k].n = 1;
		return;
	}
	int mid = (p[k].l + p[k].r) / 2;
	if(i <= mid)
		insert(i, 2*k);
	else
		insert(i, 2*k+1);
	p[k].n = p[2*k].n + p[2*k+1].n;
}

//查找区间(l,r)中有多少元素 
int purey(int l, int r, int k)
{
	//printf("k:%d %d %d ", l, r, k);
	if(p[k].l == l && p[k].r == r)
	{
		return p[k].n;
	}
	//if(p[k].l == p[k].r)return p[k].n;
	int mid = (p[k].l + p[k].r) / 2;
	if(r <= mid)
		return purey(l, r, 2*k);
	else if(l > mid)
		return purey(l, r, 2*k+1);
	else
		return purey(l, mid, 2*k)+purey(mid+1, r, 2*k+1);
}
