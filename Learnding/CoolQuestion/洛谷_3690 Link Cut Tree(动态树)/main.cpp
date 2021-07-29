//LCT����̬��
//��ĿҪ���ѯ��̬�����ϵ�����֮���·������
//����ʹ�ö�̬������̬���ǽ�ԭ��������Ϊ����
//SPLAY��ÿ��SPLAY��Ľ����ȶ���һ�����������С��
//�������һ������ȴ��ǰ�棬Ȼ�����ͨ��access��makeroot 
//�Ȳ�������ά�����ϵ�ֵ
//��Ŀ���ӣ�https://www.luogu.org/problem/P3690 
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
#define eps 1e-6
  
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 300200;
const int mod = 1000000007;
struct node{
	int ch[2], fa, val, lz, sum;
}lct[maxn];
int n, stk[maxn];
void pushdown(int x);
void Update(int x);
bool noroot(int x);
void rotate(int x);
void splay(int x);
void access(int x);
void makeroot(int x);
int findroot(int x);
void link(int x, int y);
void cut(int x, int y);
void split(int x, int y);
int query(int x, int y);
void swapval(int x, int val);
void debug(int x, int n);

int main()
{
	int m, i, j;
	lct[0].ch[0] = lct[0].ch[1] = lct[0].fa = lct[0].lz = lct[0].sum = 0;
	scanf("%d %d", &n, &m);
	for(i=1;i<=n;i++){
		scanf("%d", &lct[i].val);
		lct[i].lz = 0;
		lct[i].sum = lct[i].val;
		lct[i].ch[0] = lct[i].ch[1] = lct[i].fa = 0;
	}
	while(m--)
	{
		int op, l, r;
		scanf("%d %d %d", &op, &l, &r);
		switch(op){
			case 0:printf("%d\n", query(l, r));break;
			case 1:link(l, r);break;
			case 2:cut(l, r);break;
			case 3:swapval(l, r);break;
		}
	}
	return 0;
}
//�´���� 
void pushdown(int x)
{
	if(lct[x].lz)
	{
		swap(lct[x].ch[0], lct[x].ch[1]);
		if(lct[x].ch[0])lct[lct[x].ch[0]].lz ^= lct[x].lz;
		if(lct[x].ch[1])lct[lct[x].ch[1]].lz ^= lct[x].lz;
		lct[x].lz = 0;
	}
}
//�������ϵ�ֵ 
void Update(int x)
{
	lct[x].sum = lct[x].val^lct[lct[x].ch[0]].sum^lct[lct[x].ch[1]].sum;
}
//�ж��Ƿ��ǵ�ǰSPLAY�ĸ� 
bool noroot(int x)
{
	return lct[lct[x].fa].ch[0] == x || lct[lct[x].fa].ch[1] == x;
}
//��ת 
void rotate(int x)
{
	int y = lct[x].fa, z = lct[y].fa;
	int k=lct[y].ch[1]==x, w=lct[x].ch[!k];
	if(noroot(y))lct[z].ch[lct[z].ch[1]==y] = x;
	lct[y].ch[k] = w, lct[x].ch[!k] = y;
	if(w)lct[w].fa = y;
	lct[x].fa = z, lct[y].fa = x;
	Update(y),Update(x);
}

void splay(int x)
{
	int top = 0, now = x;
	stk[++top] = now;
	while(noroot(now))stk[++top] = now = lct[now].fa;
	while(top)pushdown(stk[top--]);
	while(noroot(x))
	{
		int y = lct[x].fa, z= lct[y].fa;
		if(noroot(y))
			rotate((lct[y].ch[0]==x) ^ (lct[z].ch[0]==y)?x:y);
		rotate(x);
	}
	Update(x);
}
//��ͨx�����ڵ��·�� 
void access(int x)
{
	for(int y=0;x;y=x,x=lct[x].fa)
		splay(x), lct[x].ch[1] = y, Update(x);
}
//��x��Ϊԭ���ĸ� 
void makeroot(int x)
{
	access(x);splay(x);
	lct[x].lz ^= 1;
	pushdown(x);
}
//�ҵ�x���ڵ�ԭ���ĸ� 
int findroot(int x)
{
	access(x), splay(x);
	pushdown(x);
	while(lct[x].ch[0]){
		x = lct[x].ch[0];
		pushdown(x);
	}
	splay(x);
	return x;
}
//�����x-y 
void link(int x, int y)
{
	makeroot(y);
	if(findroot(x) != y)
		lct[y].fa = x;
}
//ɾ����x-y 
void cut(int x, int y)
{
	makeroot(x);
	if(findroot(y)==x && lct[y].fa ==x && !lct[y].ch[0]){
		lct[y].fa = lct[x].ch[1] = 0;
		Update(y), Update(x);
	}
}
//��ͨx-y��·�� 
void split(int x, int y)
{
	makeroot(x);
	access(y);splay(y);
}

int query(int x, int y)
{
	split(x, y);
	return lct[y].sum;
}

void swapval(int x, int val)
{
	splay(x);
	lct[x].val = val;
	Update(x);
}

void debug(int x, int n)
{
	queue<int> que;
	que.push(x);
	while(!que.empty())
	{
		x = que.front();que.pop();
		if(!x)continue;
		que.push(lct[x].ch[1]);
		que.push(lct[x].ch[0]);
		printf("id:%d %d %d %d %d %d\n", x, lct[x].sum, lct[x].val, lct[x].ch[0], lct[x].ch[1], lct[x].fa); 
	}
	printf("all tree node:\n");
	for(x=1;x<=n;x++)
		printf("id:%d %d %d %d %d %d\n", x, lct[x].sum, lct[x].val, lct[x].ch[0], lct[x].ch[1], lct[x].fa); 
}
/*
4 100
1 2 4 8
1 1 2
1 1 3
1 1 4
0 2 4
0 2 2 
0 4 4 
2 1 2
1 2 4
0 2 4
*/
