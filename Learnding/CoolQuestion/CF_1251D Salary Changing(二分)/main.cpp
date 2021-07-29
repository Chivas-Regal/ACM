//二分
//有n个数(待定)，每个位置的数的值在[li,ri]，并且所有位置
//的数的和加起来小于等于s，求这些数中位数最大为多少
//题解：很容易想到二分，但和平常有点不一样，对于检验的 
//值mid，如果得到的中位数在满足限制的条件下大于等于mid
//就认为此方案合理
//至于检查很容易想，对于每个数mid，需要构造所有的数尽可能
//小，对于ri小于mid的，让其作为中位数的左半部分，直接
//取值为li。
//其余的数都尽量取mid，如果li>mid,则取mid，先假设其为右半部分 
//如果已确定在左半部分的数大于n/2， 则为假，(因为这些数一定小于mid
//数量大于n/2，则中位数也小于mid了)
//如果已确定的左半部分的数小于n/2，则将尽量的将右边的转移到
//左半部分，同时为了总和最小，应选li尽量小的
//题目链接：https://codeforces.com/contest/1251/problem/D
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
const int mod = 998244353;
struct node{
	int l, r;
}p[maxn];
int b[maxn];
bool isok(LL mid, LL s, int n);

int main()
{
	int t, n, i, j;
	LL s, l, r;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %I64d", &n, &s);
		for(i=0;i<n;i++)
			scanf("%d %d", &p[i].l, &p[i].r);
		l = 0, r = INF;
		while(l<r)
		{
			LL mid = (l+r+1)/2;
			if(isok(mid, s, n))
				l = mid;
			else
				r = mid-1;
		}
		printf("%I64d\n", l);
	}
	return 0;
}
//检验是否存在中位数大于等于mid的合理方案 
bool isok(LL mid, LL s, int n)
{
	int i, j, a1=0, top = 0;
	LL sum = 0;
	for(i=0;i<n;i++)
	{
		//r小于mid，则只能作为左半部分，取最小值即可 
		if(p[i].r < mid)
		{
			a1++;sum += p[i].l;
		}
		//将可以取到大于等于mid的数先作为右半部分 
		else
		{
			b[top++] = p[i].l;
			sum += max(mid, (LL)p[i].l);
		}
	}
	//小于mid的数超过一半，则中位数也一定小于mid 
	if(a1 > n/2)return false;
	sort(b, b+top);
	i = 0;
	//将一些右半部分的数转移至左半部分，同时为了最小化
	//sum，应该取li尽量小的 
	while(i<top && b[i]<= mid && a1 < n/2)
	{
		sum -= mid-b[i];
		i++, a1++;
	}
	return sum <= s;
}
