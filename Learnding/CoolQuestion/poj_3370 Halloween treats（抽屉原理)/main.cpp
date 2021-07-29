//抽屉原理 
//资料http://www.cnblogs.com/ACShiryu/archive/2011/08/09/poj2356.html
//http://poj.org/problem?id=3370
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
typedef long long int ll;

int main()
{
	priority_queue<int, vector<int>, greater<int> > que;
	//vis为状态数组，每组数据将其所有位置初始为-1 
	int c, n, i, j, vis[100005]; 
	ll a[100005];
	while(scanf("%d %d", &c, &n),c!=0 && n!=0)
	{
		while(que.size())
			que.pop();
		for(i=1;i<=n;i++)
			scanf("%lld", &a[i]);
		memset(vis, -1, sizeof(vis));
		long long int sum = 0;
/*!!!!核心：sum为a[0]到a[i]的和，当sum%c为0时，则正好能分平均
当sum%c！=0时，则记录下第一次出现该余数时i的位置
当sum%c的余数前面已经出现过，则代表此时sum2-sum1可以正好整除人数（C）
sum2为第二次出现该余数的和，sum1为第一次
此时从vis数组vis[sum2%c]中的j,从j+1到此时的i之间所有数和可以整除C 
*/		 
		for(i=1;i<=n;i++)
		{
			sum += a[i];
			if(sum % c == 0)
			{
				for(j=1;j<=i;j++)
					que.push(j);
				break;
			}
			else if(vis[sum % c] != -1)
			{
				//该余数第二次出现 
				for(j=vis[sum %c]+1;j<=i;j++)
					que.push(j);
				break;
			}
			//将第一次出现该余数的下标记录下来。 
			vis[sum%c] = i;
		}
		if(que.size() == 0)
			printf("no sweets");
		else
		{
			i=0;
			while(que.size())
			{
				if(i)
					printf(" ");
				i++;
				int t = que.top();
				printf("%d", t);
				que.pop();
			}
		}
		printf("\n");
	 }
	return 0;
}
