//凸包
//向量叉积,已知向量为(x1,y1)(x2,y2),叉乘为x1*y2-x2*y1;
//向量a叉乘b大于0,则a在b顺时针方向，小于0则在逆时针方向
//--------------------------------------------- 
//参考博客:https://blog.csdn.net/qq_36336522/article/details/79432744
//题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=2202 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
double add(double a, double b);
struct node
{
    int x,y;
    node(){
	}
    node(double x, double y):x(x),y(y){
	}
    node operator - (node p)
    {
    	return node(add(x, -p.x), add(y, -p.y));
	}
	double det(node p)
	{
		return add(x*p.y, -y*p.x);
	}
};
node a[50010],ps[50010];
double cross(node a, node b, node c);
int tubao(int n);
bool cmp(node a, node b);
double dis(node a, node b, node c);

int main()
{
	int n, k, m, i;
	while(scanf("%d", &n)!=EOF)
	{
		for(i=0;i<n;i++)
			scanf("%d %d", &ps[i].x, &ps[i].y);
		k = tubao(n);
		//for(i=0;i<k;i++)
		//	printf("%d %d\n", a[i].x, a[i].y);
		double maxx = -1;
		for(i=0;i<k;i++)
			for(int j=0;j<k;j++)
				for(int s=0;s<k;s++)
					maxx = max(maxx, dis(a[i], a[j], a[s]));
		printf("%.2f\n", maxx);
	}
	return 0;
}

bool cmp(node a, node b)
{
	if(a.x != b.x)return a.x < b.x;
	return a.y < b.y;
}

int tubao(int n)
{
	int k=0;
	sort(ps, ps+n, cmp);
	for(int i=0;i<n;i++)
	{ 
		while(k>1 && (a[k-1]-a[k-2]).det(ps[i]-a[k-1])<=0)
			k--;
		a[k] = ps[i];
		k++;
	}
	for(int i=n-2,t=k;i>=0;i--)
	{
		while(k>t && (a[k-1]-a[k-2]).det(ps[i]-a[k-1])<=0)
			k--;
		a[k] = ps[i];
		k++;
	}
	return k-1;
}
//计算三角形面积，已知三点面积为(x1,y1),(x2,y2),(x3,y3)
//则三角形面积就是行列式
//| x1 y1 1 |
//| x2 y2 1 |*1/2的值
//| x3 y3 1 |
double dis(node a, node b, node c)
{
	return (a.x*b.y + b.x*c.y + c.x*a.y - a.x*c.y - b.x*a.y - c.x * b.y)*1.0/2;
}

double add(double a, double b)
{
	double EPS = 1e-10;
	if(fabs(a+b) < EPS*(fabs(a)+fabs(b)))return 0;
	return a+b;
}
