//���㼸�Σ����
//��һ�ιܵ�����i��ת�۵�����Ϊ(xi,yi)(x1<x2<x3<..<xn)
//��i��ת�۵�����(x1,yi-1) 
//��x1�����һ�����ߣ�����Զ�ܵ�x������
//�²�����Ĺ��߱ض���2*n���������������ڵ�ֱ��
//����ö�����е�����ɵ�ֱ�ߣ�����Զ�ܵ����ֱ��
//��Ŀ���ӣ�http://poj.org/problem?id=1039 
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
				//�����ʵ����д�ĸ�����һ�㣬���Ҳ�������� 
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

//�ж�ֱ��ab���߶�cd�Ƿ��н��� 
bool iscom(node a, node b, node c, node d)
{
	//���c��d����ֱ�ߵ�ͬһ�����޽��� 
	double tmp = Cross(a, b, c)*Cross(a, b, d);
	return tmp < 0.0 || fabs(tmp)<1e-6;
}
//��ֱ��ab���߶�cd�������� 
double getPoint(node a, node b, node c, node d){
	double a1 = a.x, b1 = a.y;
	double a2 = b.x, b2 = b.y;
	double a3 = c.x, b3 = c.y;
	double a4 = d.x, b4 = d.y;
	double t=((a2-a1)*(b3-b1)-(a3-a1)*(b2-b1))/((a2-a1)*(b3-b4)-(a3-a4)*(b2-b1));
	//�������x:a3+t*(a4-a3),y:b3+t*(b4-b3) 
	return a3 + t*(a4-a3);
}
//������ab������ac�Ĳ������ab X ac 
double Cross(node a, node b, node c)
{
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x); 
}

bool solve(int n, double &x, node a, node b)
{
	for(int i=1;i<=n;i++){
		//��������ܹ����߶�p[i]�����·�1����ĵ�
		//��˵���ܴ�����һ�� 
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
