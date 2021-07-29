//数论
//x*x+y*y=n 或 x*x+y*y=n!，求是否存在合理的x，y使式子成立
//思路：定理：对于x*x+y*y=n，
//n可以分解为p1^a1 * p2^a2 * ... * pn^an
//若ai为奇数，且对应的pi%4 == 3 则n无解
//知道上面的定理即可，然后删选素数，将n或n!分解即可
//题目链接：https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1149
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
const int maxn = 10001000;
const int mod = 998244353;
int top, vis[maxn], pr[1000000];
vector<int> g;
void pretrean();
int getNum(int n, int pri);

int main()
{
	pretrean();
	int n, i, j, sig, num, z=0;
	char ch;
	while(~scanf("%d%c", &n, &ch))
	{
		sig = 1;
		if(z)printf("\n");z++;
		if(ch == '!')
		{
			g.clear();
			for(i=1;pr[i]<=n;i++)
			{
				if(pr[i] % 4 == 3)
				{
					int num = getNum(n, pr[i]);
					if(num % 2)
					{
						sig = 0;
						g.push_back(pr[i]);
					}
					if(g.size()>52)break; 
				}
			}
			if(sig)
				printf("He might be honest.\n");
			else
			{
				printf("He is a liar.\n");
				printf("%d", g[0]);
				for(i=1;i<g.size() && i<50;i++)
					printf(" %d", g[i]);
				printf("\n");
			}
		}
		else
		{
			for(i=1;n!=1;i++)
			{
				j = 0;
				while(n%pr[i] == 0)
					j++, n/=pr[i];
				if(j%2 && pr[i]%4 == 3)
				{
					sig = 0;break;
				}
			}
			if(sig)
				printf("He might be honest.\n");
			else
				printf("He is a liar.\n");
		}
	}
	return 0;
}
//筛选素数 
void pretrean()
{
	int n = maxn - 500;
	top = 0;
	for(int i=2;i<=n;i++)
	{
		if(vis[i] == 0)
		{
			pr[++top] = i;
			for(int j=i+i;j<=n;j+=i)
				vis[j] = 1;
		}
	}
}
//求n!分解后有多少个pri相乘 
int getNum(int n, int pri)
{
	int num = 0;
	while(n)
	{
		num += n / pri;
		n /= pri;
	}
	return num;
}
