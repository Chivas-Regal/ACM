//��״����
//��άƫ�����⣬��һ��1~n�����У�������[l,r]���ж��ٶ�
//(i,j)ʹai%aj==0||aj%ai==0
//����ÿ��ai�������ҳ��ܺ�������������ϵ������aj��������
//aj���Ǹ��±꣬��j����Ϊi��j�����ظ��������нϴ�Ĵ����С���� 
//������ѯ�ʰ�l�ݼ�����Ȼ��l�ұߵ�����ai�����������±�
//����������״�����ڣ�Ȼ�����sum(r)����Ϊ���� 
//��Ŀ���ӣ� http://codeforces.com/problemset/problem/301/D
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
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 200100;
struct node{
	int id, l, r;
}pb[maxn];
int n, p[maxn], a[maxn], b[maxn], ans[maxn];
vector<int> g[maxn];
int sum(int x);
int lowbit(int x);
bool cmp(node a, node b);
void add(int x, int ad);

int main()
{
	int m, i, j;
	scanf("%d %d", &n, &m);
	for(i=1;i<=n;i++){
		scanf("%d", &a[i]);
		b[a[i]] = i;
	}
	//Ԥ������������������ģ������ϴ���±�����С���� 
	for(i=1;i<=n;i++)
		for(j=a[i];j<=n;j+=a[i])
		{
			if(i < b[j])
				g[i].push_back(b[j]);
			else
				g[b[j]].push_back(i);
		}
	for(i=1;i<=m;i++){
		scanf("%d %d", &pb[i].l, &pb[i].r);
		pb[i].id = i;
	}
	sort(pb+1, pb+1+m, cmp);
	int maxx = n+1;
	for(i=1;i<=m;i++){
		for(j=pb[i].l;j<maxx;j++){
			for(int k=0;k<g[j].size();k++)
				add(g[j][k], 1);
		}
		maxx = pb[i].l;
		ans[pb[i].id] = sum(pb[i].r);
	}
	for(i=1;i<=m;i++)
		printf("%d\n", ans[i]);
	return 0;
}

bool cmp(node a, node b)
{
	return a.l > b.l;
}

int lowbit(int x)
{
	return x&(-x);
}

void add(int x, int ad)
{
	for(int i=x;i<=n;i+=lowbit(i))
		p[i] += ad; 
}

int sum(int x)
{
	int sum = 0;
	for(int i=x;i;i-=lowbit(i))
		sum += p[i];
	return sum;
}
