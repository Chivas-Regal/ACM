//思路题 
//求每个数在包含其区间中是中位数的区间数
//对于每个数，需要求其左边有多少个大于它的数和
//多少个小于它的数，右边同理。如果其左边某个位置
//i和右边某个位置j，他们大于该数的数量等于小于该数
//的数量，总数可以加1
//题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=5701
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<vector>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 8020;
int a[maxn], add[2*maxn];

int main()
{
	int n, i, j, k;
	LL ans;
	while(~scanf("%d", &n))
	{
		for(i=0;i<n;i++)
			scanf("%d", &a[i]);
		for(i=0;i<n;i++)
		{
			ans = 1;
			//统计左区间的状态 
			memset(add, 0, sizeof(add)); 
			j=1, k=0;
			add[n]++;
			while(i-j>=0)
			{
				//大于该元素，k++;小于,k--
				if(a[i-j] > a[i])k++;
				else k--;
				if(k == 0)ans++;
				//统计状态出现次数 
				add[n+k]++;
				j++;
			}
			j=1, k=0;
			while(i+j<n)
			{
				if(a[i+j] > a[i])k++;
				else k--;
				//对于右区间状态k，总数加上左边的-k的状态数 
				ans += add[n-k];
				j++;
			}
			if(i)printf(" ");
			printf("%lld", ans);
		}
		printf("\n");
	}
	return 0;
}
/*
5
1 4 3 2 5
*/
