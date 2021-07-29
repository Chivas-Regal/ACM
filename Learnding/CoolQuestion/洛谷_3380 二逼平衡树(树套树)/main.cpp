//������(��״������Ȩֵ�߶���)
//�����������ģ���⣬
//������⣺��������ʵ������״������߶���(��˵���߶�������ʵ���Ǽ�����)
//��Ϊ���ֱ��ÿ����״�����ڲ��ٽ��߶�����ֱ����n*n�Ŀռ���
//�ڲ�ʵ���ϴ洢�����ޣ�����1λ�õ���״����ʵ���Ͼ�ֻ��1��Ԫ��
//������n���߶�����ܶ���ʵ�����ǿյ�
//����������״���飬ʵ���ϴ洢���Ǽ������������յĲ��ֶ����ظ������� 
//Ȼ���ڲ����ÿ��Ԫ��ʵ����ֻ�洢��һ����������
//���Գ�ʼ���Ŀռ临�Ӷ���n*log n *log n
//���£��������Ԫ�أ��ͺ���ϯ����࣬��ԭ��������ȥֵ��Ȼ���ٸ����µ�������
//		��������
//��ѯ����ѯ��Ҫ��Ϊ���֣�һ���ǲ�ѯ�����kС��������Ҫ���������Ҫʹ�õ������
//		��״���飬Ȼ�����[ql,qr]���ڲ��߶���������ж��ٸ�Ԫ�أ�Ȼ��������ı�
//		����
//		��һ�ֲ�ѯ����С��k���ж��ٸ������Ҳ�ܼ򵥣���ֱ�ӱ���������Ҫ�õ������
//		��״���飬Ȼ��ͳ�Ƹ�����״������������������Ԫ�صĸ�����Ȼ���һ��������
//��Ŀ���ӣ�https://www.luogu.org/problem/P3380 
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
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<LL, int> P;
const int maxn = 50100;
//tot:��ǰʹ�ý���ţ�tl������������ţ�tr������������ţ�p���洢����ֵ 
int tot, tl[100*maxn], tr[100*maxn], p[100*maxn]; 
//n�������С��le����ɢ��������п���ȡֵ��������dic����ɢ���� 
int n, le, dic[2*maxn], a[maxn], op[maxn], ql[maxn], qr[maxn], qk[maxn];
//lsz��rsz����l��rΪǰ׺�͵���״������Ҫ���ʵ�Ԫ��������vl��vr���洢��Ҫ���ʵ�Ԫ�� 
int lsz, rsz, vl[maxn], vr[maxn];
void init();
int lowbit(int x);
void built(int n);
int lisan(int dic[], int n);
void Add(int k, int pos, int x);
void Update(int x, int pk);
void Insert(int l, int r, int k, int pos, int x);
int queryRank(int ql, int qr, int qk, int x);
int querymin(int l, int r, int k, int x);
int queryVal(int l, int r, int x); 
int queryK(int l, int r, int x);
int KsBefore(int ql, int qr, int qk);
int KsAfter(int ql, int qr, int qk);

int main()
{
	int m, i, j, k, ans;
	init();
	scanf("%d %d", &n, &m);
	for(i=1;i<=n;i++){
		scanf("%d", &a[i]);
		dic[++le] = a[i];
	}
	for(i=1;i<=m;i++){
		scanf("%d %d %d", &op[i], &ql[i], &qr[i]);
		if(op[i]!=3)
			scanf("%d", &qk[i]);
		if(op[i] == 3)dic[++le] = qr[i];
		else if(op[i] != 2)dic[++le] = qk[i];
	}
	le = lisan(dic, le);
	built(n); 
	for(i=1;i<=m;i++)
		switch(op[i]){
			case 1:ans = queryRank(ql[i], qr[i], qk[i], 1)+1;
					printf("%d\n", ans);break;
			case 2:ans = queryVal(ql[i], qr[i], qk[i]);
					printf("%d\n", ans);break;
			case 3:Update(ql[i], qr[i]);break;
			case 4:ans = KsBefore(ql[i], qr[i], qk[i]);
					if(ans == -1)
						printf("-2147483647\n");
					else
						printf("%d\n", ans);
					break;
			case 5:ans = KsAfter(ql[i], qr[i], qk[i]);
					if(ans == -1)
						printf("2147483647\n");
					else
						printf("%d\n", ans);
					break;
		}
	return 0;
}
//��ɢ��ȥ�ز����س���
int lisan(int dic[], int n)
{
	int l=0;
	sort(dic+1, dic+1+n);
	dic[0] = dic[1]-100;
	for(int i=1;i<=n;i++){
		if(dic[i] != dic[l])
		dic[++l] = dic[i];
	}
	return l;
}
//��ʼ������
void init()
{
	le = 0;
	memset(tl, 0, sizeof(tl));
	memset(tr, 0, sizeof(tr));
	memset(p, 0, sizeof(p));
}
//�����ʼ����(��)
void built(int n)
{
	tot = 1;
	while(tot<n)
		tot<<=1;
	for(int i=1;i<=n;i++)
	{
		int pos = lower_bound(dic+1, dic+1+le, a[i])-dic;
		Add(i, pos, 1);
	}
}
//����k�йص������״���� 
void Add(int k, int pos, int x)
{
	for(int i=k;i<=n;i+=lowbit(i))
		Insert(1, le, i, pos, x);
}

