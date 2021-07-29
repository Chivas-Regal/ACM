//思路题
//已知si是i前面的比i小的数的和
//可以一次确定每个数，最小的最靠右的数一定是当前的i，
//第一个靠右的si为0的i一定是1，然后将i之后的si都减去1 
//然后继续找最靠右的0，其位置一定是2，然后将其后面的si都减去2 
//线段树维护一下就好了
//题目链接：https://codeforces.com/contest/1208/problem/D
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 200100;
struct node{
	LL s, lazy;
	int id;
}p[4*maxn];
int a[maxn];
LL s[maxn];
void pushup(int k);
void pushdown(int k);
void creat(int l, int r, int k);
int query(int l, int r, int k);
void update1(int l, int r, int x, int k);
void update2(int l, int r, int al, int ar, int x, int k);

int main()
{
	int n, i, j;
	scanf("%d", &n);
	for(i=1;i<=n;i++)
		scanf("%I64d", &s[i]);
	creat(1, n, 1);
	for(i=1;i<=n;i++)
	{
		//查询当前最靠近右的si为0的下标 
		int id = query(1, n, 1);
		a[id] = i;
		//当前位置已使用，更新一下状态 
		update1(1, n, id, 1);
		if(id != n)
			update2(1, n, id+1, n, -i, 1);
	}
	for(i=1;i<=n;i++)
		printf("%d ", a[i]);
	return 0;
}

void creat(int l, int r, int k)
{
	p[k].lazy = 0;
	if(l == r){
		p[k].s = s[l];
		p[k].id = l;
		return;
	}
	int mid = (l+r)/2;
	creat(l, mid, 2*k);
	creat(mid+1, r, 2*k+1);
	pushup(k);
}

int query(int l, int r, int k)
{
	if(l == r)return p[k].id;
	pushdown(k);
	int mid = (l+r)/2;
	if(p[2*k].s < p[2*k+1].s)
		return query(l, mid, 2*k);
	else
		return query(mid+1, r, 2*k+1);
	pushup(k);
}
//将x标记为不可用 
void update1(int l, int r, int x, int k)
{
	if(l == r){
		p[k].s = 100000000000000LL;
		return;
	}
	pushdown(k);
	int mid = (l+r)/2;
	if(x <= mid)
		update1(l, mid, x, 2*k);
	else
		update1(mid+1, r, x, 2*k+1);
	pushup(k);
}
//将[l,r]内的所有数，都减去x 
void update2(int l, int r, int al, int ar, int x, int k)
{
	if(al == l && ar == r){
		p[k].lazy += x;
		p[k].s += x;
		if(l != r)pushdown(k), pushup(k);
		return ; 
	}
	pushdown(k);
	int mid = (l+r)/2;
	if(ar <= mid)
		update2(l, mid, al, ar, x, 2*k);
	else if(al > mid)
		update2(mid+1, r, al, ar, x, 2*k+1);
	else{
		update2(l, mid, al, mid, x, 2*k);
		update2(mid+1, r, mid+1, ar, x, 2*k+1);
	}
	pushup(k);
}

void pushup(int k)
{
	if(p[2*k].s < p[2*k+1].s){
		p[k].s = p[2*k].s;
		p[k].id = p[2*k].id;
	}else{
		p[k].s = p[2*k+1].s;
		p[k].id = p[2*k+1].id;
	}
}

void pushdown(int k)
{
	if(p[k].lazy){
		p[2*k].lazy += p[k].lazy;
		p[2*k+1].lazy += p[k].lazy;
		p[2*k].s += p[k].lazy;
		p[2*k+1].s += p[k].lazy;
		p[k].lazy = 0;
	}
}
