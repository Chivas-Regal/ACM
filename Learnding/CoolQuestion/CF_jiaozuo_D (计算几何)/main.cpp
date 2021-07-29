//计算几何
//2018.icpc焦作D
//这道题的切入点在于车在出弯的一刻，车头与弯道的结束重合
//那么弯道的起点到车的最外面的一个点，只要保证那个点在
//弯道内即可
//主要有两种情况，一种是车在出弯时那个点是在弯道内，那样的话
//道路宽度即为最外点到原点的距离减去半径
//如果那个点在弯道内，则可以根据投影来求出大圆半径，然后减去r 
//题目链接：http://codeforces.com/gym/102028/problem/D 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) printf("debug:%d\n", x);
#define INF 0x3f3f3f3f
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<LL, int> P;
const int maxn = 100100;
const LL mod = 998244353;
const double pi = acos(-1.0);

int main()
{
	int t;
	double a, b, r, d, ts;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lf %lf %lf %lf", &a, &b, &r, &d);
		//将d转化为弧度制 
		d = d*pi / 180;
		//求圆心到最外点的距离 
		double dis = sqrt(b*b+(a+r)*(a+r));
		//根据余弦定理求出最外点的连线与弯道结束连线的弧度 
		double cosa = (2*(a+r)*(a+r))/(2*(a+r)*dis);
		double ang = acos(cosa);
		//如果车在出弯时，最外点在弯内，则直接减去r 
		if(ang <= d+eps){
			printf("%.6f\n", dis - r);
		}
		//如果车载出弯时，最外点在弯外，则先通过投影求其弯道大圆半径，再减去r 
		else{
			printf("%.6f\n", dis*cos(ang-d) - r);
		}
	}
	return 0;
}
