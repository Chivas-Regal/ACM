/****************************************************
线段树+期望

有n个点，每个点有pi/100的概率回答是。现规则如下：
询问第i个点，如果其回答为是，如果i=n,则游戏结束，否则第二天
继续询问第i+1个点，
如果第i个点回答为否，则下一天访问<=i的编号最大的checkpoint.
第1个点必然一直是checkpoint，每次会询问将第u个点变换一下(如果不是
checkpoint则变为checkpoint，如果是则变为不是checkpoint)，问每次
改变后游戏结束的期望步数。

思想：设数组pi[i]为第i个点回答是的概率，则单独考虑每一步，它回答
为是的期望步数ex[i] = 100/pi[i];首先不考虑其他checkpoint，
游戏结束的期望步数是
	((((0+1)*ex[1] + 1)*ex[2]....+1)*ex[n]
假如中间的j点变成了checkpoint，则游戏结束的期望步数变为
(((0+1)*ex[1]+1)*ex[2]....+1)*ex[j-1]+(((0+1)*ex[j]+1)*ex[j+1]....+1)*ex[n]
而如果将是checkpoint的点j，变为不是checkpoint，期望步数就会变成最上面的
式子，而实际上就是将加号后面的那个0变为其加号前面的那个式子，而前面的式子
正好是1号点到j-1号点回答为是期望步数。
而通过上式可以发现对于多个检查点，从1号点到n号点回答为是的期望步数，实际上
就是每个checkpoint到下一个checkpoint点之前的那个点回答为是的期望步数的总和。
所以可以考虑利用线段树来维护点的信息，包括其是否为checkpoint，以及如果是
checkpoint从其开始到下一个checkpoint之前的那个点回答为是的期望步数，线段树
维护区间内checkpoint点的数量和总期望步数。
而对于检查点i到检查点j之前的点回答为是的期望步数可以利用后缀来求。
设suf[i]表示i号点开始，到n号点回答为是期望步数，而sum[i]=ex[i]*ex[i+1]*..*ex[n]
利用上面的公式可以推出 suf[i] = suf[i+1] + ex[i] * sum[i];
题目链接：https://codeforces.com/problemset/problem/1264/C
***************************************************/
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
const int maxn = 201000;
const int mod = 998244353;
int a[maxn], q[maxn*4];
bool stu[maxn];
//ex[i]:只考虑i号点回答为是的期望步数
//suf[i]:i号点为checkpoint到n号点回答为是的期望步数
//sum[i]:ex[i]*ex[i+1]*ex[i+2]*....*ex[n];
LL p[maxn*4], suf[maxn], sum[maxn], ex[maxn];
LL Pow(LL a, LL b);
void pushup(int k);
void creat(int l, int r, int k);
int getId(int l, int r, int x, int k);
int getSum(int l, int r, int al, int ar, int k);
void Update(int l, int r, int x, int y1, LL y2, int k);

int main()
{
	int n, m, i, j, k, l, r;
	scanf("%d %d", &n, &m);
	for(i=1;i<=n;i++){
		scanf("%d", &a[i]);
		ex[i] = (100*Pow(a[i], mod-2))%mod;
	}
	suf[n] = sum[n] = ex[n];
	suf[n+1] = 0, sum[n+1] = 1;
	for(i=n-1;i>=1;i--){
		sum[i] = (sum[i+1]*ex[i])%mod;
		suf[i] = (suf[i+1] + sum[i]) %mod;
	}
	creat(1, n, 1);
	Update(1, n, 1, 1, suf[1], 1);
	stu[1] = 1;

	while(m--)
	{
		scanf("%d", &i);
		stu[i] = !stu[i];
		j = getSum(1, n, 1, i, 1);
		if(!stu[i])
		{
			l = getId(1, n, j-1, 1);
			if(j == q[1])r = n+1;
			else r = getId(1, n, j+1, 1);
			//printf("l:%d r:%d\n", l, r);
			//将两段checkpoint的期望步数合为一段的期望步数
			Update(1, n, l, 0, 0, 1);
			Update(1, n, i, 0, 0, 1);
			LL ks = (suf[l]-suf[r]+mod)%mod * Pow(sum[r], mod-2)%mod;
			Update(1, n, l, 1, ks, 1);
		}
		else
		{
			l = getId(1, n, j, 1);
			if(j == q[1])r = n+1;
			else r = getId(1, n, j+1, 1);
			//printf("l:%d r:%d\n", l, r);
			Update(1, n, l, 0, 0, 1);
			LL ks = (suf[l]-suf[i]+mod)%mod * Pow(sum[i], mod-2)%mod;
			Update(1, n, l, 1, ks, 1);
			ks = (suf[i]-suf[r]+mod)%mod * Pow(sum[r], mod-2)%mod;
			Update(1, n, i, 1, ks, 1);
		}
		printf("%lld\n", p[1]);
	}
	return 0;
}

LL Pow(LL a, LL b)
{
	LL n = 1;
	while(b)
	{
		if(b&1)n = n*a % mod;
		a = a*a%mod;
		b /=2 ;
	}
	return n;
}

void pushup(int k)
{
	q[k] = q[2*k] + q[2*k+1];
	p[k] = (p[2*k] + p[2*k+1])%mod;
}

void creat(int l, int r, int k)
{
	q[k] = 0, p[k] = 0;
	if(l == r)return ;
	int mid = (l+r)/2;
	creat(l, mid, 2*k);
	creat(mid+1, r, 2*k+1);
}

void Update(int l, int r, int x, int y1, LL y2, int k)
{
	if(l == r && l == x){
		q[k] = y1;
		p[k] = y2;
		return ;
	}
	int mid = (l+r)/2;
	if(x <= mid)
		Update(l, mid, x, y1, y2, 2*k);
	else
		Update(mid+1, r, x, y1, y2, 2*k+1);
	pushup(k);
}

int getSum(int l, int r, int al, int ar, int k)
{
	if(l == al && r == ar){
		return q[k];
	}
	int mid = (l+r)/2;
	if(ar <= mid)
		return getSum(l, mid, al, ar, 2*k);
	else if(al > mid)
		return getSum(mid+1, r, al, ar, 2*k+1);
	else{
		return getSum(l, mid, al, mid, 2*k)+
		getSum(mid+1,r, mid+1, ar, 2*k+1);
	}
}

int getId(int l, int r, int x, int k)
{
	if(l == r)return l;
	int mid = (l+r)/2;
	if(x <= q[2*k])
		return getId(l, mid, x, 2*k);
	else
		return getId(mid+1, r, x-q[2*k], 2*k+1);
}