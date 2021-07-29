/*********************************************
二分+尺取
有n个数，第i个数为ai，从序列中取连续的一段数，将其中第k大的数
加入集合b(如果不存在第k大的数则忽略),求集合b第m大的数。
思路：二分答案，求结果>=x的区间组合有多少个，如果大于等于m，
更新左区间为mid，否则右区间更新为mid-1。对于求第k大数>=x的区间
有多少个，可以利用尺取法，对于左区间为l，若到右区间r中>=mid的
数大于等于k，则区间第k大数>=mid的区间组合共有n-r+1个(即左区间
为l，右区间为[r,n]都可以，可以保证区间第k大的数>=mid)。
题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=6231
**********************************************/
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
const int maxn = 100100;
const int mod = 998244353;
int a[maxn];
bool isok(int mid, int n, int k, LL m);

int main()
{
	int t, n, k, i, j, l, r;
	LL m;
	scanf("%d", &t);
	while(t--)
	{
		l = INF, r = 0;
		scanf("%d %d %lld", &n, &k, &m);
		for(i=0;i<n;i++){
			scanf("%d", &a[i]);
			r = max(r, a[i]);
			l = min(l, a[i]);
		}
		while(l<r)
		{
			int mid = (l+r+1)/2;
			if(isok(mid, n, k, m))
				l = mid;
			else
				r = mid-1;
		}
		printf("%d\n", l);
	}
	return 0;
}

bool isok(int mid, int n, int k, LL m)
{
	int num, l, r;
	LL sum = 0;
	num = l = r = 0;
	while(l<n)
	{
		while(r < n && num < k){
			if(a[r] >= mid)num++;
			r++;
		}
		//不能使第k大数>=mid，跳出，避免加到计数器中
		if(num < k)break;
		//实际上右区间取[r-1,n-1]都满足区间第k大>=mid
		sum += n - r + 1;
		if(a[l] >= mid)num--;
		l++;
	}
	return sum >= m;
}