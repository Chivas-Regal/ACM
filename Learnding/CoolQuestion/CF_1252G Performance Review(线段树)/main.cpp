/********************************************* 
线段树
原本有一组数(第一个数为Randall)，有m次更换，每次更换会将那组数中最低的k
个数淘汰，同时会放新的k个数放进去。有q次更改，每次更改
会将其中的一个数更换为另一个数，问更改后，经过m次替换，
Randall是否还在数组中。(更改相互关联)
题解：因为询问的是Randall的状态，而每次淘汰只会淘汰最低的k个数，
所以可以只考虑Randall在每组数里的排名(每次替换视为一组新数)，
维护一个数组a,a[i]表示Randall在第i次替换后有多少个比他小的
(显然没必要关心比Randall大的)，如果所有的a[i]都大于等于0，则说明
Randall不会被淘汰(比他小的都没淘汰完)。
对于q次更改，因为只关心Randall的排名，所以只需要关心以下两种情况：
(设nb为原本的数，ng为更改后的数，randall为Randall的数) 
1. nb<randall && ng>randall, 一个原本比Randall小的数变的比Randall大，
		则之后Randall的排名都下降1，将此次后面的a[i]全部减1；
2. nb>randall && ng<randall, 一个原本比Randall大的数变得比Randall大，
		则之后Randall的排名会上升1，将此次后面的a[i]全部加1；
对所有的输入，求初始的a[i]，然后用线段树维护更改即可。 
PS：1252的K题是线段树维护矩阵，暑期的网络赛出过，听好
的一道题，题解就不写了，只需要重载下运算符就好了 
题目链接：https://codeforces.com/problemset/problem/1252/G
***********************************************/ 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<deque>
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
const int mod = 1000000007;
int a[maxn], p[maxn*4], lz[maxn*4];
vector<int> g[maxn];
void pushup(int k);
void pushdown(int k);
void creat(int l, int r, int k);
void Update(int l, int r, int al, int ar, int x, int k);

int main()
{
	//ra:Randall的值，num比ra小的数的数量 
	int ra, n, m, q, i, j, k, num = 0;
	scanf("%d %d %d", &n, &m, &q);
	scanf("%d", &ra);
	for(i=2;i<=n;i++)
	{
		scanf("%d", &j);
		if(j<ra)num++;
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d", &j);
		//淘汰j个数 
		a[i] = num-j;
		num -= j;
		//下标从1开始，0位填充0 
		g[i].push_back(0);
		while(j--)
		{
			scanf("%d", &k);
			g[i].push_back(k);
			if(k<ra)num++;
		}
	}
	creat(1, m, 1);
	while(q--)
	{
		int z, x, y;
		scanf("%d %d %d", &x, &y, &z);
		//如果一个比ra大的数变为比ra小的数，则后面全部加1 
		if(g[x][y] > ra && z<ra)
			Update(1, m, x+1, m, 1, 1);
		//如果一个比ra小的数变为比让大的数，则后面全部减1 
		else if(g[x][y] < ra && z>ra)
			Update(1, m, x+1, m, -1, 1);
		g[x][y] = z;
		if(p[1] < 0)printf("0\n");
		else printf("1\n");
	}
	return 0;
}

void creat(int l, int r, int k)
{
	lz[k] = 0;
	if(l == r)
	{
		p[k] = a[l];
		return;		
	}
	int mid=(l+r)/2;
	creat(l, mid, 2*k);
	creat(mid+1, r, 2*k+1);
	pushup(k);
}

void pushup(int k)
{
	p[k] = min(p[2*k], p[2*k+1]);
}

void pushdown(int k)
{
	if(lz[k])
	{
		lz[2*k] += lz[k], lz[2*k+1] += lz[k];
		p[2*k] += lz[k], p[2*k+1] += lz[k];
		lz[k] = 0;
	}
}

void Update(int l, int r, int al, int ar, int x, int k)
{
	if(al > ar)return;
	if(l == al && r == ar)
	{
		p[k] += x;
		lz[k] += x;
		return;
	}
	pushdown(k);
	int mid = (l+r)/2;
	if(ar <= mid)
		Update(l, mid, al, ar, x, 2*k);
	else if(al > mid)
		Update(mid+1, ar, al, ar, x, 2*k+1);
	else
		Update(l, mid, al, mid, x, 2*k),
		Update(mid+1, r, mid+1, r, x, 2*k+1);
	pushup(k);
}
