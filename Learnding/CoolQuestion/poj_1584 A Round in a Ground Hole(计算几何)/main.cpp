//���㼸��
//�����жϸ�����Щ���Ƿ���һ��͹��
//��������ж�Բ���Ƿ���͹����
//Ȼ�����ж�Բ�ĵ�ÿ���ߵľ����Ƿ񶼴��ڵ��ڰ뾶
//��Ŀ���ӣ�http://poj.org/problem?id=1584
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
  
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn =800100;
struct point{
	double x, y;
	point(){}
	point(double a, double b):x(a),y(b){
	}
	point operator -(const point &b)const{
		return point(x-b.x, y-b.y);
	}
	//���� 
	double operator *(const point &b)const{
		return x*b.x + y*b.y;
	}
	//���� 
	double operator ^(const point &b)const{
		return x*b.y - y*b.x;
	}
}p[maxn];
bool IsTu(point poly[], int n);
int sgn(double x);
double Cross(point a, point b, point c);
double dist(point a, point b);
point PointToLine(point p, point a, point b);
int inPoly(point p, point poly[], int n);
bool IsCom(point a, point b, point c, point d);
int intersect(double l1,double r1,double l2,double r2);

int main()
{
	int n, i, j;
	double rx, ry, r;
	while(scanf("%d", &n), n>2){
		scanf("%lf %lf %lf", &r, &rx, &ry);
		for(i=0;i<n;i++)
			scanf("%lf %lf", &p[i].x, &p[i].y);
		if(!IsTu(p, n)){
			printf("HOLE IS ILL-FORMED\n");
			continue;
		}
		i = 0;
		if(inPoly(point(rx, ry), p, n)>0)
		for(i=0;i<n;i++){
			double dis = dist(point(rx, ry), PointToLine(point(rx,ry), p[i], p[(i+1)%n]));
			if(sgn(dis-r) < 0)break;
		}
		if(i == n)
			printf("PEG WILL FIT\n");
		else
			printf("PEG WILL NOT FIT\n");
	}
	return 0;
}
//�ж��Ƿ���͹�� 
//���б�һֱ��ĳһ������ת�䣬����͹�� 
bool IsTu(point poly[], int n)
{
	int af = 0;
	for(int i=0;i<n;i++){
			int tmp = sgn(Cross(poly[i], poly[(i+1)%n], poly[(i+2)%n]));
			if(!af)af = tmp;
			if(af*tmp < 0){
				return false;
			}
		}
	return true;
}
//������ab������bc�����ϵ 
double Cross(point a, point b, point c)
{
	return (b-a)^(c-b);
}
//���p���߶�ab����ĵ������ 
point PointToLine(point p, point a, point b)
{
	point result;
	double t = ((p-a)*(b-a))/((b-a)*(b-a));
	if(t>=0 && t<=1)
	{
		result.x = a.x+(b.x-a.x)*t;
		result.y = a.y+(b.y-a.y)*t;
	}
	else
	{
		if(dist(p, a)<dist(p, b))
			result = a;
		else
			result = b;
	}
	return result;
}

int sgn(double x)
{
	if(x < -eps)return -1;
	else if(x > eps)return 1;
	else 0;
}

double dist(point a, point b)
{
	return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}
//�ж�p�Ƿ����߶�ab�� 
bool OnSeg(point p, point a, point b)
{
	return sgn((a-p)^(b-p))==0 && 
	sgn((p.x-a.x)*(p.x-b.x))<=0 &&
	sgn((p.y-a.y)*(p.y-b.y))<=0;
}
//�жϵ�P�Ƿ������������� 
int inPoly(point p, point poly[], int n)
{
	int cnt = 0;
	point ray1, ray2, side1, side2;
	ray1 = p, ray2.y = p.y, ray2.x = -1000000000.0;
	for(int i=0;i<n;i++)
	{
		if(sgn((poly[i]-poly[(i+1)%n])^(poly[i]-poly[(i+2)%n])) == 0)continue;
		side1 = poly[i], side2 = poly[(i+1)%n];
		if(OnSeg(p, side1, side2))return 0;
		if(sgn(side1.y - side2.y) == 0)
			continue;
		if(OnSeg(side1, ray1, ray2))
		{
			if(sgn(side1.y-side2.y)>0)cnt++;
		}
		else if(OnSeg(side2, ray1, ray2))
		{
			if(sgn(side2.y-side1.y)>0)cnt++;
		}
		else if(IsCom(ray1, ray2, side1, side2))
			cnt++;
	}
	if(cnt%2 == 1)return 1;
	return -1;
}
//�����ų�ʵ�� 
int intersect(double l1,double r1,double l2,double r2){//�����ų�ʵ��
    if (l1>r1) swap(l1,r1); 
	if (l2>r2) swap(l2,r2); 
	return sgn(r1-l2)!=-1&&sgn(r2-l1)!=-1;
}
//�ж�ab��cd�Ƿ��ཻ 
bool IsCom(point a, point b, point c, point d)
{
	if(!(intersect(a.x, b.x, c.x, d.x) && intersect(a.y, b.y, c.y, d.y)))return false;
	double d1 = (b-c)^(d-c), d2 = (a-c)^(d-c);
	double d3 = (c-a)^(b-a), d4 = (d-a)^(b-a);
	if(sgn(d1*d2)<= 0 && sgn(d3*d4)<=0)
		return true;
	else return false; 
 }

