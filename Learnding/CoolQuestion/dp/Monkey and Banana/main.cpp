//dp
//长方体虽然说数量不限，因为必须上面的长宽必须小于下面
//的长和宽，所以实际上只需要考虑三个不同面的情况，这样
//就化为01背包问题了。
//n最大是30，开100应该就足够，但实际上1020的空间
//不知为何仍会wrong answer 
//http://acm.hdu.edu.cn/showproblem.php?pid=1069
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
#define INF 0x3f3f3f3f
  
using namespace std;
typedef long long int ll;
typedef pair<int,int> P;
typedef struct
{
	int x, y, z;
}node;
node p[5020];
int num; 
void add(int x, int y, int z);
bool cmp(node a, node b);

int main()
{
    int n, i, j, z = 1, maxx, dp[5020];
    while(scanf("%d", &n), n!=0)
    {
    	memset(dp, 0, sizeof(dp));
    	num = maxx = 0;
    	for(i=0;i<n;i++)
    	{
    		int a[4]; 
    		scanf("%d %d %d", &a[1], &a[2], &a[3]);
    		//对数据进行排序，保证长大于等于宽 
    		sort(a+1, a+4);
    		add(a[1], a[2], a[3]);
    		add(a[2], a[3], a[1]);
    		add(a[1], a[3], a[2]);
		}
		//对数据排序，长比较大的靠前 
		sort(p, p+num, cmp);
    	for(i=0;i<num;i++)
    	{
    		//只考率i则高为p[i].z
    		dp[i] = p[i].z;
    		for(j=i-1;j>=0;j--)
    		{
    			//如果此方块可以放到前面的方块上 
    			if(p[i].x < p[j].x && p[i].y < p[j].y)
    			{
    				//j从i开始逐渐减小，dp[j]为只考虑到
					//第j个方块的最大值，如果能放上午，则
					//比较已有值和放在此上面的值 
    				dp[i] = max(dp[i], dp[j]+p[i].z);
				}
			}
			maxx = max(maxx, dp[i]);
		}
		printf("Case %d: maximum height = %d\n", z, maxx);
		z++;
	}
	return 0;
}

void add(int x, int y, int z)
{
	p[num].x = x;
	p[num].y = y;
	p[num].z = z;
	num++;
}

bool cmp(node a, node b)
{
	if(a.x == b.x)
		return a.y > b.y;
	return a.x > b.x;
}
