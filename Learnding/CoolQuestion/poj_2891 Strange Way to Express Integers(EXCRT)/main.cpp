//��չ�й�ʣ�ඨ��
//����x%m1 = a1, x%m2 = a2
//���Ժϲ�����k1*m1+a1 = x, k2*m2+a2 = x
//=> k1*m1-k2*m2=a2-a1
//=> d = gcd(m1,m2)
//=> ���(a2-a1)|d,����Ժϲ��������ܺϲ�
//=> ʹ��exgcd���k1*m1+a1ʹ���m2ȡ��Ϊa2
//=> ������ΪLCM(m1,m2)
//��Ŀ���ӣ� http://poj.org/problem?id=2891
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
const int maxn = 100100;
LL m[maxn], a[maxn];
LL exgcd(LL a, LL b, LL &x, LL &y);
LL exCRT(int n);

int main()
{
	int n, i, j;
	while(~scanf("%d", &n))
	{
		for(i=0;i<n;i++)
			scanf("%lld %lld", &m[i], &a[i]);
		LL ans = exCRT(n);
		printf("%lld\n", ans);
	}
	return 0;
}

LL exCRT(int n)
{
	for(int i=1;i<n;i++)
	{
		LL c, e, x, y;
		//���k1*m1-k2*m2=a2-a1
		c = exgcd(m[0], m[i], x, y);
		e = a[i]-a[0];
		if(e%c == 0)
		{ 
			//��������k1 
			x = e/c*x%m[i];
			while(x<0)x += m[i]/c;
			//��k1*m1+a1,ͬʱʹ���m2ȡ��Ϊa2 
			a[0] += m[0]*x;
			//��m1��Ϊlcm(m1,m2); 
			m[0] = m[0]/c*m[i];
			a[0] = (a[0]%m[0]+m[0])%m[0]; 
		}
		else
			return -1;
	}
	return a[0];
}

LL exgcd(LL a, LL b, LL &x, LL &y)
{
	if(!b){
		x=1,y=0;
		return a;
	}
	LL d = exgcd(b, a%b, y, x);
	y -= a/b*x;
	return d;
}
