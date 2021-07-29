//�����ʷ�
//����һ����������ֽ�Ϊ���������Ȼ�����ʹ���߶���
//�����ݽṹ��ά�����ϵ�ֵ��һ������֤�������������
//�����ϵı��������
//��l��r·���������������Խ��п��ٵļӼ���ͳ�Ʋ���
//��ĳ�������Ҳ���Խ��мӼ���ͳ�Ʋ���
//��Ŀ���ӣ�https://www.luogu.org/problem/P3384
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
const int mod = 1e9;
struct node{
	LL sum, lazy;
}p[maxn*4];
//fa����Ž��ĸ���� son����Ž����ض���
//de���������       size�����������С
//id�����±�ź���ԭ����Ӧ�ı��
//rk�����±�ź����Ŷ�Ӧ��ԭ��� 
int cnt, fa[maxn], son[maxn], de[maxn], size[maxn], top[maxn];
int id[maxn], rk[maxn];
int n, a[maxn], b[maxn];
LL ans, modd;
vector<int> g[maxn];
void dfs1(int f, int u, int d);
void dfs2(int t, int u);
void bulit(int l, int r, int k);
void upd(int l, int r, int al, int ar, int x, int k);
void down(int k, int l);
void query(int l, int r, int al, int ar, int k);
void quiry(int l, int r);
void road_upd(int l, int r, int x);

int main()
{
	int t, i, j, k, m, l, r, root;
	scanf("%d %d %d %lld", &n, &m, &root, &modd);
	for(i=1;i<=n;i++)
		scanf("%d", &a[i]);
	for(i=1;i<n;i++){
		scanf("%d %d", &j, &k);
		g[j].push_back(k);
		g[k].push_back(j);
	}
	dfs1(-1, root, 1);
	dfs2(root, root);
	for(i=1;i<=n;i++)
		b[id[i]] = a[i];
	bulit(1, n, 1);
	while(m--){
		int x;
		scanf("%d", &t);
		switch(t){
			case 1:
				scanf("%d %d %d", &l, &r, &x);
				road_upd(l, r, x);
				break;
			case 2:
				scanf("%d %d", &l, &r);
				quiry(l, r);
				printf("%lld\n", ans);
				break;
			case 3:
				//l������������r����id[l]+size[l]-1 
				scanf("%d %d", &l, &r);
				upd(1, n, id[l], id[l]+size[l]-1, r, 1);
				break;
			case 4:
				scanf("%d", &x);
				ans = 0;
				query(1, n, id[x], id[x]+size[x]-1, 1);
				printf("%lld\n", ans);
				break;
		}
	}
	return 0;
}

void dfs1(int f, int u, int d){
	//��¼���������������������Ϊ�ض��� 
	int mx = -1;
	fa[u] = f;
	size[u] = 1;
	de[u] = d;
	for(int i=0;i<g[u].size();i++){
		if(g[u][i] != f){
			dfs1(u, g[u][i], d+1);
			size[u] += size[g[u][i]];
			if(mx == -1 || size[g[u][i]]>size[mx])
				mx = g[u][i];
		}
	}
	son[u] = mx;
}
//t:u�ĸ���㣬u��ǰ��� 
void dfs2(int t, int u){
	top[u] = t;
	id[u] = ++cnt;
	rk[cnt] = u;
	//�ȱ����ض��ӣ��Ա�֤����������� 
	if(son[u]==-1)return;
	dfs2(t, son[u]);
	for(int i=0;i<g[u].size();i++){
		if(g[u][i] != fa[u] && g[u][i] != son[u])
			dfs2(g[u][i], g[u][i]);
	}
}

void bulit(int l, int r, int k)
{
	p[k].lazy = 0;
	if(l == r){
		p[k].sum = b[l] % modd;
		return;
	}
	int mid = (l+r)/2;
	bulit(l, mid, 2*k);
	bulit(mid+1, r, 2*k+1);
	p[k].sum = (p[2*k].sum + p[2*k+1].sum) % modd;
}

void upd(int l, int r, int al, int ar, int x, int k){
	//����ǰ��lazy��Ǽ������ 
	down(k, r-l+1);
	if(l == al && r == ar){
		p[k].lazy = x;
		down(k, r-l+1);
		return;
	}
	//[al,ar]���䶼����x����ǰ�����ܺͼ���(ar-al+1)*x;
	p[k].sum = (p[k].sum + (ar-al+1)*x%modd) % modd;
	int mid = (l+r)/2;
	if(ar <= mid)
		upd(l, mid, al, ar, x, 2*k);
	else if(al>mid)
		upd(mid+1, r, al, ar, x, 2*k+1);
	else{
		upd(l, mid, al, mid, x, 2*k);
		upd(mid+1, r, mid+1, ar, x, 2*k+1);
	}
}

void query(int l, int r, int al, int ar, int k){
	down(k, r-l+1);
	if(l == al && r == ar){
		ans = (ans + p[k].sum)%modd;
		return;
	}
	int mid = (l+r)/2;
	if(ar <= mid)
		query(l, mid, al, ar, 2*k);
	else if(al>mid)
		query(mid+1, r, al, ar, 2*k+1);
	else{
		query(l, mid, al, mid, 2*k);
		query(mid+1, r, mid+1, ar, 2*k+1);
	}
}

//����ǰ�����lazy��Ǽӵ�sum�У�����lazy�������
//�Ա�֤��ǰ����sumֵ��ȷ 
void down(int k, int l){
	p[k].sum = (p[k].sum +  p[k].lazy * l % modd)%modd;
	if(l != 1){
		p[2*k].lazy = (p[2*k].lazy+p[k].lazy) % modd;
		p[2*k+1].lazy = (p[2*k+1].lazy+p[k].lazy) % modd;	
	}
	p[k].lazy = 0;
}
//��l��r��·���ϵ����е����x 
//Ѱ��LCA����ͨ��top���� 
void road_upd(int l, int r, int x){
	//������㲻��һ�������ϣ��������������Ƚϴ� 
	//�����ȼ���(������ƶ���Ƚ�С�ģ����ܴ��LCA) 
	while(top[l] != top[r]){
		if(de[top[l]] > de[top[r]]){
			//�����������������Ϊ�������ڵ�ĸ���� 
			upd(1, n, id[top[l]], id[l], x, 1); 
			l = fa[top[l]];
		}else{
			upd(1, n, id[top[r]], id[r], x, 1);
			r = fa[top[r]];
		}
	}
	//��ͬһ�������ϣ����¼��� 
	if(de[l] > de[r])
		upd(1, n, id[r], id[l], x, 1);
	else
		upd(1, n, id[l], id[r], x, 1);
}

void quiry(int l, int r){
	ans = 0;
	while(top[l] != top[r]){
		if(de[top[l]] > de[top[r]]){
			query(1, n, id[top[l]], id[l], 1);
			l = fa[top[l]];
		}
		else{
			query(1, n, id[top[r]], id[r], 1);
			r = fa[top[r]];
		}
	}
	if(de[l] > de[r])
		query(1, n, id[r], id[l], 1);
	else
		query(1, n, id[l], id[r], 1);
}
