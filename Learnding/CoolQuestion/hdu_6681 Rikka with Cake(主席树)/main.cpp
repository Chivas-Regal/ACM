//��ϯ��
//����ŷ����ʽ�����Ƴ�����ͨ�����������k�����߽���������1
//���Խ������������Ȼ�����Ӧ�������������ϯ����
//����ÿ�����ŵ��ߣ����ֲ�������������������������ཻ��λ��
//Ȼ����ϯ����������������ֵ���������
//���о��ǲ��Һ�����ʵ�����ʱ��Ҫע����ֵı߽���� 
//PS����ϯ��д�������У�����һ�죬��ʵ��������״���飬ɨ���߸�һ��
//����һ����
//��Ŀ���ӣ�http://acm.hdu.edu.cn/showproblem.php?pid=6681 
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
const int maxn = 200100;
const int mod = 1000000007;
struct node
{
	int l, r, sum;
}p[maxn*20];
int num, root[maxn], a[maxn], b[maxn];
vector<P> g[5];
int creat(int l, int r);
bool cmp1(P a, P b);
int update(int la, int l, int r, int x);
int query(int ql, int qr, int l, int r, int al, int ar);
int Search(int l, int r, int x,int a[]);
int Find1(int l, int r, int x);
int Find2(int l, int r, int x);

int main()
{
	int t, n, i, j, r, l, m, k;
	char ch;
	LL V, E;
	scanf("%d", &t);
	while(t--)
	{
		g[0].clear(), g[1].clear(), g[2].clear(), g[3].clear();
		V = E = num = 0, l = 0, r = 0;
		scanf("%d %d %d", &m, &k, &n);
		for(i=0;i<n;i++)
		{
			int x, y;
			scanf("%d %d %c", &x, &y, &ch);
			if(ch == 'U')g[0].push_back(P(x, y));
			else if(ch == 'L')g[1].push_back(P(x, y));
			else if(ch == 'D')g[2].push_back(P(x, y));
			else if(ch == 'R')g[3].push_back(P(x, y)); 
			a[++l] = x;a[++l] = y;
		}
		int n1=g[0].size(), n2 = g[1].size(), n3 = g[2].size(), n4 = g[3].size();
		sort(a+1, a+1+l);
		for(i=0;i<4;i++){
			for(j=0;j<g[i].size();j++)
			{
				if(g[i][j].first == a[l])
					g[i][j].first = l;
				else
					g[i][j].first = Search(1, l, g[i][j].first, a);
				if(g[i][j].second == a[l])
					g[i][j].second = l;
				else
					g[i][j].second = Search(1, l, g[i][j].second, a);
			}
		}
		root[0] = creat(1, l);
		sort(g[1].begin(), g[1].end(), cmp1), sort(g[3].begin(), g[3].end(), cmp1);
		for(i=0;i<n2;i++){
			++r;
			root[r] = update(root[r-1], 1, l, g[1][i].second);
		}
		for(i=0;i<n4;i++){
			++r;
			root[r] = update(root[r-1], 1, l, g[3][i].second);
		}
		for(i=0;i<n1;i++){
			int x, num = 0;
			if(n2 != 0){
				//���������к�������ڵ��ڵ�ǰ���������С�±� 
				if(g[0][i].first < g[1][0].first)x = 0;
				else if(g[0][i].first > g[1][n2-1].first)x = n2;
				else x = Find1(0, n2-1, g[0][i].first);
				num = query(root[x], root[n2], 1, l, g[0][i].second, l);
			}
			if(n4 != 0){
				//���������к�����С�ڵ��ڵ�ǰ������±� 
				if(g[0][i].first < g[3][0].first)x = 0;
				else if(g[0][i].first > g[3][n4-1].first)x = n4;
				else x = Find2(0, n4-1, g[0][i].first)+1;
				num += query(root[n2], root[n2+x], 1, l, g[0][i].second, l);
			}
			if(num){
				V += num, E += num+1;
			}
		}
		for(i=0;i<n3;i++){
			//�������µ�����˵����������1~�������귶Χ�ڵĶ����н���� 
			int x, num = 0;
			if(n2 != 0){
				if(g[2][i].first < g[1][0].first)x = 0;
				else if(g[2][i].first > g[1][n2-1].first)x = n2;
				else x = Find1(0, n2-1, g[2][i].first);
				num = query(root[x], root[n2], 1, l, 1, g[2][i].second);
			}
			if(n4 != 0){
				if(g[2][i].first < g[3][0].first)x = 0;
				else if(g[2][i].first > g[3][n4-1].first)x = n4;
				else x = Find2(0, n4-1, g[2][i].first)+1;
				num += query(root[n2], root[n2+x], 1, l, 1, g[2][i].second);
			}
			if(num){
				V += num, E += num+1;
			}
		}
		//dbg(V);
		printf("%lld\n", V+1);
	}
	return 0;
}

//����ԭʼ���߶���(����) 
int creat(int l, int r)
{
	int ts = ++num;
	p[ts].sum = 0;
	if(l == r)return ts;
	int mid = (l+r)>>1;
	p[ts].l = creat(l, mid);
	p[ts].r = creat(mid+1, r);
	return ts;
}
//��������x������ʱ������������ص���
int update(int la, int l, int r, int x)
{
	int now = ++num;
	p[now] = p[la];
	if(l == r){
		p[now].sum++;return now;
	}
	int mid=(l+r)>>1;
	if(x<=mid)
		p[now].l = update(p[la].l, l, mid, x);
	else
		p[now].r = update(p[la].r, mid+1, r, x);
	p[now].sum++;
	return now;
}
//��ѯ����Ϊ������������ԣ��������������ͬ������[l,r]��
//�ڵ�qr״̬ʱ��ȥql״̬ʱ����������[ql+1,qr]�����״̬ 
int query(int ql, int qr, int l, int r, int al, int ar)
{
	if(l == al && r == ar)
		return p[qr].sum - p[ql].sum;
	int mid = (l+r)>>1;
	if(ar <= mid)
		return query(p[ql].l, p[qr].l, l, mid, al, ar);
	else if(al > mid)
		return query(p[ql].r, p[qr].r, mid+1, r, al, ar);
	else{
		return query(p[ql].l, p[qr].l, l, mid, al, mid)+query(p[ql].r, p[qr].r, mid+1, r, mid+1, ar);
	}
}

bool cmp1(P a, P b)
{
	return a.first < b.first;
}

int Search(int l, int r, int x,int a[])
{
	int mid = (l+r)/2;
	if(a[mid] == x && a[mid+1]>x)return mid;
	else if(a[mid] <= x)return Search(mid+1, r, x, a);
	else return Search(l, mid-1, x, a);
}

int Find1(int l, int r, int x)
{
	if(l>r)return -1;
	int mid = (l+r)/2;
	if(g[1][mid].first >= x && (mid == 0 || g[1][mid-1].first<x))
		return mid;
	else if(g[1][mid].first >= x)
		return Find1(l, mid-1, x);
	else 
		return Find1(mid+1, r, x);
}

int Find2(int l, int r, int x)
{
	if(l > r)return -1;
	int mid = (l+r)/2;
	if(g[3][mid].first <= x && (mid+1== g[3].size() ||  g[3][mid+1].first>x))
		return mid;
	else if(g[3][mid].first > x)
		return Find2(l, mid-1, x);
	else 
		return Find2(mid+1, r, x);
}

