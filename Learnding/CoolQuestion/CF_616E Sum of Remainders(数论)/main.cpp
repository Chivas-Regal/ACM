//���� 
//��n%1 + n%2 + n%3 + ...... + n%m
//����ؼ������뵽����n%1 + n%2 + .... + n%(min(n,m))����
//Ȼ�����ÿ������ת��Ϊn - n/i*i;
//һֱ�ۼӵ�m����n*m - (n/1*1+n/2*2 + ... + n/m*m)
//���Է��������ڵ���һ���ǵȲ����У���Ȼ����ĳЩi���Է���n/i���
//���ߴ����� 
//����Ϊn/i+i, �����±�Ϊi��β���±�Ϊmin(n/(n/i), m)
//Ȼ����͹�ʽ�ͺ��ˣ�ע������������ȼ�����
//��Ŀ���ӣ� http://codeforces.com/contest/616/problem/E
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
#define dbg(x) printf("debug:%d\n", x);
#define INF 0x3f3f3f3f
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1000100;
const int mod = 1000000007;

int main()
{
	LL ans = 0, sum = 0, n, m, k;
	scanf("%I64d %I64d", &n, &m);
	ans = ((n%mod) * (m%mod))%mod;
	m = min(n, m);
	sum = 0;
	for(LL i=1;i<=m;){
		LL l = i, r = min(n/(n/i), m);
		LL a1 = n/i*i, d = n/i;
		//ע�������ȼ����� 
		if((r-l)%2 == 0)
			sum = (sum+((r-l+1)%mod * (a1 %mod)) %mod + (((((r-l)/2)%mod)*((r-l+1)%mod)%mod) * d)%mod)%mod;
		else
			sum = (sum+((r-l+1)%mod * (a1 %mod)) %mod + ((((r-l)%mod)*(((r-l+1)/2)%mod)%mod) * d)%mod)%mod;
		i = r+1;
	}
	printf("%I64d\n", ((ans-sum)%mod+mod)%mod);
	return 0;
}

