//树套树(树状数组套权值线段树)
//经典的树套树模板题，
//个人理解：树套树其实就是树状数组和线段树(虽说是线段树，其实就是几条链)
//因为如果直接每个树状数组内层再建线段树就直接是n*n的空间了
//内层实际上存储的有限，比如1位置的树状数组实际上就只有1个元素
//所以这n棵线段树里，很多结点实际上是空的
//对于外层的树状数组，实际上存储的是几条链，其他空的部分都是重复利用了 
//然后内层对于每个元素实际上只存储那一条链就行了
//所以初始建的空间复杂度是n*log n *log n
//更新：后面更新元素，就和主席树差不多，将原本的链减去值，然后再更新新的那条的
//		链就行了
//查询：查询主要分为两种，一种是查询区间第k小，这种需要算出所有需要使用到的外层
//		树状数组，然后算出[ql,qr]在内层线段树的左边有多少个元素，然后决定往哪边
//		遍历
//		另一种查询就是小于k的有多少个，这个也很简单，就直接遍历所有需要用到的外层
//		树状数组，然后统计各个树状数组满足条件的所有元素的个数，然后减一波就行了
//题目链接：https://www.luogu.org/problem/P3380 
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
typedef pair<LL, int> P;
const int maxn = 50100;
//tot:当前使用结点编号，tl：左子树结点编号，tr：右子树结点编号，p：存储的数值 
int tot, tl[100*maxn], tr[100*maxn], p[100*maxn]; 
//n：数组大小，le：离散化后的所有可能取值的数量，dic：离散数组 
int n, le, dic[2*maxn], a[maxn], op[maxn], ql[maxn], qr[maxn], qk[maxn];
//lsz，rsz：以l，r为前缀和的树状数组需要访问的元素数量，vl，vr：存储需要访问的元素 
int lsz, rsz, vl[maxn], vr[maxn];
void init();
int lowbit(int x);
void built(int n);
int lisan(int dic[], int n);
void Add(int k, int pos, int x);
void Update(int x, int pk);
void Insert(int l, int r, int k, int pos, int x);
int queryRank(int ql, int qr, int qk, int x);
int querymin(int l, int r, int k, int x);
int queryVal(int l, int r, int x); 
int queryK(int l, int r, int x);
int KsBefore(int ql, int qr, int qk);
int KsAfter(int ql, int qr, int qk);

int main()
{
	int m, i, j, k, ans;
	init();
	scanf("%d %d", &n, &m);
	for(i=1;i<=n;i++){
		scanf("%d", &a[i]);
		dic[++le] = a[i];
	}
	for(i=1;i<=m;i++){
		scanf("%d %d %d", &op[i], &ql[i], &qr[i]);
		if(op[i]!=3)
			scanf("%d", &qk[i]);
		if(op[i] == 3)dic[++le] = qr[i];
		else if(op[i] != 2)dic[++le] = qk[i];
	}
	le = lisan(dic, le);
	built(n); 
	for(i=1;i<=m;i++)
		switch(op[i]){
			case 1:ans = queryRank(ql[i], qr[i], qk[i], 1)+1;
					printf("%d\n", ans);break;
			case 2:ans = queryVal(ql[i], qr[i], qk[i]);
					printf("%d\n", ans);break;
			case 3:Update(ql[i], qr[i]);break;
			case 4:ans = KsBefore(ql[i], qr[i], qk[i]);
					if(ans == -1)
						printf("-2147483647\n");
					else
						printf("%d\n", ans);
					break;
			case 5:ans = KsAfter(ql[i], qr[i], qk[i]);
					if(ans == -1)
						printf("2147483647\n");
					else
						printf("%d\n", ans);
					break;
		}
	return 0;
}
//离散化去重并返回长度
int lisan(int dic[], int n)
{
	int l=0;
	sort(dic+1, dic+1+n);
	dic[0] = dic[1]-100;
	for(int i=1;i<=n;i++){
		if(dic[i] != dic[l])
		dic[++l] = dic[i];
	}
	return l;
}
//初始化数组
void init()
{
	le = 0;
	memset(tl, 0, sizeof(tl));
	memset(tr, 0, sizeof(tr));
	memset(p, 0, sizeof(p));
}
//构造初始的树(链)
void built(int n)
{
	tot = 1;
	while(tot<n)
		tot<<=1;
	for(int i=1;i<=n;i++)
	{
		int pos = lower_bound(dic+1, dic+1+le, a[i])-dic;
		Add(i, pos, 1);
	}
}
//更新k有关的外层树状数组 
void Add(int k, int pos, int x)
{
	for(int i=k;i<=n;i+=lowbit(i))
		Insert(1, le, i, pos, x);
}

