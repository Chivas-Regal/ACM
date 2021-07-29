//计算几何，叉积
//有一段管道，第i个转折点坐标为(xi,yi)(x1<x2<x3<..<xn)
//第i个转折点下有(x1,yi-1) 
//从x1处射出一道光线，求最远能到x的坐标
//猜测射出的光线必定是2*n个点中两个点所在的直线
//暴力枚举所有点能组成的直线，求最远能到达的直线
//题目链接：http://poj.org/problem?id=1039 
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
#define dbg(x) printf("debug:%d\n", x);
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 25;
struct node{
	double x, y;
	node(){}
	node(double a, double b):x(a),y(b){
	}
}p[maxn];
double Cross(node a, node b, node c);
bool iscom(node a, node b, node c, node d);
double getPoint(node a, node b, node c, node d);
bool solve(int n, double &x, node a, node b);

int main()
{
	int n, i, j, sig;
	double x, ans;
	while(~scanf("%d", &n), n){
		sig = 1;
		for(i=1;i<=n;i++)
			scanf("%lf %lf", &p[i].x, &p[i].y);
		x = ans = p[1].x;
		p[0] = p[1];
		for(int i=1;i<=n;i++){
			for(j=i+1;j<=n;j++){
				//这边其实可以写的更优美一点，但我并不想改了 
				if(solve(n, x, p[i], p[j])){
					printf("Through all the pipe.\n");
					sig = 0;
					break;
				}
				else
					ans = max(ans, x);
				if(solve(n, x, p[i], node(p[j].x, p[j].y-1))){
					printf("Through all the pipe.\n");
					sig = 0;
					break;
				}
				else
					ans = max(ans, x);
				if(solve(n, x, node(p[i].x, p[i].y-1), p[j])){
					printf("Through all the pipe.\n");
					sig = 0;
					break;
				}
				else
					ans = max(ans, x);
				if(solve(n, x, node(p[i].x, p[i].y-1), node(p[j].x, p[j].y-1))){
					printf("Through all the pipe.\n");
					sig = 0;
					break;
				}
				else
					ans = max(ans, x);
			}
			if(!sig)break;
		}
		if(sig)
		printf("%.2f\n", ans);
	}
	return 0;
}

//判断直线ab与线段cd是否有交点 
bool iscom(node a, node b, node c, node d)
{
	//如果c、d都在直线的同一边则无交点 
	double tmp = Cross(a, b, c)*Cross(a, b, d);
	return tmp < 0.0 || fabs(tmp)<1e-6;
}
//求直线ab与线段cd交点坐标 
double getPoint(node a, node b, node c, node d){
	double a1 = a.x, b1 = a.y;
	double a2 = b.x, b2 = b.y;
	double a3 = c.x, b3 = c.y;
	double a4 = d.x, b4 = d.y;
	double t=((a2-a1)*(b3-b1)-(a3-a1)*(b2-b1))/((a2-a1)*(b3-b4)-(a3-a4)*(b2-b1));
	//交点左标x:a3+t*(a4-a3),y:b3+t*(b4-b3) 
	return a3 + t*(a4-a3);
}
//求向量ab和向量ac的叉积，即ab X ac 
double Cross(node a, node b, node c)
{
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x); 
}

bool solve(int n, double &x, node a, node b)
{
	for(int i=1;i<=n;i++){
		//如果光线能过与线段p[i]和他下方1距离的点
		//则说明能穿过这一段 
		if(!iscom(a, b, p[i], node(p[i].x, p[i].y-1))){
			if(iscom(a, b, p[i-1], p[i]))
				x = max(x, getPoint(a, b, p[i-1], p[i]));
			if(iscom(a, b, node(p[i-1].x, p[i-1].y-1), node(p[i].x, p[i].y-1)))
				x = max(x, getPoint(a, b, node(p[i-1].x, p[i-1].y-1), node(p[i].x, p[i].y-1)));
			return false;
		}
	}
	return true;
}
