/********************************************************
DP

有长度为n的只包含小写字母的字符串，现在需要给每个位置的数另设一个值，相同字母的值不要求相等，
如果两个字母相邻，且他们的值不相等，则可以交换两个字母。问使字母串非降序，应该怎么赋值，使最大
的值最小？

思路：首先对于最大的字母，先将其设置为1，那么的后面的所有字母的数字都应该与它不同，这样才能保证
最大的字母到最后。排除最大的，再考虑次大的，如果最大的前面的次大的，可以与最大的相同，因为他们不需要
交换，最大的后面的次大的必须不同，同理次大的后面的字符必须与次大的不同。所以结论如下：
看样例猜题意可以发现，一个序列需要使用的数字数量，实际上就是最长非递减序列。至于每个位置应该
填的值，直接将DP数组输出即可。

题目链接：https://codeforces.com/problemset/problem/1296/E2
***************************************************************/
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
typedef pair<int, string> P;
const int maxn = 100100;
const int mod = 1000000007;
int dp[maxn];
char str1[maxn], str2[maxn];

int main()
{
	int n, i, j, k, pos, be, ed, mx=1;
	scanf("%d %s", &n, str1);
	ed = be = n;
	str2[be] = 'z'+1;
	for(i=0;i<n;i++)
	{
		pos = upper_bound(str2+be, str2+ed+1, str1[i])-str2;
		if(pos == be)be--;
		str2[pos-1] = str1[i];
		dp[i] = ed-pos+1;
		mx = max(mx, dp[i]);
	}
	printf("%d\n", mx);
	for(i=0;i<n-1;i++)
		printf("%d ", dp[i]);
	printf("%d\n", dp[n-1]);
	return 0;
}