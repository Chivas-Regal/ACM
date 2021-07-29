//计算几何+三分
//已知三维有n个点求最小包含所有点的圆锥的体积，求其高和地面半径
//因为圆锥的顶点一定x、y的坐标一定为0,所以可以三分z的坐标
//对于每个确定的z坐标，可以确定最小的半径r，然后已知三分
//求最小值即可 
//题目链接：http://poj.org/problem?id=3962
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
const int maxn = 10100;
struct node{
	double x, y, z, r;
}p[maxn];
int a[maxn];
double isok(double z, double n, double &rr);
bool cmp(node a, node b);

int main()
{
	int n, i, j;
	double lz = 0, rz, ans, rr;
	scanf("%d", &n);
	for(i=0;i<n;i++){
		scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].z);
		p[i].r = sqrt(p[i].x*p[i].x+p[i].y*p[i].y);
		lz = max(lz, p[i].z);
	}
	//以下内容是想尝试优化一下，降低复杂度，然而没啥用
	//说不定可以模拟退火跑到快一点 
	sort(p, p+n, cmp);
	rr = p[n-1].r;
	for(i=n-2;i>=0;i--){
		if(p[i].r < rr)
			a[i] = 1;
		else
			rr = p[i].r;
	}
	int num = 0;
	for(i=0;i<n;i++)
	if(!a[i])p[num++] = p[i];
	n = num;
	//*******************
	
	rz = 10000;
	while(fabs(lz-rz)>1e-8)
	{
		double mid = (rz-lz)/3; 
		//求在两个三等分点时的值 
		double midl = isok(lz+mid, n, rr), midr = isok(lz+2*mid, n, rr);
		//将两个三等分点较大的值更新 
		if(midl > midr)
			lz = lz + mid;
		else
			rz = lz + 2*mid;
	}
	isok(lz, n, rr);
	printf("%.3f %.3f\n", lz, rr);
	return 0;
}

double isok(double z, double n, double &rr)
{
	double r=0;
	for(int i=0;i<n;i++)
	{
		//根据相似三角形，求底面半径
		r = max(r, p[i].r/(1-p[i].z/z));
	}
	rr = r;
	return r*r*z;
}

bool cmp(node a, node b)
{
	return a.z < b.z;
}
