/****************************************** 
单调队列
有一个r*w的矩阵，需要选出一块n*n的正方形，使选中的区域中
最大值与最小值的差最小
思路：题目关键在于求出n个数字中最大和最小的，对于原矩阵
先求出以a[i][j]为起始位置的向右n个中最大的数，存为b[i][j]
(如果i其实取不到n个则舍弃)，则b[i][j]可能为以i,j为所选
矩阵左上角的矩阵的最大值。然后在b[i][j]中求b[i][j]向下
n个数中的最大值。
整体利用了分块的思想吧，对于每个r*w向有可以取n个的所有点
先求出一行1*n的区域的最大值，然后再对1*n的区域进行同样操作
可以得到n*n的区域内的最大值，最小值类似。
 
单调队列：
单调队列可以在1~w个数中，求以i为起点，连续n个数中的最大(小)值
以下以求最大值为例： 
具体实现利用了双端队列，队列维护一个递减的序列初始队列为空，
队列中的每个元素维护两个值，一个是数值，一个是位置 
对于一个数a[i]，因为有n个的限制，所以需要从队首开始，将队列中
取不到i的元素全部弹出，
然后把队列中比a[i]小的数全部弹出，然后将a[i]放入 
队列尾部，然后以i开头，连续n个数的最大值即为当前队列中首元素的
数值

下面是一个实例帮助理解：
对于序列5 3 4 6 1，求以i为起始点的，连续3个数的最大值
({(id,val)}代表队列，(id,val)代表队列中的一个元素,id为位置，val为值)
i=1:放入5，     				{(1,5)}
i=2:3大于队尾元素放入3 			{(1,5),(2,3)}
i=3:4大于队尾元素，将(2,3)弹出 	{(1,5),(3,4)}
i=4:1开始不能取到4，弹出(1,5)，6大于队尾元素，弹出(3,4)，队列为空
	放入6 						{(4,6)} 
i=5:1小于队尾元素值，放入队列   {(4,6),(5,1)}

题目链接： https://vjudge.net/problem/SCU-3636
*******************************************/ 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<deque>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1520;
const int mod = 1;
struct node{
	int id, mx;
	node(){}
	node(int a, int b){
		id = a, mx = b;
	}
}; 
//b[i][j]：i，j为n*n区域左上角，区域中最大值
//c[i][j]：i，j为n*n区域左上角，区域中最小值
int a[maxn][maxn], b[maxn][maxn], c[maxn][maxn];
void sovlemx(int r, int w, int n);
void sovlemi(int r, int w, int n);

int main()
{
	int r, w, n, i, j, ans;
	while(~scanf("%d %d %d", &r, &w, &n))
	{
		for(i=0;i<r;i++)
			for(j=0;j<w;j++)
				scanf("%d", &a[i][j]);
		sovlemx(r, w, n);
		sovlemi(r, w, n); 
		ans = b[0][0] - c[0][0];
		for(i=0;i+n-1<r;i++)
		{
			for(j=0;j+n-1<w;j++)
				ans = min(ans, b[i][j]-c[i][j]);
		}
		printf("%d\n", ans);
	}
	return 0;
}

void sovlemx(int r, int w, int n)
{
	int i, j;
	deque<node> que;
	for(i=0;i<r;i++)
	{
		//清空队列 
		while(!que.empty())que.pop_back();
		//先将前n个数放入队列 
		que.push_back(node(0, a[i][0]));
		for(j=1;j<n;j++)
		{
			//将队尾小于a[i][j]的弹出队列 
			while(!que.empty() && que.back().mx < a[i][j])
				que.pop_back();
			que.push_back(node(j, a[i][j]));
		}
		b[i][0] = que.front().mx;
		for(;j<w;j++)
		{
			//将不能取到j位置的元素弹出 
			while(!que.empty() && que.front().id+n-1 < j)que.pop_front();
			while(!que.empty() && que.back().mx < a[i][j])
				que.pop_back();
			que.push_back(node(j, a[i][j]));
			b[i][j-n+1] = que.front().mx;
		}
	}
	for(j=0;j+n-1<w;j++)
	{
		while(!que.empty())que.pop_back();
		que.push_back(node(0, b[0][j]));
		for(i=1;i<n;i++)
		{
			while(!que.empty() && que.back().mx < b[i][j])
				que.pop_back();
			que.push_back(node(i, b[i][j]));
		}
		b[0][j] = que.front().mx;
		for(;i<r;i++)
		{
			while(!que.empty() && que.front().id+n-1 < i)que.pop_front();
			while(!que.empty() && que.back().mx < b[i][j])
				que.pop_back();
			que.push_back(node(i, b[i][j]));
			b[i-n+1][j] = que.front().mx;
		}
	}
}

void sovlemi(int r, int w, int n)
{
	int i, j;
	deque<node> que;
	for(i=0;i<r;i++)
	{
		while(!que.empty())que.pop_back();
		que.push_back(node(0, a[i][0]));
		for(j=1;j<n;j++)
		{
			while(!que.empty() && que.back().mx > a[i][j])
				que.pop_back();
			que.push_back(node(j, a[i][j]));
		}
		c[i][0] = que.front().mx;
		for(;j<w;j++)
		{
			while(!que.empty() && que.front().id+n-1 < j)que.pop_front();
			while(!que.empty() && que.back().mx > a[i][j])
				que.pop_back();
			que.push_back(node(j, a[i][j]));
			c[i][j-n+1] = que.front().mx;
		}
	}
	for(j=0;j+n-1<w;j++)
	{
		while(!que.empty())que.pop_back();
		que.push_back(node(0, c[0][j]));
		for(i=1;i<n;i++)
		{
			while(!que.empty() && que.back().mx > c[i][j])
				que.pop_back();
			que.push_back(node(i, c[i][j]));
		}
		c[0][j] = que.front().mx;
		for(;i<r;i++)
		{
			while(!que.empty() && que.front().id+n-1 < i)que.pop_front();
			while(!que.empty() && que.back().mx > c[i][j])
				que.pop_back();
			que.push_back(node(i, c[i][j]));
			c[i-n+1][j] = que.front().mx;
		}
	}
}