int lowbit(int x)
{
	return x&(-x);
}
//����k�������ڲ��߶��� 
void Insert(int l, int r, int k, int pos, int x)
{
	if(l == r){
		p[k] += x;
		return;
	}
	int mid = (l+r)/2;
	if(pos<=mid){
		if(!tl[k])tl[k]=++tot;
		Insert(l, mid, tl[k], pos, x);
	}
	else{
		if(!tr[k])tr[k]=++tot;
		Insert(mid+1, r, tr[k], pos, x);
	}
	p[k] = p[tl[k]] + p[tr[k]];
}
//��ԭ����x�����޸�Ϊpk
void Update(int x, int pk)
{
	int pos = lower_bound(dic+1, dic+le+1, a[x])-dic;
	Add(x, pos, -1);
	pos = lower_bound(dic+1, dic+le+1, pk)-dic;
	Add(x, pos, 1);
	a[x] = pk;
}
//��ѯֵqk��������[ql,qr]������(xΪ1����������xΪ0��������)
//��ѯ�����qkС�����������Խ��ֱ����l-1��r�ܹ��ж��ٸ����ټ�һ�� 
int queryRank(int ql, int qr, int qk, int x)
{
	int pos = lower_bound(dic+1, dic+le+1, qk)-dic;
	int sum = 0;
	if(pos-x<1)return 0;
	for(int i=qr;i;i-=lowbit(i))
		sum += querymin(1, le, i, pos-x);
	for(int i=ql-1;i;i-=lowbit(i))
		sum -= querymin(1, le, i, pos-x);
	return sum;
}
//��ѯС�ڵ���x���������� 
int querymin(int l, int r, int k, int x)
{
	if(l == r && l == x)
		return p[k];
	int mid = (l+r)/2;
	if(x <= mid)
		return querymin(l, mid, tl[k], x);
	else
		return p[tl[k]]+querymin(mid+1, r, tr[k], x);
}
//������������Ϊk���� 
int queryVal(int l, int r, int k)
{
	lsz = rsz = 0;
	for(int i=l-1;i;i-=lowbit(i))
		vl[lsz++] = i;
	for(int i=r;i;i-=lowbit(i))
		vr[rsz++] = i;
	int ks = queryK(1, le, k);
	return dic[ks];
}
//��ѯ�ڲ㣬���kС
//����ÿһ���������ǰ��[l,r]�ڵ�����ж��ٸ� 
int queryK(int l, int r, int x)
{
	if(l == r)return l;
	int i, sum = 0;
	for(i=0;i<rsz;i++)
		sum += p[tl[vr[i]]];
	for(i=0;i<lsz;i++)
		sum -= p[tl[vl[i]]];
	int mid = (l+r)/2;
	if(x <= sum){
		for(i=0;i<rsz;i++)
			vr[i] = tl[vr[i]];
		for(i=0;i<lsz;i++)
			vl[i] = tl[vl[i]];
		return queryK(l, mid, x);
	}
	else {
		for(i=0;i<rsz;i++)
			vr[i] = tr[vr[i]];
		for(i=0;i<lsz;i++)
			vl[i] = tr[vl[i]];
		return queryK(mid+1, r, x-sum);
	} 
}
//����[ql,qr]��С��qk�������� 
int KsBefore(int ql, int qr, int qk)
{
	int num = queryRank(ql, qr, qk, 1);
	if(num == 0)return -1;
	return queryVal(ql, qr, num);
}
//����[ql,qr]�д���qk����С���� 
int KsAfter(int ql, int qr, int qk)
{
	int num = queryRank(ql, qr, qk, 0);
	if(num == qr-ql+1)return -1;
	return queryVal(ql, qr, num+1);
}
