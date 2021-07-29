/********************************************** 
数论
求杨辉三角前n行的偶数个数mod10000003
题解：数论上来先打表，如果对杨辉三角奇偶进行打表，
对于0输出空格，可以看出一个分层的图形，如下： 
1
1 1
1   1
1 1 1 1
1       1
1 1     1 1
1   1   1   1
1 1 1 1 1 1 1 1 
继续分析表，可以看出对于2^n,下面2^n行是两个2^n的图形
合并的，所以对于数n，可以求出其总数，减去奇数的数量 
对于所求的n，分解n为2^a1+2^a2+...+2^an，二进制下最高位
的1，则对应有2^a1时前面对应的奇数数量；第二个1包含2倍的
2^a2对应的奇数数量....
题目链接：https://www.luogu.org/problem/P1762
***********************************************/ 
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
const int maxn = 150;
const int mod = 1000003;
LL t[maxn], tp[maxn];
int a[150][150];

int main()
{
	int i, j;
	/*此部分为打表杨辉三角奇偶性的图 
	for(i=0;i<=100;i++)
	{
		int num = 0;
		a[i][0] = a[i][i] = 1;
		for(j=1;j<i;j++)
			a[i][j] = (a[i-1][j]+a[i-1][j-1])%2;
		for(j=0;j<=i;j++)
			if(a[i][j]%2 == 1)
				printf("1 ");
			else
				printf("  ");
		printf("\n");
	}*/
	t[0] = 1;
	for(i=1;i<=62;i++)
		t[i] = t[i-1]*2;
	tp[0] = 1;
	for(i=1;i<=62;i++)
		tp[i] = tp[i-1]*3%mod;
	LL n, ans, p, sum;
	scanf("%lld", &n);
	ans = 0, p = 1;
	if(n % 2 == 1)
		sum = ((n+1)/2%mod)*(n%mod)%mod;
	else
		sum = ((n+1)%mod)*((n/2)%mod)%mod;
	for(i=62;i>=0;i--)
	{
		if(n >= t[i])
		{
			n -= t[i];
			ans = (ans+p*tp[i]%mod) %mod;
			p = p * 2 % mod;
		}
	}
	sum = ((sum-ans)%mod+mod)%mod;
	printf("%lld\n", sum);
	return 0;
}
/*
1
1 1
1   1
1 1 1 1
1       1
1 1     1 1
1   1   1   1
1 1 1 1 1 1 1 1
1               1
1 1             1 1
1   1           1   1
1 1 1 1         1 1 1 1
1       1       1       1
1 1     1 1     1 1     1 1
1   1   1   1   1   1   1   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1                               1
1 1                             1 1
1   1                           1   1
1 1 1 1                         1 1 1 1
1       1                       1       1
1 1     1 1                     1 1     1 1
1   1   1   1                   1   1   1   1
1 1 1 1 1 1 1 1                 1 1 1 1 1 1 1 1
1               1               1               1
1 1             1 1             1 1             1 1
1   1           1   1           1   1           1   1
1 1 1 1         1 1 1 1         1 1 1 1         1 1 1 1
1       1       1       1       1       1       1       1
1 1     1 1     1 1     1 1     1 1     1 1     1 1     1 1
1   1   1   1   1   1   1   1   1   1   1   1   1   1   1   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
*/
