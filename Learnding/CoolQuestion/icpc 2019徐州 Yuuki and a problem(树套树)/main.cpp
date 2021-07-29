/**********************************************************
树套树
有n个数，可以进行两种操作，第一种操作是将a[x]变为y，第二种操作是询问
[l,r]区间内的数，选用一部分求和，不能组成的最小的数。

思路：假设1~n已经能被组成，则对于权值为w的物品，如果w <= n+1，则
1~n+w内的数都能被组成，如果w > n+1，显然n+1不能被组成。
对于带修改的区间查询，可以考虑使用BIT套权值线段树来维护区间信息，
对于询问，只需要依次考虑n+1能否被组成即可，假设1~n能被组成，则求n+1
能否被组成，如果能，则求和1~n+1,然后继续更新。

题目链接:https://nanti.jisuanke.com/t/42547
*************************************************************/
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
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 200100;
const int mod = 1000000007;
struct node{
	int l, r;
	LL sum;
}bs[maxn*100];
int n, mn, num, root[maxn], a[maxn];
int lowbit(int x);
void Insert(int x, int y, int z);
void Update(int l, int r, int k, int y, int z);
LL query(int al, int ar, int x);
LL getSum(int l, int r, int al, int ar, int k);

int main()
{
	int q, i, j, k;
	num = 1, mn = 200000;
	scanf("%d %d", &n, &q);
	for(i=1;i<=n;i++){
		scanf("%d", &a[i]);
		root[i] = num++;
	}
	num+=1000;
	for(i=1;i<=n;i++)
		Insert(i, a[i], 1);
	while(q--)
	{
		int l, r, op;
		scanf("%d %d %d", &op, &l, &r);
		if(op == 1)
		{
			Insert(l, a[l], -1);
			Insert(l, r, 1);
			a[l] = r;
		}
		else
		{
			LL ans = 0;
			while(1)
			{
				//求权值在1~ans+1之间的棋子的和
				LL sum;
				if(ans <= mn)
					sum = query(l, r, (int)ans+1);
				else
					sum = query(l, r, mn);
				//如果sum>=ans+1，则说明ans+1可以被组成，则更新ans
				//如果不能则跳出。
				if(sum >= ans + 1)
					ans = sum;
				else break;
				//dbg(ans);
			}
			printf("%lld\n", ans+1);
		}
	}
	return 0;
}
//以下代码为权值线段树
int lowbit(int x)
{
	return x&(-x);
}

void Insert(int x, int y, int z)
{
	for(;x<=n;x+=lowbit(x))
		Update(1, mn, root[x], y, z);
}

void Update(int l, int r, int k, int y, int z)
{
	bs[k].sum += z*y;
	if(l == r){
		return ;
	}
	int mid = (l+r)/2;
	if(y <= mid)
	{
		if(!bs[k].l)
			bs[k].l = num++;
		Update(l, mid, bs[k].l, y, z);
	}
	else
	{
		if(!bs[k].r)
			bs[k].r = num++;
		Update(mid+1, r, bs[k].r, y, z);
	}
}

LL query(int al, int ar, int x)
{
	LL sum1=0, sum2 = 0;
	for(int i=ar;i>0;i-=lowbit(i))
		sum1 += getSum(1, mn, 1, x, root[i]);
	for(int i=al-1;i>0;i-=lowbit(i))
		sum2 += getSum(1, mn, 1, x, root[i]);
	return sum1 - sum2;
}

LL getSum(int l, int r, int al, int ar, int k)
{
	if(l == al && r == ar){
		return bs[k].sum;
	}
	int mid = (l+r)/2;
	if(ar <= mid)
		return getSum(l, mid, al, ar, bs[k].l);
	else if(al > mid)
		return getSum(mid+1, r, al, ar, bs[k].r);
	else{
		return getSum(l, mid, al, mid, bs[k].l) + 
				getSum(mid+1, r, mid+1, r, bs[k].r);
	}
}