/*************************************************************
线段树

有一个排列，每一步可以交换两个相邻位置的数，现在需要求出对于每个k，使
排列存在子串1,2,3...k所需要移动的最少次数

思路：对于每个k可以看出答案可以分为两个部分，一个部分是将1,2,3...k移动
到相邻的位置，一个部分是将乱序的1,2,3...k调整为升序。
对于前面一部分，可以将小于等于k的数看为1，大于k的看做0，然后求前缀和pi，
那么对于所有为0的数，对答案的贡献为(pi,k-pi)。对于k，显然pi<k/2+1，应该
加上pi，pi>=k/2+1应该加上k-pi。所以对于每个k，需要求出第k/2+1个元素的位置c
对于c之前的，所有前缀和pi求和，对于c之后的，应该求
k-p[c] + k-p[c+1] + ... + k-p[n]
即k*(n-c+1) - (p[c]+p[c+1]+...+p[n])即可。注意这之中还包括为1的数的情况，
所以需要减去 对于1~k,min(i,k-i)的和。

对于第二部分，则可以求逆序数对即可。
题目链接：https://codeforces.com/contest/1268/problem/C
****************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 200100;
const int mod = 1000000007;
int lz[4*maxn], a[maxn], b[maxn], c[maxn];
LL ans[maxn], p[4*maxn];
void creat(int l, int r, int k);
void pushdown(int k, int l, int r);
int getId(int l, int r, int x, int k);
LL query(int l, int r, int al, int ar, int k);
void Update(int l, int r, int al, int ar, int k);

int main()
{
	int n, i, j, k;
	scanf("%d", &n);
	for(i=1;i<=n;i++)
	{
		scanf("%d", &a[i]);
		b[a[i]] = i;
	}
	creat(1, n, 1);
	//求逆序数对，即后半部分的贡献
	for(i=1;i<=n;i++)
	{
		ans[i] = ans[i-1]+query(1,n,b[i], n, 1);
		Update(1, n, b[i], b[i], 1);
		//c[i]表示以分解，即c[i]之前的pi较小，c[i]之后的k-pi较小
		c[i] = getId(1, n, i/2+1, 1);
	}
	creat(1, n, 1);
	for(i=1;i<=n;i++)
	{
		Update(1, n, b[i], n, 1);
		LL sum = query(1, n, 1, c[i]-1, 1) + (LL)i*(n-c[i]+1) - query(1, n, c[i], n, 1);
		LL l = (i-1)/2, r=i-1-l;
		sum -= (l+1)*l/2 + (r+1)*r/2;
		ans[i] += sum;
	}
	for(i=1;i<=n;i++)
		printf("%I64d ", ans[i]);
	return 0;
}

void creat(int l, int r, int k)
{
	p[k] = 0;
	lz[k] = 0;
	if(l == r)return;
	int mid = (l+r)/2;
	creat(l, mid, 2*k);
	creat(mid+1, r, 2*k+1);
}

void Update(int l, int r, int al, int ar, int k)
{
	p[k] += (ar-al+1);
	if(l ==al && ar == r){
		lz[k]++;
		return ;
	}
	pushdown(k, l, r);
	int mid = (l+r)/2;
	if(ar <= mid)Update(l, mid, al, ar, 2*k);
	else if(al > mid)Update(mid+1, r, al, ar, 2*k+1);
	else Update(l, mid, al, mid, 2*k),
			Update(mid+1, r, mid+1, ar, 2*k+1);
}

void pushdown(int k, int l, int r)
{
	if(lz[k])
	{
		int mid = (l+r)/2;
		lz[2*k] += lz[k];
		lz[2*k+1] += lz[k];
		p[2*k] += lz[k] *(mid-l+1);
		p[2*k+1] += lz[k] *(r-mid);
		lz[k] = 0;
	}
}

LL query(int l, int r, int al, int ar, int k)
{
	if(al > ar)return 0;
	if(l == al && r == ar)
		return p[k];
	int mid = (l+r)/2;
	pushdown(k, l, r);
	if(ar <= mid)
		return query(l, mid, al, ar, 2*k);
	else if(al > mid)
		return query(mid+1, r, al, ar, 2*k+1);
	else
		return query(l, mid, al, mid, 2*k)+
				query(mid+1, r, mid+1, ar, 2*k+1);
}

int getId(int l, int r, int x, int k)
{
	if(l == r)return l;
	int mid = (l+r)/2;
	pushdown(k, l, r);
	if(x <= p[2*k])return getId(l, mid, x, 2*k);
	else return getId(mid+1, r, x-p[2*k], 2*k+1);
}