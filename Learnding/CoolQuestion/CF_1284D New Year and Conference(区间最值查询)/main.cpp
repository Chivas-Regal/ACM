/**********************************************************
数据结构
有n场表演，有两个场地，如果在a场地表演则需要占用[sai,eai]这段时间，在b场地表演则需要占用[sbi,ebi]这段时间。如果两个表演，占用了同一个时间点，则认为这两个表演是冲突的。但因为每个表演在a场地和b场地的时间段不同。所以所有的表演是否满足一起在某场地冲突或者不冲突。

思路：题目就是让求两个表演，如果在a场地冲突，则在b场地也需要冲突，如果每两个表演都满足上述条件，则输出YES，否则输出NO。显然如果暴力判断，时间复杂度是O(n^2)，会超时。所以考虑对于每个表演i，找出a场地与它冲突的表演，然后判断这些表演在b场地是否也冲突。
对于表演[s1,e1]和[x,y]，两者不冲突的条件是e1<x || s1>y。而对于多个表演[s1,e1]、[s2,e2]....都与[x,y]冲突，则需要不存在ei<x || si>y。所以如果emin<y || smax>y成立，则存在表演与[x,y]不冲突。
可以考虑对sa作为第一关键字，ea作为第二关键字升序排列。对于第i场表演，找出所有在[sai,eai]开始的表演，则这些表演必然与第i场表演冲突。同时，排序过后的这些表演必然连续，可以考虑使用数据结构(线段树/ST表等)查询这一段区间另一个场地的emin和smax，如果另一个场地，有表演与第i个表演不冲突，则输出NO。
同时，因为上述只检验了在a场地冲突一定在b场地冲突的情况，并未考虑在b场地冲突而在a场地不冲突的情况。所以可以将[sai,eai]与[sbi,ebi]交换，在进行上述检验即可。

题目链接：https://codeforces.com/problemset/problem/1284/D
************************************************************/
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
#define eps 1e-6
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
const int mod = 9901;
struct node{
	int sa, ea, sb, eb;
	node(){}
	node(int a, int b, int c, int d){
		sa=a,ea=b,sb=c,eb=d;
	}
	bool operator <(node b)const{
		if(sa == b.sa)return ea < b.ea;
		return sa < b.sa;
	}
}p[maxn];
int mx[4*maxn], mi[4*maxn];
bool solve(int n);
void creat(int l, int r, int k);
int querymin(int l, int r, int al, int ar, int k);
int querymax(int l, int r, int al, int ar, int k);

int main()
{
	int n, i, j, k, sig = 1;
	scanf("%d", &n);
	for(i=1;i<=n;i++)
		scanf("%d %d %d %d", &p[i].sa, &p[i].ea, &p[i].sb, &p[i].eb);
	sig &= solve(n);
	for(i=1;i<=n;i++)
		swap(p[i].sa, p[i].sb), swap(p[i].ea, p[i].eb);
	sig &= solve(n);
	if(sig)printf("YES\n");
	else printf("NO\n");
	return 0;
}

bool solve(int n)
{
	sort(p+1, p+1+n);
	creat(1, n, 1);
	for(int i=1;i<=n;i++)
	{
		//查找与第i场表演冲突的集合
		int pos = lower_bound(p+1, p+1+n, node(p[i].ea, 1e9+1000, 0, 0) )-p-1;
		if(!(i+1 <= pos))continue;
		//检验另一场地中的所有表演是否都与当前场冲突
		if(querymin(1, n, i+1, pos, 1)<p[i].sb || 
			querymax(1, n, i+1, pos, 1)>p[i].eb)
			return false;
	}
	return true;
}
//线段树初始化，以及后面的函数求smax, emin。
void creat(int l, int r, int k)
{
	if(l == r){
		mx[k]=p[l].sb, mi[k]=p[l].eb;
		return ;
	}
	int mid = (l+r)/2;
	creat(l, mid, 2*k);
	creat(mid+1, r, 2*k+1);
	mx[k] = max(mx[2*k], mx[2*k+1]);
	mi[k] = min(mi[2*k], mi[2*k+1]);
}

int querymin(int l, int r, int al, int ar, int k)
{
	if(l == al && r == ar)return mi[k];
	int mid = (l+r)/2;
	if(ar <= mid)return querymin(l, mid, al, ar, 2*k);
	else if(al > mid)return querymin(mid+1, r, al, ar, 2*k+1);
	else return min(querymin(l, mid, al, mid, 2*k),
					querymin(mid+1, r, mid+1, ar, 2*k+1));
}

int querymax(int l, int r, int al, int ar, int k)
{
	if(l == al && r == ar)return mx[k];
	int mid = (l+r)/2;
	if(ar <= mid)return querymax(l, mid, al, ar, 2*k);
	else if(al > mid)return querymax(mid+1, r, al, ar, 2*k+1);
	else return max(querymax(l, mid, al, mid, 2*k),
					querymax(mid+1, r, mid+1, ar, 2*k+1));
}