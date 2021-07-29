/************************************************
计算几何
在二维平面上，有两根木条，求当下雨时，能接到水的面积。

思路：首先判断线段是否相交，如果不相交，则为0。相交的话，
求出交点，然后求出积水的水平面的距离，利用斜率公式，可以计算
，然后求和就好了。另外需要特殊考虑几种情况，有木条平放的时候；
有木条竖放的时候，以及一根木条的上端完全盖过另一条木条上端的情况，
因为保留两位小数，精度卡的不是特别严，直接计算即可。

题目链接：http://poj.org/problem?id=2826
***************************************************/
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
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 200100;
const int mod = 1e9+7;
struct point{
	double x, y;
	point( ){}
	point( double a, double b):x(a),y(b){}
	point operator +(point b)const{
		return point(x+b.x, y+b.y);
	}
	point operator -(point b)const{
		return point(x-b.x, y-b.y);
	}
	//点积 
	double operator *(point b)const{
		return x*b.x + y*b.y;
	}
	//叉积 
	double operator ^(point b)const{
		return x*b.y-y*b.x;
	}
}p1, p2, p3, p4;
void read(point &p);
int sgn(double x);
int intersect(double l1,double r1,double l2,double r2);
bool IsCom(point a, point b, point c, point d);
double dist(point a, point b);

int main()
{
	int t, i, j, k;
	scanf("%d", &t);
	while(t--)
	{
		read(p1), read(p2);
		read(p3), read(p4);
		//如果不相交或有至少一根木条平放则一定没积水
		if(!IsCom(p1, p2, p3, p4) || sgn(p3.y-p4.y) == 0 || sgn(p1.y-p2.y)==0){
			printf("0.00\n");
			continue;
		}
		//有一根木条竖放，另一根目标不竖放
		if(sgn(p1.x-p2.x) == 0 && sgn(p3.x-p4.x)!=0){
			double k = (p3.y-p4.y)/(p3.x-p4.x);
			double b = p3.y - k * p3.x;
			double cx = p1.x;
			double cy = k*cx+b;
			double my = min(max(p1.y, p2.y), max(p3.y, p4.y));
			double mx = fabs(p1.x - (my-b)/k);
			printf("%.2f\n", mx*(my-cy)*0.5+eps);
		}
		else if(sgn(p1.x-p2.x) != 0 && sgn(p3.x-p4.x)==0){
			double k = (p1.y-p2.y)/(p1.x-p2.x);
			double b = p1.y - k * p1.x;
			double cx = p3.x;
			double cy = k*cx+b;
			double my = min(max(p1.y, p2.y), max(p3.y, p4.y));
			double mx = fabs(p3.x - (my-b)/k);
			printf("%.2f\n", mx*(my-cy)*0.5+eps);
		}
		else if(sgn(p3.x-p4.x)!=0 && sgn(p1.x-p2.x)!=0)
		{
			double k1 = (p1.y-p2.y)/(p1.x-p2.x), k2 = (p3.y-p4.y)/(p3.x-p4.x);
			double b1 = p1.y - p1.x*k1, b2 = p3.y - p3.x*k2;
			//考虑上方的木条完全盖过另一根木条
			if(k1>0 && k2>0 && k1 > k2 && max(p1.x,p2.x) >= max(p3.x,p4.x))
				printf("0.00\n");
			else if(k1>0 && k2>0 && k1 < k2 && max(p1.x,p2.x) <= max(p3.x,p4.x))
				printf("0.00\n");
			else if(k1<0 && k2<0 && k1 > k2 && min(p1.x,p2.x) >= min(p3.x,p4.x))
				printf("0.00\n");
			else if(k1<0 && k2<0 && k1 < k2 && min(p1.x,p2.x) <= min(p3.x,p4.x))
				printf("0.00\n");
			else if(sgn(k1-k2) == 0)
				printf("0.00\n");
			else{
				double cx = (b1-b2)/(k2-k1);
				double cy = cx*k1 + b1;
				double my = min(max(p1.y, p2.y), max(p3.y, p4.y));
				double mx = fabs((my-b1)/k1 - (my-b2)/k2);
				printf("%.2f\n", mx*(my-cy)*0.5+eps);
			}
		}
		else
			printf("0.00\n");
	}
	return 0;
}

void read(point &p)
{
	scanf("%lf %lf", &p.x, &p.y);
}

int sgn(double x)
{
	if(x > eps)return 1;
	else if(x < -eps)return -1;
	else return 0;
}

double dist(point a, point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}


int intersect(double l1,double r1,double l2,double r2)
{//快速排斥实验
    if (l1>r1) swap(l1,r1); 
	if (l2>r2) swap(l2,r2); 
	return sgn(r1-l2)!=-1&&sgn(r2-l1)!=-1;
}

bool IsCom(point a, point b, point c, point d)
{
	if(!(intersect(a.x, b.x, c.x, d.x) && intersect(a.y, b.y, c.y, d.y)))return false;
	double d1 = (b-c)^(d-c), d2 = (a-c)^(d-c);
	double d3 = (c-a)^(b-a), d4 = (d-a)^(b-a);
	if(sgn(d1*d2)<= 0 && sgn(d3*d4)<=0)
		return true;
	else return false; 
 }