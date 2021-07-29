/******************************
博弈
对于非空盒子A，和另一个盒子B，满足B<A && (A+B)%2=1 && (A+B)%3=0，可以将A中
至少一个物品移动至盒子B中，最后一次可以移动的获胜。

思路：通过转移图可以发现，只有1,3,4的盒子里是不能移动的，所以放入1,3,4盒子就相当于
移除，然后其余的物品都可以转移至1,3,4的盒子里所以对%6余数不为1,3,4的进行nim博弈即可


题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=3389
*********************************/
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
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 10010;
const int mod = 1000000007;
int a[maxn];

int main()
{
	int t, n, i, j, k;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		scanf("%d", &n);
		int num = 0;
		for(i=1;i<=n;i++)
		{
			scanf("%d", &a[i]);
			if(i % 6 == 0 || i % 6 == 2 || i % 6 == 5)
				num ^= a[i];
		}
		if(num) printf("Case %d: Alice\n", z);
		else printf("Case %d: Bob\n", z);
	}
	return 0;
}