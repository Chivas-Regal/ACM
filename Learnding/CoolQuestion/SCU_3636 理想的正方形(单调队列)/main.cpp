/****************************************** 
��������
��һ��r*w�ľ�����Ҫѡ��һ��n*n�������Σ�ʹѡ�е�������
���ֵ����Сֵ�Ĳ���С
˼·����Ŀ�ؼ��������n��������������С�ģ�����ԭ����
�������a[i][j]Ϊ��ʼλ�õ�����n��������������Ϊb[i][j]
(���i��ʵȡ����n��������)����b[i][j]����Ϊ��i,jΪ��ѡ
�������Ͻǵľ�������ֵ��Ȼ����b[i][j]����b[i][j]����
n�����е����ֵ��
���������˷ֿ��˼��ɣ�����ÿ��r*w���п���ȡn�������е�
�����һ��1*n����������ֵ��Ȼ���ٶ�1*n���������ͬ������
���Եõ�n*n�������ڵ����ֵ����Сֵ���ơ�
 
�������У�
�������п�����1~w�����У�����iΪ��㣬����n�����е����(С)ֵ
�����������ֵΪ���� 
����ʵ��������˫�˶��У�����ά��һ���ݼ������г�ʼ����Ϊ�գ�
�����е�ÿ��Ԫ��ά������ֵ��һ������ֵ��һ����λ�� 
����һ����a[i]����Ϊ��n�������ƣ�������Ҫ�Ӷ��׿�ʼ����������
ȡ����i��Ԫ��ȫ��������
Ȼ��Ѷ����б�a[i]С����ȫ��������Ȼ��a[i]���� 
����β����Ȼ����i��ͷ������n���������ֵ��Ϊ��ǰ��������Ԫ�ص�
��ֵ

������һ��ʵ��������⣺
��������5 3 4 6 1������iΪ��ʼ��ģ�����3���������ֵ
({(id,val)}������У�(id,val)��������е�һ��Ԫ��,idΪλ�ã�valΪֵ)
i=1:����5��     				{(1,5)}
i=2:3���ڶ�βԪ�ط���3 			{(1,5),(2,3)}
i=3:4���ڶ�βԪ�أ���(2,3)���� 	{(1,5),(3,4)}
i=4:1��ʼ����ȡ��4������(1,5)��6���ڶ�βԪ�أ�����(3,4)������Ϊ��
	����6 						{(4,6)} 
i=5:1С�ڶ�βԪ��ֵ���������   {(4,6),(5,1)}

��Ŀ���ӣ� https://vjudge.net/problem/SCU-3636
*******************************************/ 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<deque>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1520;
const int mod = 1;
struct node{
	int id, mx;
	node(){}
	node(int a, int b){
		id = a, mx = b;
	}
}; 
//b[i][j]��i��jΪn*n�������Ͻǣ����������ֵ
//c[i][j]��i��jΪn*n�������Ͻǣ���������Сֵ
int a[maxn][maxn], b[maxn][maxn], c[maxn][maxn];
void sovlemx(int r, int w, int n);
void sovlemi(int r, int w, int n);

int main()
{
	int r, w, n, i, j, ans;
	while(~scanf("%d %d %d", &r, &w, &n))
	{
		for(i=0;i<r;i++)
			for(j=0;j<w;j++)
				scanf("%d", &a[i][j]);
		sovlemx(r, w, n);
		sovlemi(r, w, n); 
		ans = b[0][0] - c[0][0];
		for(i=0;i+n-1<r;i++)
		{
			for(j=0;j+n-1<w;j++)
				ans = min(ans, b[i][j]-c[i][j]);
		}
		printf("%d\n", ans);
	}
	return 0;
}

void sovlemx(int r, int w, int n)
{
	int i, j;
	deque<node> que;
	for(i=0;i<r;i++)
	{
		//��ն��� 
		while(!que.empty())que.pop_back();
		//�Ƚ�ǰn����������� 
		que.push_back(node(0, a[i][0]));
		for(j=1;j<n;j++)
		{
			//����βС��a[i][j]�ĵ������� 
			while(!que.empty() && que.back().mx < a[i][j])
				que.pop_back();
			que.push_back(node(j, a[i][j]));
		}
		b[i][0] = que.front().mx;
		for(;j<w;j++)
		{
			//������ȡ��jλ�õ�Ԫ�ص��� 
			while(!que.empty() && que.front().id+n-1 < j)que.pop_front();
			while(!que.empty() && que.back().mx < a[i][j])
				que.pop_back();
			que.push_back(node(j, a[i][j]));
			b[i][j-n+1] = que.front().mx;
		}
	}
	for(j=0;j+n-1<w;j++)
	{
		while(!que.empty())que.pop_back();
		que.push_back(node(0, b[0][j]));
		for(i=1;i<n;i++)
		{
			while(!que.empty() && que.back().mx < b[i][j])
				que.pop_back();
			que.push_back(node(i, b[i][j]));
		}
		b[0][j] = que.front().mx;
		for(;i<r;i++)
		{
			while(!que.empty() && que.front().id+n-1 < i)que.pop_front();
			while(!que.empty() && que.back().mx < b[i][j])
				que.pop_back();
			que.push_back(node(i, b[i][j]));
			b[i-n+1][j] = que.front().mx;
		}
	}
}

void sovlemi(int r, int w, int n)
{
	int i, j;
	deque<node> que;
	for(i=0;i<r;i++)
	{
		while(!que.empty())que.pop_back();
		que.push_back(node(0, a[i][0]));
		for(j=1;j<n;j++)
		{
			while(!que.empty() && que.back().mx > a[i][j])
				que.pop_back();
			que.push_back(node(j, a[i][j]));
		}
		c[i][0] = que.front().mx;
		for(;j<w;j++)
		{
			while(!que.empty() && que.front().id+n-1 < j)que.pop_front();
			while(!que.empty() && que.back().mx > a[i][j])
				que.pop_back();
			que.push_back(node(j, a[i][j]));
			c[i][j-n+1] = que.front().mx;
		}
	}
	for(j=0;j+n-1<w;j++)
	{
		while(!que.empty())que.pop_back();
		que.push_back(node(0, c[0][j]));
		for(i=1;i<n;i++)
		{
			while(!que.empty() && que.back().mx > c[i][j])
				que.pop_back();
			que.push_back(node(i, c[i][j]));
		}
		c[0][j] = que.front().mx;
		for(;i<r;i++)
		{
			while(!que.empty() && que.front().id+n-1 < i)que.pop_front();
			while(!que.empty() && que.back().mx > c[i][j])
				que.pop_back();
			que.push_back(node(i, c[i][j]));
			c[i-n+1][j] = que.front().mx;
		}
	}
}

