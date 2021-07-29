//暴力
//选q-2个位置，可以统计出每个位置的人数，然后
//暴力枚举两个人，将两个人的区间减去，取最大的
//暴力减去区间会超时，所以需要预处理出各个位置只有
//一个人和两个人的数量，然后用n1[r]-n1[l-1]表示区间
//[l,r]中只有一（二）个人的数量
//题目链接：http://codeforces.com/contest/1132/problem/C
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;

int main()
{
	int n, q, i, j, res, ans, num;
	int a[5020], l[5020], r[5020], n0[5020], n1[5020], n2[5020];
	scanf("%d %d", &n, &q);
	memset(a, 0, sizeof(a));
	for(i=0;i<q;i++)
	{
		scanf("%d %d", &l[i], &r[i]);
		a[l[i]]++, a[r[i]+1]--;
	}
	j = n0[0] = n1[0] = n2[0] = num = 0;
	for(i=1;i<=n;i++)
	{
		j += a[i];
		a[i] = j;
		if(a[i])num++;
		n0[i] = n0[i-1]+(a[i]==0);
		//预处理出累加到i有多少个数量为1(2)的人数 
		n1[i] = n1[i-1]+(a[i]==1);
		n2[i] = n2[i-1]+(a[i]==2);
	}
	res = 0;
	for(i=0;i<q;i++)
		for(j=i+1;j<q;j++)
		{
			ans = num;
			//减去[l,r]内只有一个的数量 
			ans -= n1[r[i]]-n1[l[i]-1];
			ans -= n1[r[j]]-n1[l[j]-1];
			//如果两者有重合，则在减去数量为2的数量 
			int l1 = max(l[i],l[j]), r1 = min(r[i], r[j]);
			if(l1<=r1)ans -= n2[r1]-n2[l1-1];
			res = max(res, ans);
		}
	printf("%d", res);
	return 0;
}
