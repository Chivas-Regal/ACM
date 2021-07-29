/************************************************************
贪心+单调栈

有n桶水，每个桶初始有ai单位的水，先可以将一段连续的桶内的水平均，即选择区间[l,r]，l到r
内所有的水将变为(al+a(l+1)+ ...+ ar)/(r-l+1)。可以进行任意次的以上操作，求使桶内水的
字典序尽量小。

思路：需要字典序最小，那么靠前的桶内的水需要尽量的少。所以可以选择每次暴力，求需要合并
到那个桶，才能使平均值最小。但这样是N^2的，所以考虑有没有更好的做法。
显然答案是一个非递减的序列，因为如果有一个桶内的水，比前面桶内的水少，那么他们平均一下，
字典序就可以更小。所以可以考虑进行这种操作：
维护一个栈，每个元素代表一段区间，区间维护三个参数l,r,ave,代表编号l到r的桶里，平均值为ave。
一次考虑每个初始桶，首先将初始的桶放入栈中，l=r=i,ave = ai。如果栈顶的平均值小于栈顶前面的
那个平均值，即stack[top].ave < stack[top-1].ave,则合并区间(这样可以保证字典序更小)。
遍历完所有桶后，栈中的区间即为结果。

题目链接：https://codeforces.com/problemset/problem/1299/C
*****************************************************************/
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
const int maxn = 1000100;
const int mod = 1000000007;
struct node{
	int l, r;
	double ave;
}p[maxn];
int a[maxn];
double ans[maxn], sum[maxn];

int main()
{
	int n, i, j, k, top = 0;
	scanf("%d", &n);
	sum[0] = 0;
	for(i=1;i<=n;i++){
		scanf("%d", &a[i]);
		sum[i] = sum[i-1]+a[i];
	}
	for(i=1;i<=n;i++){
		p[++top].l = i;
		p[top].r = i;
		p[top].ave = a[i];
		while(top>=2 && p[top].ave < p[top-1].ave)
		{
			p[top-1].ave = (sum[p[top].r]-sum[p[top-1].l-1])/(p[top].r-p[top-1].l+1);
			p[top-1].r = p[top].r;
			top--;
		}
	}
	while(top){
		for(j=p[top].l;j<=p[top].r;j++)
			ans[j] = p[top].ave;
		top--;
	}
	for(i=1;i<=n;i++)
		printf("%.10f\n", ans[i]);
	return 0;
}