//ŷ������
//��Ŀʵ�������������a^a^a^a...,�ܹ�b����Ȼ���mȡ��
//����a��b���ݶ�pȡ�࣬���gcd(a,p) == 1��ԭʽ����a��(b%phi[p])%p;
//��������ʣ���b<phi[p],�����a��b����%p 
//����Ϊa��b%phi[p]+phi[p]�Ĵ���%p
//�ر���Ҫע����ǣ����b��0������Ҫ�������phi[p]
//��Ŀ���ӣ�https://nanti.jisuanke.com/t/41299 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<":"<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1001000;
const LL mod = 998244353;
LL phi[maxn], aa[maxn], n;
LL Pow(LL a, LL b, LL m);
void euler();
LL gcd(LL a, LL b);
LL solve(int b, int n, LL m);

int main()
{
	int t, n;
	LL a, b, m;
	euler();
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld %lld %lld", &a, &b, &m);
		if(a == 1 || b == 0)
			printf("%lld\n", 1LL%m);
		else if(b == 1)
			printf("%lld\n", a % m);
		else
		{
			for(int i=0;i<b;i++)
				aa[i] = a;
			LL ans = solve(0, b, m);
			printf("%lld\n", ans%m);
		}
		
	}
	return 0;
}
//ŷ������ 
LL solve(int b, int n, LL m)
{
	if(phi[m] == 1LL)return aa[b];
	LL ans;
	//���ֻʣ�������Ͳ����ڵݹ��� 
	if(b == n-2)
		ans = aa[n-1];
	else
	   ans = solve(b+1, n, phi[m]);
	if(gcd(aa[b], m) == 1LL){
		if(ans == 0)ans += phi[m];
		ans = Pow(aa[b], ans%phi[m], m);
	}
	else if(ans < phi[m] && ans!= 0)
		ans = Pow(aa[b], ans%phi[m], m);
	else
		ans = Pow(aa[b], ans%phi[m]+phi[m], m);
	return ans;
}

LL Pow(LL a, LL b, LL m)
{
	LL n=1LL;
	while(b>0)
	{
		if(b%2)n = n*a % m;
		a = a*a%m;
		b /= 2;
	}
	return n;
}

void euler()
{
	int i, j, n = 1000010;
	memset(phi, 0, sizeof(phi));
	phi[1] = 1;
	for(i=2;i<=n;i++)
		if(!phi[i])
			for(j=i;j<=n;j+=i){
				if(!phi[j])
					phi[j] = (LL)j;
				phi[j] = phi[j]/i*(i-1);
			}
}

LL gcd(LL a, LL b)
{
	LL k;
	do{
		k = a % b;
		a = b;
		b = k;
	}while(k!=0);
	return a;
}
