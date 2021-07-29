//���㼸��
//һ��͹����Σ�����һ��Q�������ι���һ�ܣ��õ���˶��켣�ĳ���
//���ڶ���ε�ÿһ������P�������е�һ���߹�������һ����
//��켣������|PQ|Ϊ�뾶�ģ�PΪԭ���Բ��һ�λ����Ƕ�Ϊ
//PI��ȥPQ��õ����ڵ������ߵĽǶȣ�ʵ���Ͼ���PI��ȥ
//PΪ������Ǹ��ǣ���Ϊ����һ�߼�ȥ����PQ��ߵĽǶȣ�һ�߼�ȥ
//����PQ�ұߵĽǶ�
//��Ŀ���ӣ�https://www.jisuanke.com/contest/2991/261479
//2018����CCPC������B 
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
#define dbg(x) cout<<#x<<":"<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<LL, int> P;
const int maxn = 100100;
const LL mod = 998244353;
const double pi = acos(-1);
struct point{
	double x, y;
	point(){}
	point(double a, double b):x(a),y(b){
	}
	point operator -(point b)const{
		return point(x-b.x, y-b.y);
	}
	double operator *(point b)const{
		return x*b.x+y*b.y;
	}
	double operator ^(point b)const{
		return x*b.y - y*b.x;
	} 
	double dis(point b){
		return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
	}
	double dis(){
		return sqrt(x*x+y*y);
	}
}p[maxn];
double getAng(point a, point b, point c);

int main()
{
	int t, n, i, j;
	point q;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		double ans = 0;
		scanf("%d", &n);
		for(i=0;i<n;i++)
			scanf("%lf %lf", &p[i].x, &p[i].y);
		p[n] = p[0], p[n+1] = p[1];
		scanf("%lf %lf", &q.x, &q.y);
		for(i=1;i<=n;i++)
		{
			double r = q.dis(p[i]);
			if(r<eps)continue;
			//printf("%.4f\n", r);
			double ang1 = getAng(p[i], p[i-1], p[i+1]);
			//printf("ang:%.4f %.4f\n", ang1, ang2);
			ans += r*(pi-ang1);
			//printf("ans:%.4f\n\n", ans);
		}
		printf("Case #%d: %.3f\n", z, ans);
	}
	return 0;
}
//������ab������ac�н� 
double getAng(point a, point b, point c)
{
	point p1 = c-a, p2 = b-a;
	return acos(p1*p2/(p1.dis()*p2.dis()));
}
