//DP
//求一个只包含AB的串，其子串的每个字母都是一个回文串的一部分
//求合理的子串的数量
//思路：考虑求总的方案数减去不合理的方案数，可以发现如果是 
//ABBBBB、BAAAA、AAAAAAB、BBBBBBA这种是不合理的减去他们即可
//题目链接：https://codeforces.com/problemset/problem/1238/D 
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
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 300100;
char str[maxn];

int main()
{
	int n, i, j, up;
	LL ans;
	scanf("%d %s", &n, str);
	ans = (LL)n*(n-1)/2;
	up = 0;
	for(i=1;i<n;i++){
		//减去AAAAB，BBBBA这种形式的不合理的数量
		//因为AB会与下面重复减，所以ans需要+1 
		if(str[i] != str[i-1]){
			ans -= i-up-1;
			up = i;
		}
	}
	up = n-1;
	for(i=n-2;i>=0;i--){
		if(str[i] != str[i+1]){
			ans -= up - i;
			up = i;
		}
	}
	printf("%I64d\n", ans);
	return 0;
}
