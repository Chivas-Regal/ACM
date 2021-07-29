//Pollard_rho + Miller_Rabin�㷨
//��ʽ�ֽ�
//һֱx,y��gcd��lcm����x,y
//��s=lcm/gcd��ֻ��Ҫ��s�зֽ�Ϊ�������ص���
//��Ϊ���󣬵��������Ǵ�i=2��s�������϶��ᳬʱ
//������Ҫ����ֽ⣬�ҳ�����������
//�������Ҫʹ��Pollard_rho��Miller_Brain�㷨 
//https://blog.csdn.net/maxichu/article/details/45459533
//http://poj.org/problem?id=2429
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#include<iterator>
#include<queue>
#include<iostream>
#include<ctime>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
LL Pow(LL a, LL b, LL n);
LL Mul(LL a, LL b, LL n);
bool Miller_Rabin(LL n);
LL gcd(LL a, LL b);
LL pollard_rho(LL n, LL c);
void Find_fac(LL n);
void dfs(int i, LL x1);
LL a, b, s, m, ans1, ans2, len, c[150];
//fac�洢s���������� 
vector<LL> fac;

int main()
{
	while(~scanf("%lld %lld", &a, &b))
	{
		srand(time(0));
		fac.clear();
		len = 0;
		ans1 = 1;
		s = b / a;
		m = (LL)sqrt(s+0.0)+0.00006;
		Find_fac(s);
		int t = fac.size();
		for(int i=0;i<t;i++)
		{
			LL res = 1;
			while(s % fac[i] == 0)
			{
				s /= fac[i];
				res *= fac[i];
			}
			if(res!=1)c[len++] = res;
		}
		dfs(0, 1);
		printf("%lld %lld\n", ans1*a, b/ans1);
	}
	return 0;
}

void dfs(int i, LL x1)
{
	//printf("%d %lld\n", i, x1);
	if(x1>m)return;
	if(i == len)
	{
		ans1 = max(ans1, x1);
		return;
	}
	dfs(i+1, x1);
	dfs(i+1, x1*c[i]);
}

void Find_fac(LL n)
{
	if(n == 1) return;
	//ȷ����ǰ���Ƿ������� 
	if(Miller_Rabin(n))
	{
		fac.push_back(n);
		return;
	}
	LL p = n;
	int z=0;
	while(p>=n)
		p = pollard_rho(p, rand()%(n-1)+1);
	Find_fac(p);
	Find_fac(n/p);
}

//�ҳ�n��һ������ 
LL pollard_rho(LL n, LL c)
{
	//�������x0 
	LL i=1, x0 = rand()%n;
	LL y = x0, k =2;
	while(1)
	{
		i++;
		//+c!!+c!!+c���������� 
		x0 = (Mul(x0,x0, n)+c)%n;
		LL d = gcd(y-x0, n);
		//���gcd(y-x0,n)������1����n����d��n��һ������ 
		if(d!=1 && d!=n)return d;
		if(y == x0)return n;
		if(i == k)
		{
			y = x0;
			k+=k;
		}
	}
}

LL Pow(LL a, LL b, LL n)
{
	b %= n;
	LL m = 1;
	while(b>0)
	{
		if(b&1)m=Mul(m, a, n);
		b >>= 1;
		a = Mul(a, a, n);
	}
	return m;
}

LL Mul(LL a, LL b, LL n)
{
	a %= n, b %= n;
	LL m = 0;
	while(b>0)
	{
		if(b&1)
		{
			m += a;
			if(m >= n)m-=n;
		}
		b=b>>1;
		a <<= 1;
		if(a >= n)a-=n;
	}
	return m;
}

//�ж�һ�����Ƿ�Ϊ���� 
bool Miller_Rabin(LL n)
{
	if(n == 2)
		return true;
	else if(n<2 || !(n&1))
		return false;
	//����С����ŷ�������������� 
	LL m = n-1, j =0;
	while(m%2==0)
	{
		m /= 2;
		j++;
	}
	if(j>=1 && (m&1) == 1)
	{
		
		for(int i=1;i<20;i++)
		{
			LL a = rand()%(n-1)+1;
			//��a^m%n 
			LL x = Pow(a, m, n);
			LL y;
			for(int k=0;k<j;k++)
			{
				//y=a^(2^(k+1)*m)%n 
				y = Mul(x, x, n);
				//���y==1����x!=1��x!=n-1���� 
				if(y==1 && x!=1 && x!=n-1)
					return false;
				x = y;
			}
			if(y!=1)return false;
		}
	}
	return true;
}

LL gcd(LL a, LL b)
{
	if(a<0)return gcd(-a, b);
	LL k;
	do
	{
		k = a % b;
		a = b;
		b = k;
	}while(k!=0);
	return a;
 } 
