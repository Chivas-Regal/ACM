//BSGS+EXGCD+������
//д������������ʵ�����ֲ���
//ʵ����������ǰ������㷨ǿ�к���һ������
//��y^z % p , �����ÿ�����
//��xy % p = z����x����������չŷ������㷨
//��y^x % p = z % p, ��x��������BSGS�㷨
//BSGS�㷨��
//��Ҫ���÷ֿ��˼�룬��y^x%p = z%p��Ϊ
// => y^(am-b) % p = z % p
// => y^(am)   % p = z*y^b % p
//�������������ö��b��ֵ(0~m-1)�����õ���ֵ������(map��hash)
//Ȼ��ö����ߵ�a��ֵ������ʽ��ֵ���������bʹ��ʽ��ֵ
//������ʽ����am-bΪһ���
//mһ��ѡȡsqrt(p)�����Եõ�һ����Ϊ�����ʱ�临�Ӷ� 
//��Ŀ���ӣ�https://www.luogu.org/problem/P2485
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
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1001000;
LL Pow(LL a, LL b, LL mod);
LL BSGS(LL y, LL z, LL p);
LL exgcd(LL a, LL b, LL &x, LL &y);

int main()
{
	int t, op;
	LL y, z, p, d, a, b;
	while(~scanf("%d %d", &t, &op))
	{
		while(t--)
		{
			scanf("%lld %lld %lld", &y, &z, &p);
			if(op == 1){
				printf("%lld\n", Pow(y, z, p));
			}
			else if(op == 2){
				z %= p;
				d = exgcd(y, p, a, b);
				if(z % d != 0)
					printf("Orz, I cannot find x!\n");
				else{
					a = a*z/d;
					a = (a%(p/d)+p/d)%(p/d);
					printf("%lld\n", a);
				}
			}
			else{
				LL ans = BSGS(y, z, p);
				if(ans == -1 || y%p== 0 && z)
					printf("Orz, I cannot find x!\n");
				else
					printf("%lld\n", ans);
			}
		}
		
	}
	return 0;
}

LL Pow(LL a, LL b, LL mod)
{
	LL n= 1;
	while(b)
	{
		if(b%2)n = n*a % mod;
		a = a*a%mod;
		b /= 2;
	}
	return n;
}

LL exgcd(LL a, LL b, LL &x, LL &y)
{
	if(b == 0){
		x = 1, y = 0;
		return a;
	}
	LL d = exgcd(b, a%b, y, x);
	y -= a/b*x;
	return d;
}

LL BSGS(LL y, LL z, LL p)
{
	map<LL,LL> mp;
	y %= p;z %= p;
	if(y == 0)
		return y>1?-1:z==0&&p>1; 
	LL kz, m = sqrt(p), tmp1, tmp2;
	//ö��b��ȡֵ���������map�� 
	tmp1 = z;
	for(int i=1;i<=m;i++){
		tmp1 = tmp1 * y % p;
		mp[tmp1] = i;
	}
	tmp1 = tmp2 = 1;
	tmp2 = Pow(y, m, p);
	//ö��a��ֵ����a�Ƿ��������ʽ��ȵ�ȡֵ 
	for(LL i=m;i-m<p-1;i+=m)
	{
		tmp1 = tmp1 * tmp2 % p;
		if(mp.count(tmp1))
			return i-mp[tmp1];
	}
	return -1;
}
