//树状数组
//二维偏序问题，有一个1~n的排列，求区间[l,r]内有多少对
//(i,j)使ai%aj==0||aj%ai==0
//对于每个ai，可以找出能和它满足上述关系的所有aj，并保存
//aj的那个下标，即j，因为i，j可能重复，将其中较大的存入较小的中 
//对所有询问按l递减排序，然后将l右边的所有ai满足条件的下标
//都更新至树状数组内，然后访问sum(r)，即为所求， 
//题目链接： http://codeforces.com/problemset/problem/301/D
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 200100;
struct node{
	int id, l, r;
}pb[maxn];
int n, p[maxn], a[maxn], b[maxn], ans[maxn];
vector<int> g[maxn];
int sum(int x);
int lowbit(int x);
bool cmp(node a, node b);
void add(int x, int ad);

int main()
{
	int m, i, j;
	scanf("%d %d", &n, &m);
	for(i=1;i<=n;i++){
		scanf("%d", &a[i]);
		b[a[i]] = i;
	}
	//预处理出所有满足条件的，并将较大的下标存入较小的中 
	for(i=1;i<=n;i++)
		for(j=a[i];j<=n;j+=a[i])
		{
			if(i < b[j])
				g[i].push_back(b[j]);
			else
				g[b[j]].push_back(i);
		}
	for(i=1;i<=m;i++){
		scanf("%d %d", &pb[i].l, &pb[i].r);
		pb[i].id = i;
	}
	sort(pb+1, pb+1+m, cmp);
	int maxx = n+1;
	for(i=1;i<=m;i++){
		for(j=pb[i].l;j<maxx;j++){
			for(int k=0;k<g[j].size();k++)
				add(g[j][k], 1);
		}
		maxx = pb[i].l;
		ans[pb[i].id] = sum(pb[i].r);
	}
	for(i=1;i<=m;i++)
		printf("%d\n", ans[i]);
	return 0;
}

bool cmp(node a, node b)
{
	return a.l > b.l;
}

int lowbit(int x)
{
	return x&(-x);
}

void add(int x, int ad)
{
	for(int i=x;i<=n;i+=lowbit(i))
		p[i] += ad; 
}

int sum(int x)
{
	int sum = 0;
	for(int i=x;i;i-=lowbit(i))
		sum += p[i];
	return sum;
}
