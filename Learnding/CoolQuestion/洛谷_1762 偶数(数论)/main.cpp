/********************************************** 
����
���������ǰn�е�ż������mod10000003
��⣺���������ȴ����������������ż���д��
����0����ո񣬿��Կ���һ���ֲ��ͼ�Σ����£� 
1
1 1
1   1
1 1 1 1
1       1
1 1     1 1
1   1   1   1
1 1 1 1 1 1 1 1 
�������������Կ�������2^n,����2^n��������2^n��ͼ��
�ϲ��ģ����Զ�����n�������������������ȥ���������� 
���������n���ֽ�nΪ2^a1+2^a2+...+2^an�������������λ
��1�����Ӧ��2^a1ʱǰ���Ӧ�������������ڶ���1����2����
2^a2��Ӧ����������....
��Ŀ���ӣ�https://www.luogu.org/problem/P1762
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
	/*�˲���Ϊ������������ż�Ե�ͼ 
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
