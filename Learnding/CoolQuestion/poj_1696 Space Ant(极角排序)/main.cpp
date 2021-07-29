//��������
//����ȷ�����·��ĵ㣬Ȼ����δ�߹������·��ĵ�ļ�����С��
//����ʹ�ò������ɼ������򣬵����ֻ�ܱ�֤��PI�ķ�Χ��
//�ų���ȷ�Ľ��������Ƕ���PI���ϾͲ��ܵõ���ȷ�Ľ����
//�������ÿ������˵��δʹ�ù��ĵ�϶����ڵ��ĳһ��
//����ÿ�ζ�δʹ�ù��ĵ���м�������Ȼ��ȡ��С����
//��Ŀ���ӣ�http://poj.org/problem?id=1696 
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
		//ȷ�����·��ĵ�Ϊ��ʼ�� 
		for(i=2;i<=n;i++)
			if(p[i].y < p[ml].y)
				ml = i;
		swap(p[1], p[ml]); 
		for(i=1;i<n;i++)
		{
			//ѡ����Ϊ���� 
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
//���ò�����м�������
bool cmp(point a, point b)
{
	if(((a-c)^(b-c)) == 0){
		return c.dis(a)<c.dis(b);
	}
	else
		return ((a-c)^(b-c))>0;
}
