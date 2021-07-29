//极角排序
//首先确定最下方的点，然后找未走过的与下方的点的极角最小的
//可以使用叉积来完成极角排序，但叉积只能保证在PI的范围内
//排出正确的结果，如果角度在PI以上就不能得到正确的结果，
//此题对于每个点来说，未使用过的点肯定都在点的某一边
//所以每次对未使用过的点进行极角排序，然后取最小即可
//题目链接：http://poj.org/problem?id=1696 
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
#define eps 1e-6

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 150;
const double PI = acos(-1.0);
struct point{
	int x, y, id;
	point(){}
	point(int a, int b){
		x = a, y = b;
	}
	point operator -(point b){
		return point(x-b.x, y-b.y);
	}
	int operator ^(point b){
		return x*b.y-y*b.x;
	}
	int dis(point b){
		return (x-b.x)*(x-b.x)+(y-b.y)*(y-b.y);
	}
}p[maxn], c;
int ans[maxn], vis[maxn];
bool cmp(point a, point b);

int main()
{
	int t, n, m, i, j;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		memset(vis, 0, sizeof(vis));
		for(i=1;i<=n;i++)
			scanf("%d %d %d", &p[i].id, &p[i].x, &p[i].y);
		int ml = 1;
		//确定最下方的点为起始点 
		for(i=2;i<=n;i++)
			if(p[i].y < p[ml].y)
				ml = i;
		swap(p[1], p[ml]); 
		for(i=1;i<n;i++)
		{
			//选点作为极点 
			c = p[i];
			sort(p+i+1, p+n+1, cmp);
		}
		printf("%d", n);
		for(i=1;i<=n;i++)
			printf(" %d", p[i].id);
		printf("\n");
	}
	return 0;
}
//利用叉积进行极角排序
bool cmp(point a, point b)
{
	if(((a-c)^(b-c)) == 0){
		return c.dis(a)<c.dis(b);
	}
	else
		return ((a-c)^(b-c))>0;
}
