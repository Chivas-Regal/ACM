/******************************************** 
�����ѧ+˼·
��һ��n*m�ľ���ÿ��λ�õ�������Ϊ[1,k],����great cellΪ
һ�������������к��е��������������󡣶���AgΪ����
�й���g��great cell���ķ���������A0*1+A1*2+A2*3+...+An*m*(n*m+1)
��⣺ ���ȿ��ܻῼ����Aiÿ���ж��ٸ���Ȼ�����������ʽ�ӽ���
���㣬�����ֺ���great all�϶��ʱ�򣬼�����������鷳������
Ŀ��ʽ�����Է��ֶ���ÿ�־�����������great cell�������
�𰸹���1��Ȼ�����ÿ��greater cell����Դ𰸹���1�Σ����һ��
������g��great cell����˾�����Թ���g��1(����������ظ�����g��)��
���Կ��Կ���ö��ÿ��λ��Ϊgreat cell����λ�ÿ���Ϊ[1,k]��
��great cell��λ����n*m�����������ǰλ��Ϊiʱ��ͬ��ͬ�е�����
λ�ÿ���Ϊ[1,i-1]������λ�ÿ���Ϊ[1,k]�֣����Թ���
n*m*((i-1)^(n+m-2))*(k^(n*m-n-m+1))����ͬʱ���ϲ�����great cell
�е�k^(n*m)���ɡ�
PS��˵�������ѧ����ʵ�������˼· 
��Ŀ���ӣ�https://codeforces.com/gym/101194 
*******************************************/ 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<deque>
#include<map>
#include<iostream>
#include<iterator> 
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 300100;
const int mod = 1000000007;
LL Pow(LL a, LL b);

int main()
{
	int t, n, m, i, j, k;
	LL ans;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		scanf("%d %d %d", &n, &m, &k); 
		ans = Pow(k, n*m);
		for(i=1;i<=k;i++)
		{
			LL tmp = (n*m*Pow(i-1, n+m-2)%mod)*Pow(k, n*m-(n+m-1))%mod;
			ans = (ans + tmp)%mod;
		 } 
		 printf("Case #%d: %lld\n", z, ans);
	}
	return 0;
}

LL Pow(LL a, LL b)
{
	LL n = 1;
	while(b)
	{
		if(b%2)n=n*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return n;
}
