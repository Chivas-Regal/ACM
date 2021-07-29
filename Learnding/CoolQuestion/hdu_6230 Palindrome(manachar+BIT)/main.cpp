/********************************************
manachar+树状数组/线段树
定义字符串满足s[i] = s[2*n-i] = s[2*n+i-2](1<=i<=n)为one-and-half palindromic
如abcbabc,对于给定字符串，求其中有多少个子串是one-and-half palindromic。

题解：观察式子和题目中的例子，可以发现目标串是两个回文串叠加在一起，
目标串有两个中心点，分别为两个回文串的中心，并且目标串只与长度为
奇数的回文串相关。所以可以利用manachar，求出给定以当前位置为中心的
回文串的半径。对于两个中心点，每个中心点必须在另一个中心的回文半径
内才能组成目标串，即对于中心点i,j,中心半径分别为p[i],p[j]，必须满足
		i-p[i] <= j <= i+p[i], j-p[j] <= i <= j+p[j]
才能组成目标串(p[i],p[j]所存的回文半径不包括中心点)。
考虑固定右中心点，求有多少个左中心点满足上述条件。对于右端点j，回文半径
为p[j](p[j]>0)，查询[j-p[j], j-1]中有多少个i，满足i+p[i]>=j。显然这个
问题可以利用主席树。也可以通过预处理，然后利用树状数组/线段树维护熟练，
对于原串的每个端点，预处理出以其为中心的回文串的左端点和右端点，然后
遍历原串，如果左端在当前位置，维护其中心点信息，然后统计线段树中 中心点
处于[j-p[j],j-1]中数量即可，然后再将右端点为当前点中心点信息删除。

PS：线段树和树状数组的常数差距真大，线段树2200ms，树状数组800ms
题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=6230
*********************************************/
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
const int maxn = 500100;
const int mod = 998244353;
char str[maxn];
int p[4*maxn], q[maxn], qs[maxn];
vector<int> g1[maxn], g2[maxn];
int manachar(char str[]);
void creat(int l, int r, int k);
void Update(int l, int r, int x, int y, int k);
int query(int l, int r, int al, int ar, int k);
int lowbit(int x);
void Update(int x, int y, int len);
int query(int x);

int main()
{
	int t, i, j, k, n, len;
	LL ans;
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf(" %s", str+1);
		len = manachar(str);
		for(i=0;i<=len;i++){
			g1[i].clear();
			g2[i].clear();
			qs[i] = 0;
		}
		for(i=1;i<=len;i++)
		{
			//预处理回文左端点和右端点信息
			g1[i-q[i]].push_back(i);
			g2[i+q[i]].push_back(i);
		}
		for(i=1;i<=len;i++)
		{
			for(j=0;j<g1[i].size();j++)
				Update(g1[i][j], 1, len);
			//统计在区间[i-q[i]-1, i-1]中的点的数量
			if(i-1 > i-q[i]-1)
				ans += query(i-1)-query(i-q[i]-1);
			for(j=0;j<g2[i].size();j++)
				Update(g2[i][j], -1, len);
		}
		/*
		//线段树维护区间信息
		creat(1, len, 1);
		for(i=1;i<=len;i++)
		{
			for(j=0;j<g1[i].size();j++)
				Update(1, len, g1[i][j], 1, 1);
			ans += query(1, len, i-q[i], i-1, 1);
			for(j=0;j<g2[i].size();j++)
				Update(1, len, g2[i][j], -1, 1);
		}
		*/
		printf("%lld\n", ans);
	}
	return 0;
}

int manachar(char str[])
{
	int i, j, k, len, id, mx;
	len = strlen(str+1);
	str[0] = '$';
	id = mx = 0;
	for(i=1;i<=len;i++)
	{
		p[i] = mx>i?min(mx-i,p[2*id-i]):1;
		while(str[i-p[i]] == str[i+p[i]])p[i]++;
		if(i+p[i] > mx)
		{
			id = i;
			mx = i+p[i];
		}
	}
	for(i=1;i<=len;i++){
		q[i] = p[i]-1;
		//printf("%c %d\n", str[i], p[i]);
	}
	return len;
}

int lowbit(int x)
{
	return x&(-x);
}

void Update(int x, int y, int len)
{
	for(int i=x;i<=len;i+=lowbit(i))
		qs[i] += y;
}

int query(int x)
{
	int i, ans = 0;
	for(i=x;i>0;i-=lowbit(i))
		ans += qs[i];
	return ans;
}
//以下是利用线段树维护信息
void creat(int l, int r, int k)
{
	p[k] = 0;
	if(l == r)return ;
	int mid = (l+r)/2;
	creat(l, mid, 2*k);
	creat(mid+1, r, 2*k+1);
}

void Update(int l, int r, int x, int y, int k)
{
	if(l == r){
		p[k] += y;
		return ;
	}
	int mid = (l+r)>>1;
	if(x <= mid)
		Update(l, mid, x, y, 2*k);
	else
		Update(mid+1, r, x, y, 2*k+1);
	p[k] = p[2*k] + p[2*k+1];
}

int query(int l, int r, int al, int ar, int k)
{
	if(al > ar)return 0;
	if(l == al  && r == ar){
		return p[k];
	}
	int mid = (l+r)>>1;
	if(ar <= mid)
		return query(l, mid, al, ar, 2*k);
	else if(al > mid)
		return query(mid+1, r, al, ar, 2*k+1);
	else return query(l, mid, al, mid, 2*k)+
				query(mid+1, r, mid+1, ar, 2*k+1);
}