int lowbit(int x)
{
	return x&(-x);
}
//更新k这条链内层线段树 
void Insert(int l, int r, int k, int pos, int x)
{
	if(l == r){
		p[k] += x;
		return;
	}
	int mid = (l+r)/2;
	if(pos<=mid){
		if(!tl[k])tl[k]=++tot;
		Insert(l, mid, tl[k], pos, x);
	}
	else{
		if(!tr[k])tr[k]=++tot;
		Insert(mid+1, r, tr[k], pos, x);
	}
	p[k] = p[tl[k]] + p[tr[k]];
}
//将原本第x个数修改为pk
void Update(int x, int pk)
{
	int pos = lower_bound(dic+1, dic+le+1, a[x])-dic;
	Add(x, pos, -1);
	pos = lower_bound(dic+1, dic+le+1, pk)-dic;
	Add(x, pos, 1);
	a[x] = pk;
}
//查询值qk在区间内[ql,qr]的排名(x为1不包含自身，x为0包含自身)
//查询区间比qk小的数量，可以将分别求出l-1，r总共有多少个，再减一下 
int queryRank(int ql, int qr, int qk, int x)
{
	int pos = lower_bound(dic+1, dic+le+1, qk)-dic;
	int sum = 0;
	if(pos-x<1)return 0;
	for(int i=qr;i;i-=lowbit(i))
		sum += querymin(1, le, i, pos-x);
	for(int i=ql-1;i;i-=lowbit(i))
		sum -= querymin(1, le, i, pos-x);
	return sum;
}
//查询小于等于x的数的数量 
int querymin(int l, int r, int k, int x)
{
	if(l == r && l == x)
		return p[k];
	int mid = (l+r)/2;
	if(x <= mid)
		return querymin(l, mid, tl[k], x);
	else
		return p[tl[k]]+querymin(mid+1, r, tr[k], x);
}
//返回区间排名为k的数 
int queryVal(int l, int r, int k)
{
	lsz = rsz = 0;
	for(int i=l-1;i;i-=lowbit(i))
		vl[lsz++] = i;
	for(int i=r;i;i-=lowbit(i))
		vr[rsz++] = i;
	int ks = queryK(1, le, k);
	return dic[ks];
}
//查询内层，求第k小
//对于每一层先求出当前层[l,r]内的左边有多少个 
int queryK(int l, int r, int x)
{
	if(l == r)return l;
	int i, sum = 0;
	for(i=0;i<rsz;i++)
		sum += p[tl[vr[i]]];
	for(i=0;i<lsz;i++)
		sum -= p[tl[vl[i]]];
	int mid = (l+r)/2;
	if(x <= sum){
		for(i=0;i<rsz;i++)
			vr[i] = tl[vr[i]];
		for(i=0;i<lsz;i++)
			vl[i] = tl[vl[i]];
		return queryK(l, mid, x);
	}
	else {
		for(i=0;i<rsz;i++)
			vr[i] = tr[vr[i]];
		for(i=0;i<lsz;i++)
			vl[i] = tr[vl[i]];
		return queryK(mid+1, r, x-sum);
	} 
}
//返回[ql,qr]中小于qk的最大的数 
int KsBefore(int ql, int qr, int qk)
{
	int num = queryRank(ql, qr, qk, 1);
	if(num == 0)return -1;
	return queryVal(ql, qr, num);
}
//返回[ql,qr]中大于qk的最小的数 
int KsAfter(int ql, int qr, int qk)
{
	int num = queryRank(ql, qr, qk, 0);
	if(num == qr-ql+1)return -1;
	return queryVal(ql, qr, num+1);
}
