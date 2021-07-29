/********************************************
贪心
有n个盒子，第i个盒子里有ai个物品，每次移动可以将1个物品
向左或向右移动一个位置，求最小的移动次数使每个盒子里的物品都能
整除k(k>1)，可以为空，如果不能输出-1。
题解：显然，当所有的糖果数<=1时，输出-1；当糖果总数sum>=2时，则
解一定是存在的。对于解存在的情况，考虑枚举sum的素因数(对于不是素数的
因数，思考一下可以发现其结果一定不会比组成其的素因数更优)，求出当k为
其素因数时满足条件的最小移动步数，取最小即为解。同时因为sum非常大，
可以考虑使用sqrt(sum)的复杂度暴力枚举其素因数。
题目链接：https://codeforces.com/contest/1255/problem/E2
***********************************************/
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
const int maxn = 1001000;
const int mod = 998244353;
int a[maxn], b[maxn];
LL solve(LL s1, int n);
 
int main()
{
    int n, i, j;
    LL ans, mi, sum;
	ans = sum = 0LL;
    scanf("%d", &n);
    for(i=1;i<=n;i++){
        scanf("%d", &a[i]);
        sum+=a[i];
    }
    if(sum < 2)
        printf("-1\n");
    else{
        if(sum < 4)
			ans = solve(sum, n);
		else{
			LL k = sqrt(sum*1.0)+0.000001;
			//枚举素因数
			//考虑sum是大素数的情况
			ans = solve(sum, n);
			for(LL i=2;i<=k;i++){
				if(sum % i == 0)
				{
					while(sum % i == 0)sum /= i;
					ans = min(ans, solve(i, n));
					if(sum != 1)ans = min(ans, solve(sum, n));
				}
			}
		}	
        printf("%I64d\n", ans);
    }
    return 0;
}
//返回当每个盒子内都为s1的倍数时，最少需要的移动步数
LL solve(LL s1, int n)
{
    int i, j, mx;
    LL s2, num, mi, l, ans = 0;
    for(i=1;i<=n;i++)b[i] = a[i];
	i = 1;
	while(i<=n)
	{
		b[i] %= s1;
		//如果当前位为空，则跳过
		if(b[i] == 0){
			while(b[i] == 0 && i<=n)i++;
			continue;
		}
		//从当前位开始找s1个物品
		s2 = num = 0;
		for(j=i;j<=n;j++){
			if(num+b[j] < s1)
				num += b[j], s2 += (LL)b[j]*(j-i);
			else{
				b[j] -= s1 -num;
				s2 += (s1-num)*(j-i);
				mx = j;
				break;
			}
		}
		mi = s2, l = b[i];
		//将s1个物品移动至一个盒子中，则代价最小一定在[i,mx]中的某个位置
		for(j=i+1;j<=mx && j<=n;j++){
			s2 += l - (s1 - l);
			mi = min(mi, s2);
			l += b[j];
		}
		ans += mi;
		if(b[mx] == 0)
			i = mx + 1;
		else i = mx;
	}
    return ans;
}