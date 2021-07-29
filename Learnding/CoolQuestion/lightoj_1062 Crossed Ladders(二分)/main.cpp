//二分
//看题意可能第一感觉是简单的数学问题，只要求个关系
//出来就行了，发现我求不出来。然后需要对底边进行二分，
//设x与左边楼的交点为A，与右边楼的交点为C，y与左边楼的交点为B，与右边楼的交点为D；
//x与y的交点为E，由E向地面做垂线，设垂足为F。
//由三角形相似：EF/AB=CF/CB=1-(BF/BC)=1-(EF/CD)，
//也就是EF/AB=1-(EF/CD)，两边同时除以EF
//摘自： https://blog.csdn.net/u011644423/article/details/38380573
//题目链接： http://lightoj.com/volume_showproblem.php?problem=1062
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
const int maxn = 220;

int main()
{
	int t, i, j, k, z;
	double a, b, c, l, r;
	scanf("%d", &t);
	for(z=1;z<=t;z++)
	{
		scanf("%lf %lf %lf", &a, &b, &c);
		l = 0, r = min(a, b);
		while(fabs(l-r)>1e-9)
		{
			double mid = (l+r)/2;
			//如果1/EF > 1/c,则EF<c 
			if(1/sqrt(a*a-mid*mid)+1/sqrt(b*b-mid*mid)>1/c)
				r = mid;
			else
				l = mid;
		}
		printf("Case %d: %.6f\n", z, l);
	} 
	return 0;
}
