/************************************************************
数论，组合数学
一个数k，将其先对2取余，然后除2，然后对3取余，再除3，一直到它为0为止，
运算时所有的余数可以组成一个集合(只保证无序，可以不互异)，问有多少个不同的数，进行同样操作后得到的数会和k得到的集合一样。

思路：假设k除以i余数为ai,那么k实际上就可以表示为1!*a2+2!*a3+...+(i-1)!*ai(ai>0,最后一个位置余数大于0)。可以先求出k的集合，然后算出该集合能得到的不同的数有多少个。设集合b，bi代表余数集合中余数为i的数有多少个。那么余数i可以放在除数大于i的位置。可以考虑，从大到小分配所有余数的位置，相乘即可。
例如集合{0,0,0,0,2,3,3,4}，除数分别为2,3,4,5,6,7,8,9。余数4可以放在除数5,6,7,8,9的位置，共有C(5,1)种。接下来余数3可以放在除数4,5,6,7,8,9的位置，但之前已经放过一个余数4了，所以共有C(5,2)种。余数2可以在除数3,4,5,6,7,8,9位置，但已放过余数3,3,4，所以共有C(4,1)种。剩下4个位置还有4个0，共有C(4,4)种可能，所有共有C(5,1)*C(5,2)*C(4,1)*C(4,4)个不同的数。
但因为上面没有考虑除数9的位置对应为0的情况，所以需要减去这种情况，将一个0放到最高，然后在进行一遍上述操作即可。

题目链接：https://codeforces.com/problemset/problem/1267/K
*************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
const int mod = 10007;
int a[24];
LL solve(int num);
LL C(int n, int m);

int main()
{
	int t, n, i, j, num;
	LL k;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%I64d", &k);
		i = 2, num = 0;
		memset(a, 0, sizeof(a));
		while(k)
		{
			a[k%i]++;
			k /= i;
			i++;
			num++;
		}
		LL ans = solve(num);
		//减去最高位余数为0的情况。
		if(a[0]){
			a[0]--;
			ans -= solve(num-1);
		}
		printf("%I64d\n", ans-1);
	}
	return 0;
}

LL solve(int num)
{
	LL res = 1;
	//sum:已用过的位置数量
	int sum = 0;
	for(int i=num+1;i>=1;i--)
	{
		//num+1-i-sum：余数i可以放的位置数量
		if(num+1-i-sum < a[i])return 0LL;
		res *= C(num+1-i-sum, a[i]);
		sum += a[i];
	}
	return res;
}
//求C(n,m)
LL C(int n, int m)
{
	LL c = 1LL;
	for(int i=0;i<m;i++)
		c = c*(n-i)/(i+1);
	return c;
}