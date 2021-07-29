//lca+���ϲ��
//��һ����������m���¼ӵıߣ��ʹ��ж����ַ�����һ��
//ԭ���ϵıߺ�һ���¼ӵıߣ�ʹͼ����ͨ�� 
//˼·������ÿ��ԭ�ߣ�����������ԭ�ߣ����ԭ�߲����� 
//�������¼ӵı������棬����m�ַ���(���ԭ�߾��Ѿ�����ͨ��
//ʣ��һ���±߿���ɾ������һ��);
//���ԭ�߱�����һ�Σ��ǲ������ԭ�ߵ��±ߣ��ڲ��ԭ��
//�������Ϊһ�ַ������ҽ���һ�֣�
//������������μ����ϣ�������ԭ��������ô�����������ʹͼ����ͨ

//����ʵ��˼·������ÿ���¼ӵıߣ�����������ԭ���ϵ�·����1
//(��Ϊ�����������·��Ψһ)���˲��ֿ��������ϲ��ʵ�֣�
//˼�����������Բ�֣���Ϊͳ�Ƶ��Ǳߣ����Զ����¼���ı�
//(s,t)��a[s]++,a[t++],a[lca(s,t)]-=2,��Ϊͳ�Ƶ��Ǳ߳��ִ���
//����lca(s,t)��Ҫ��ȥ2������ǵ�,��lca(s,t)��1���丸����1 
//����ÿ���ߣ�ͳ���䱻���ǹ��Ĵ��������δ�����ǹ�
//��ans+=m,��������ǹ�һ�Σ���ans++,�������ans���䡣
//ps:����Ῠvector 
//��Ŀ���ӣ� http://poj.org/problem?id=3417
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<string>
#include<ctype.h>
#include<cstring>
#include<stack>
#include<queue>
#include<iostream>
#include<iterator>
#define INF 100000000

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
struct node{
	int num;
	node* nex;
};
int m, a[maxn], root, dep[maxn], par[maxn][20];
LL ans; 
node* head[maxn];
void dfs(int v, int p, int d);
void init(int n);
int lca(int u, int v);
void end_dfs(int u);
void add(int f, int t);

int main()
{
	int n, i, f, t;
	scanf("%d %d", &n, &m);
	for(i=0;i<=n;i++)
		head[i] = NULL;
	ans = 0;
	for(i=1;i<n;i++){
		scanf("%d %d", &f, &t);
		add(f, t);
		add(t, f);
	}
	root = 1;
	init(n);
	for(i=1;i<=m;i++)
	{
		scanf("%d %d", &f, &t);
		if(f == t)continue;
		int fa = lca(f, t);
		//���������������1��lca��2 
		a[f]++, a[t]++, a[fa]-=2;
	}
	end_dfs(1);
	printf("%lld\n", ans);
	return 0;
}

void add(int f, int t)
{
	node *p = new node;
	p->nex = head[f];
	p->num = t;
	head[f] = p;
}

void dfs(int v, int p, int d){
	par[v][0] = p;
	dep[v] = d;
	node *q;
	for(q = head[v];q!=NULL;q=q->nex)
		if(q->num != p)dfs(q->num, v, d+1);
}

void init(int n)
{
	dfs(root, -1, 0);
	for(int k=0;k+1<17;k++)
		for(int v=1;v<=n;v++){
			if(par[v][k]<0)par[v][k+1] = -1;
			else par[v][k+1] = par[par[v][k]][k];
		}
}

int lca(int u, int v)
{
	if(dep[u]>dep[v]){
		int t=u;u=v;v=t;
	}
	for(int k=0;k<17;k++){
		if((dep[v]-dep[u])>>k &1)
			v = par[v][k];
	}
	if(u == v)return u;
	for(int k=16;k>=0;k--){
		if(par[u][k] != par[v][k]){
			u = par[u][k];
			v = par[v][k];
		}
	}
	return par[u][0];
}
//�ݹ�����������ֵ 
void end_dfs(int u)
{
	node *p;
	//��ǰ����ֵ�����������ӽ���ֵ�ͼ�������ֵ 
	for(p = head[u];p!=NULL;p=p->nex)
	{
		if(par[u][0] == p->num)continue;
		end_dfs(p->num);
		int &e = a[p->num];
		a[u] += e;
		if(e == 0)ans+=m;
		else if(e == 1)ans++;
	}
	
}
