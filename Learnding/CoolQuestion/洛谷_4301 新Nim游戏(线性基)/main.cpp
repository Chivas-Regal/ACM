/********************************************
线性基

有n堆火柴，第一次操作第一个人可以直接拿走若干个整堆的火柴，但不能拿完所有堆，
第二次操作第二个人可以直接拿走若干个整堆的火柴，同样也不能拿完。之后两个人进行
Nim博弈，问在保证第一个人必胜的情况下，第一回合最少拿多少根火柴。

思路：经过思考可以发现，第一个人是必胜的，只要第一回合结束后，留下的火柴堆中，
没有一个非空子集的异或和为0即可。所以只需要第一次将总和尽可能多的火柴堆留在
那里，且保证这些火柴堆的任意子集异或不为0。线性基有一个重要的性质就是线性基内
的异或集合中不存在0。所以构造一个线性基，使其总和最大即可。
考虑从大到小依次考虑每个元素，如果其能放到集合内，就放进去即可。

链接：https://www.luogu.com.cn/problem/P4301
************************************************/
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
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 120;
const int mod = 2008;
LL a[maxn], b[40];

int main()
{
	int t, n, i, j;
	LL ans = 0;
	scanf("%d", &n);
	for(i=0;i<n;i++)
		scanf("%lld", &a[i]);
	sort(a, a+n);
	for(i=n-1;i>=0;i--)
	{
		LL x = a[i];
		for(j=33;j>=0;j--)
			if(x & (1LL<<j))
			{
				if(b[j] == 0)
				{
					b[j] = x;break;
				}
				else x ^= b[j];
			}
		if(!x)ans += a[i];
	}
	printf("%lld\n", ans);
	return 0;
}