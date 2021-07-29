/*********************************************************
线段树

有一个排列，第i位为ai.初始可以选择一个位置，这个位置及其左边元素为一个集合，这个位置右边的元素为一个集合
可以花费一定的代价，将一个元素转移至另一个集合中，转移第i个元素的代价为pi，现在要求是前面的集合
的最大值，小于右边集合的最小值。求需要的最小代价。

思路：首先因为可以任意划分，所以初始集合不确定，需要考虑每种划分的最优解。对于每个初始的划分
可以考虑依次考虑将所有小于等于i的数都留在左集合，大于i的都留在右集合(i属于1~n)的代价，
取最小值即可。当求取i的结果时，需要计算两部分，将左集合[i+1,n]的数转移，将右集合[1,i]的数转移
结果为两者和。
可以考虑利用线段树维护所有i的代价最小值。初始划分左区间为空，右区间满的，则初始状态下第i个数
的值就是移动数字1~数字i的所有数字的代价和(是数字1到i，不是位置)。当初始划分将aj,分至左集合，
则对于上一种划分来说，右集合少了aj,所以所有的i>=aj来说，不用再花费pj的代价将aj移动至左集合
(因为他已经被移动至右集合了)，但对于左集合来说，所有的i<aj，需要花费额外pj的代价将aj移动至
右集合。所以每次更新需要将1~aj-1的部分加上pj，aj~n的部分减去pj。

题目链接：http://codeforces.com/contest/1295/problem/E
****************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<map>
#include<queue>
#include<stack>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 200200;
const int mod = 1000000007;
LL ans, sum[maxn], p[maxn*4], lz[maxn*4];
//b：移动第i个元素的代价
int a[maxn], b[maxn];
void creat(int l, int r, int k);
void pushdown(int k);
void Update(int l, int r, int al, int ar, int x, int k);
 
int main()
{
	int n, i, j, k;
	scanf( "%d", &n);
	ans = 1e17;
	for(i=1;i<=n;i++)
		scanf("%d", &a[i]);
	for(i=1;i<=n;i++){
		scanf("%d", &b[i]);
		sum[a[i]] = b[i];
	}
	for(i=2;i<=n;i++){
		sum[i] += sum[i-1];
	}
	creat(1, n, 1);
	ans = min(b[1], b[n]);
	for(i=1;i<n;i++){
		Update(1, n, 1, a[i]-1, b[i], 1);
		Update(1, n, a[i], n, -b[i], 1);
		ans = min(ans, p[1]);
	}
	printf("%I64d\n", ans);
	return 0;
}
 
void creat(int l, int r, int k)
{
	lz[k] = 0;
	if(l == r){
		p[k] = sum[l];
		return;
	}
	int mid = (l+r)/2;
	creat(l, mid, 2*k);
	creat(mid+1, r, 2*k+1);
	p[k] = min(p[2*k], p[2*k+1]);
}
 
void Update(int l, int r, int al, int ar, int x, int k)
{
	if(al>ar)return;
	if(l == al && r == ar){
		p[k] += x;
		lz[k] += x;
		return;
	}
	pushdown(k);
	int mid = (l+r)/2;
	if(ar <= mid)Update(l, mid, al, ar, x,2*k);
	else if(al > mid)Update(mid+1, r, al, ar, x, 2*k+1);
	else Update(l, mid, al, mid, x, 2*k), Update(mid+1, r, mid+1, ar, x, 2*k+1);
	p[k] = min(p[2*k], p[2*k+1]);
}
 
void pushdown(int k)
{
	if(lz[k])
	{
		p[2*k]+=lz[k];
		p[2*k+1] += lz[k];
		lz[2*k] += lz[k];
		lz[2*k+1] += lz[k];
		lz[k] = 0;
	}
}