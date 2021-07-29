//主席树
//主席树就是多棵线段树，可以用来求[l,r]内第k大的值，或小于x的数的数量
//按照本题的样例，先暴力建n棵线段树，第i棵表示前i个元素放进树中的状态 
//然后求[l,r]区间的第k小值，参照前缀和的思想，拿r的状态减去l-1的状态
//剩下的就是[l,r]的状态。
//然后如果按上述做法肯定会超时爆内存，观察n棵线段树，会发现第i棵线段
//树与第i-1棵线段树的区别只有插入的那个元素a[i],所访问到的链不同
//所以主席树就是与前一颗线段树相比，只多更新访问a[i]的那条链一部分
//所以实际上除了原本的第一颗线段树，多出来的空间只是log2(n)*n，
//即链的深度*元素的个数。
//下面的博客关于主席树的图画的挺好的，能方便理解 
//博客链接：https://www.cnblogs.com/zyf0163/p/4749042.html
//题目链接：http://poj.org/problem?id=2104
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
const int maxn = 100100;
struct node
{
	int l, r, sum;
}p[maxn*20];
int num, root[maxn], a[maxn], b[maxn];
int update(int la, int l, int r, int x);
int creat(int l, int r);
int query(int ql, int qr, int l, int r, int x);

int main()
{
	int n, i, j, m;
	num = 0;
	scanf("%d %d", &n, &m);
	root[0] = creat(1, n);
	for(i=1;i<=n;i++)
	{
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	sort(b+1, b+n+1);
	for(i=1;i<=n;i++)
	{
		int x = lower_bound(b+1,b+n+1, a[i])-b;
		root[i] = update(root[i-1], 1, n, x);
	}
	while(m--)
	{
		int l, r, x;
		scanf("%d %d %d", &l, &r, &x);
		printf("%d\n", b[query(root[l-1], root[r], 1, n, x)]);
	}
	return 0;
}
//建立原始的线段树(空树) 
int creat(int l, int r)
{
	int ts = ++num;
	p[ts].sum = 0;
	if(l == r)return ts;
	int mid = (l+r)>>1;
	p[ts].l = creat(l, mid);
	p[ts].r = creat(mid+1, r);
	return ts;
}
//建立当把x插入树时，单独更新相关的链
int update(int la, int l, int r, int x)
{
	int now = ++num;
	p[now] = p[la];
	if(l == r){
		p[now].sum++;return now;
	}
	int mid=(l+r)>>1;
	if(x<=mid)
		p[now].l = update(p[la].l, l, mid, x);
	else
		p[now].r = update(p[la].r, mid+1, r, x);
	p[now].sum++;
	return now;
}
//查询，因为区间满足相减性，比如树所保存的同样区间[l,r]，
//在第qr状态时减去ql状态时的数，就是[ql+1,qr]区间的状态 
int query(int ql, int qr, int l, int r, int x)
{
	if(l == r)return l;
	int mid = (l+r)>>1, sum = p[p[qr].l].sum-p[p[ql].l].sum;
	if(x<=sum)
		return query(p[ql].l, p[qr].l, l, mid, x);
	else
		return query(p[ql].r, p[qr].r, mid+1, r, x-sum);
}
