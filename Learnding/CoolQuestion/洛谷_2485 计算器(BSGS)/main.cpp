//BSGS+EXGCD+快速幂
//写个计算器，能实现三种操作
//实际上这题就是把三种算法强行合在一个题里
//求y^z % p , 可以用快速幂
//求xy % p = z，求x，可以用扩展欧几里德算法
//求y^x % p = z % p, 求x，可以用BSGS算法
//BSGS算法：
//主要利用分块的思想，将y^x%p = z%p变为
// => y^(am-b) % p = z % p
// => y^(am)   % p = z*y^b % p
//变成这样后首先枚举b的值(0~m-1)，将得到的值存起来(map或hash)
//然后枚举左边的a的值，求左式的值，如果存在b使右式的值
//等于左式，则am-b为一组解
//m一般选取sqrt(p)，可以得到一个较为优秀的时间复杂度 
//题目链接：https://www.luogu.org/problem/P2485
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
	//枚举b的取值，将其存入map中 
	tmp1 = z;
	for(int i=1;i<=m;i++){
		tmp1 = tmp1 * y % p;
		mp[tmp1] = i;
	}
	tmp1 = tmp2 = 1;
	tmp2 = Pow(y, m, p);
	//枚举a的值，看a是否存在与右式相等的取值 
	for(LL i=m;i-m<p-1;i+=m)
	{
		tmp1 = tmp1 * tmp2 % p;
		if(mp.count(tmp1))
			return i-mp[tmp1];
	}
	return -1;
}
