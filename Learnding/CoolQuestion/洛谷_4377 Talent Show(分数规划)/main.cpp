//分数规划
//最优比率背包问题
//有n个物品，每个物品有价值t，和重量w
//求找一些物品使t1+t2+...+tk与w1+w2+...+wk的比值最大，且
//w1+w2+...+wk>= W(已给出)
//思路：分数规划的经典模型，同样利用二分枚举L
//然后每个物品权值就变为d = t - L * w; 
//然后看是否存在满足条件的组合使simga(d)>0
//如果有更新下界，没有则更新上界
//PS：题目一开始理解的使可以直接贪心的，对d值进行排序，贪心
//去最大的d，直到w的和大于等于W，后来发现使错的
//当下面的数据时，是错的
//W = 8
//d:2 -0.1 -0.5 -1.5 
//w:4   1    2    4  
//题目链接：https://www.luogu.org/problem/P4377
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
const int maxn = 300;
double d[maxn], dp[1020]; 
int w[maxn], t[maxn];
bool check(double mid, int w, int n);

int main()
{
	int n, W, i, j, sum;
	double l, r;
	scanf("%d %d", &n, &W);
	for(i=1;i<=n;i++)
		scanf("%d %d", &w[i], &t[i]);
	//二分找出最大的L 
	l = 0.0, r = 10000000.0;
	while(r-l>eps)
	{
		double mid = (l+r)/2;
		if(check(mid, W, n))	
			l = mid;
		else
			r = mid;
	}
	printf("%d\n", (int)(l*1000));
	return 0;
}
//背包检查L为mid时，是否存在d的和大于0的组合 
bool check(double mid, int W, int n)
{
	int i, j, k;
	for(int i=1;i<=n;i++){
		d[i] = t[i] - mid * w[i];
	}
	//将dp数组初始化为一个极小值 
	for(i=0;i<=W;i++)
		dp[i] = -INF;
	dp[0] = 0;
	for(i=1;i<=n;i++){
		for(j=W;j>=0;j--){
			//更新数组 
			int k = min(W, j+w[i]);
			dp[k] = max(dp[k], dp[j]+d[i]);
		}
	}
	return dp[W] >= 0;
}
