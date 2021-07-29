//��ϯ��
//��ϯ�����Ƕ���߶���������������[l,r]�ڵ�k���ֵ����С��x����������
//���ձ�����������ȱ�����n���߶�������i�ñ�ʾǰi��Ԫ�طŽ����е�״̬ 
//Ȼ����[l,r]����ĵ�kСֵ������ǰ׺�͵�˼�룬��r��״̬��ȥl-1��״̬
//ʣ�µľ���[l,r]��״̬��
//Ȼ����������������϶��ᳬʱ���ڴ棬�۲�n���߶������ᷢ�ֵ�i���߶�
//�����i-1���߶���������ֻ�в�����Ǹ�Ԫ��a[i],�����ʵ�������ͬ
//������ϯ��������ǰһ���߶�����ȣ�ֻ����·���a[i]��������һ����
//����ʵ���ϳ���ԭ���ĵ�һ���߶�����������Ŀռ�ֻ��log2(n)*n��
//���������*Ԫ�صĸ�����
//����Ĳ��͹�����ϯ����ͼ����ͦ�õģ��ܷ������ 
//�������ӣ�https://www.cnblogs.com/zyf0163/p/4749042.html
//��Ŀ���ӣ�http://poj.org/problem?id=2104
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<set>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
struct node
{
	int l, r, sum;
}p[maxn*20];
int num, root[maxn], a[maxn], b[maxn];
int update(int la, int l, int r, int x);
int creat(int l, int r);
int query(int ql, int qr, int l, int r, int x);

int main()
{
	int n, i, j, m;
	num = 0;
	scanf("%d %d", &n, &m);
	root[0] = creat(1, n);
	for(i=1;i<=n;i++)
	{
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	sort(b+1, b+n+1);
	for(i=1;i<=n;i++)
	{
		int x = lower_bound(b+1,b+n+1, a[i])-b;
		root[i] = update(root[i-1], 1, n, x);
	}
	while(m--)
	{
		int l, r, x;
		scanf("%d %d %d", &l, &r, &x);
		printf("%d\n", b[query(root[l-1], root[r], 1, n, x)]);
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
int query(int ql, int qr, int l, int r, int x)
{
	if(l == r)return l;
	int mid = (l+r)>>1, sum = p[p[qr].l].sum-p[p[ql].l].sum;
	if(x<=sum)
		return query(p[ql].l, p[qr].l, l, mid, x);
	else
		return query(p[ql].r, p[qr].r, mid+1, r, x-sum);
}
