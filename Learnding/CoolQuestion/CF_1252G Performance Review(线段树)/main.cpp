/********************************************* 
�߶���
ԭ����һ����(��һ����ΪRandall)����m�θ�����ÿ�θ����Ὣ����������͵�k
������̭��ͬʱ����µ�k�����Ž�ȥ����q�θ��ģ�ÿ�θ���
�Ὣ���е�һ��������Ϊ��һ�������ʸ��ĺ󣬾���m���滻��
Randall�Ƿ��������С�(�����໥����)
��⣺��Ϊѯ�ʵ���Randall��״̬����ÿ����ֻ̭����̭��͵�k������
���Կ���ֻ����Randall��ÿ�����������(ÿ���滻��Ϊһ������)��
ά��һ������a,a[i]��ʾRandall�ڵ�i���滻���ж��ٸ�����С��
(��Ȼû��Ҫ���ı�Randall���)��������е�a[i]�����ڵ���0����˵��
Randall���ᱻ��̭(����С�Ķ�û��̭��)��
����q�θ��ģ���Ϊֻ����Randall������������ֻ��Ҫ�����������������
(��nbΪԭ��������ngΪ���ĺ������randallΪRandall����) 
1. nb<randall && ng>randall, һ��ԭ����RandallС������ı�Randall��
		��֮��Randall���������½�1�����˴κ����a[i]ȫ����1��
2. nb>randall && ng<randall, һ��ԭ����Randall�������ñ�Randall��
		��֮��Randall������������1�����˴κ����a[i]ȫ����1��
�����е����룬���ʼ��a[i]��Ȼ�����߶���ά�����ļ��ɡ� 
PS��1252��K�����߶���ά���������ڵ�����������������
��һ���⣬���Ͳ�д�ˣ�ֻ��Ҫ������������ͺ��� 
��Ŀ���ӣ�https://codeforces.com/problemset/problem/1252/G
***********************************************/ 
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
const int maxn = 100100;
const int mod = 1000000007;
int a[maxn], p[maxn*4], lz[maxn*4];
vector<int> g[maxn];
void pushup(int k);
void pushdown(int k);
void creat(int l, int r, int k);
void Update(int l, int r, int al, int ar, int x, int k);

int main()
{
	//ra:Randall��ֵ��num��raС���������� 
	int ra, n, m, q, i, j, k, num = 0;
	scanf("%d %d %d", &n, &m, &q);
	scanf("%d", &ra);
	for(i=2;i<=n;i++)
	{
		scanf("%d", &j);
		if(j<ra)num++;
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d", &j);
		//��̭j���� 
		a[i] = num-j;
		num -= j;
		//�±��1��ʼ��0λ���0 
		g[i].push_back(0);
		while(j--)
		{
			scanf("%d", &k);
			g[i].push_back(k);
			if(k<ra)num++;
		}
	}
	creat(1, m, 1);
	while(q--)
	{
		int z, x, y;
		scanf("%d %d %d", &x, &y, &z);
		//���һ����ra�������Ϊ��raС�����������ȫ����1 
		if(g[x][y] > ra && z<ra)
			Update(1, m, x+1, m, 1, 1);
		//���һ����raС������Ϊ���ô�����������ȫ����1 
		else if(g[x][y] < ra && z>ra)
			Update(1, m, x+1, m, -1, 1);
		g[x][y] = z;
		if(p[1] < 0)printf("0\n");
		else printf("1\n");
	}
	return 0;
}

void creat(int l, int r, int k)
{
	lz[k] = 0;
	if(l == r)
	{
		p[k] = a[l];
		return;		
	}
	int mid=(l+r)/2;
	creat(l, mid, 2*k);
	creat(mid+1, r, 2*k+1);
	pushup(k);
}

void pushup(int k)
{
	p[k] = min(p[2*k], p[2*k+1]);
}

void pushdown(int k)
{
	if(lz[k])
	{
		lz[2*k] += lz[k], lz[2*k+1] += lz[k];
		p[2*k] += lz[k], p[2*k+1] += lz[k];
		lz[k] = 0;
	}
}

void Update(int l, int r, int al, int ar, int x, int k)
{
	if(al > ar)return;
	if(l == al && r == ar)
	{
		p[k] += x;
		lz[k] += x;
		return;
	}
	pushdown(k);
	int mid = (l+r)/2;
	if(ar <= mid)
		Update(l, mid, al, ar, x, 2*k);
	else if(al > mid)
		Update(mid+1, ar, al, ar, x, 2*k+1);
	else
		Update(l, mid, al, mid, x, 2*k),
		Update(mid+1, r, mid+1, r, x, 2*k+1);
	pushup(k);
}
