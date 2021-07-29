//数论
//有k个人，n个糖，每个人轮流拿x个糖，知道没有x个糖为止
//其中每个人最多拿d次，x最大为m，求第一个人最多拿多少个 
//d的范围为1~1000，可以考虑从d入手，枚举d，即枚举第一个人
//能拿的次数i，则所有人总共拿的次数为[i+(i-1)*(k-1),i*k]次
//则每次可以拿[n/(i*k),n/(i+(i-1)*(k-1))]个，第一人拿i次 
//其最后就能拿i*n/(i+(i-1)*(k-1))个，不过需要注意最多只能 
//拿m个的限制
//另外需要注意(i-1)*(k-1)可能爆LL，而CF不能用__int128,所以
//需要判断一下
//PS：自己被自己拉的题目演了一波，主要就坑在上面那个点了 
//题目链接:https://codeforces.com/problemset/problem/965/C
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<unordered_map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6

using namespace std;
typedef unsigned long long LL;
typedef pair<int, int> P;
const int maxn = 100100;

int main()
{
	LL n, k, m, d, a, b, ans=0;
	scanf("%I64u %I64u %I64u %I64u", &n, &k, &m, &d);
	//枚举第一个人能拿i次 
	for(LL i=1;i<=d;i++)
	{
		//因为(i-1)*(k-1)可能爆LL，所以需要特殊判断一下 
		if(i>1 && (n-1)/(i-1) <= k-1)
			a=n+1;
		else
			a = i+(i-1)*(k-1);
		b = i*k;
		if(n/a<=m)ans = max(ans, n/a*i);
		if(n/i/k<=m)ans = max(ans, n/i/k*i);
		if(m>= n/i/k && m<=n/a)ans = max(ans, m*i);
	}
	printf("%I64u\n", ans);
	return 0;
}
