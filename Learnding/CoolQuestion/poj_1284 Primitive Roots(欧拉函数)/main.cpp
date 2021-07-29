//欧拉函数
//当一个数m有原根时，其原根的个数为phi(phi(m))
//题目链接：http://poj.org/problem?id=1284 
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
typedef pair<LL, int> P;
const int maxn = 660100;
const LL mod = 998244353;
int phi[maxn];
void euler();

int main()
{
	int n, ans, i;
	euler();
	while(~scanf("%d", &n))
		printf("%d\n", phi[n-1]);
	return 0;
}
//筛选欧拉函数 
void euler()
{
	int i, j, n = 66000;
	memset(phi, 0, sizeof(phi));
	phi[1] = 1;
	for(i=2;i<=n;i++)
		if(!phi[i])
			for(j=i;j<=n;j+=i){
				if(!phi[j])
					phi[j] = j;
				phi[j] = phi[j]/i*(i-1);
			}
}
