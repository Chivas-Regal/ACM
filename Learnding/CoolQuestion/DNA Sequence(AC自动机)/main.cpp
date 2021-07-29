//AC自动机+矩阵快速幂
//矩阵的n次幂，其中第i行第j列的值k代表从第i个节点出发，
//在第n步到达第j个节点有k种走法（离散数学）
// http://poj.org/problem?id=2778
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <set>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long int ll;
typedef pair<int,int> P;
struct node
{
	int id, flag;
	node *fail;
	node *nex[4];
 };
struct matrix
{
	//用ll存，否则运算过程中可能爆int 
	ll m[110][110];
}mat;
node *root;
int num;
const int mod = 100000;
void getfail();
node* creat();
int isid(char ch);
void insert(char str[]);
void bianli(node *p);
matrix mul(matrix a, matrix b);
matrix Pow(matrix a, int b);
matrix sermat();

int main()
{
	int m, n, i, j;
	char str[15];
	while(scanf("%d %d", &n, &m)!=EOF)
	{
		num = 0;
		root = creat();
		for(i=0;i<n;i++)
		{
			scanf(" %s", str);
			insert(str);
		}
		getfail();
		mat = sermat();
		mat = Pow(mat, m);
		/*for(i=0;i<num;i++)
		{
			for(j=0;j<num;j++)
				printf("%d ", mat.m[i][j]);
			printf("\n");
		}*/
		ll sum = 0;
		for(i=0;i<num;i++)
			sum = (sum + mat.m[0][i]) % mod;
		sum %= mod;
		printf("%lld\n", sum);
	}
	return 0;
}
//生成一个新的节点 
node* creat()
{
	node *p = new node;
	for(int i=0;i<4;i++)
		p->nex[i] = NULL;
	p->fail = NULL;
	p->flag = 0;
	p->id = num;
	num++;
	return p;
}

int isid(char ch)
{
	switch(ch)
	{
		case 'A':return 0;
		case 'C':return 1;
		case 'T':return 2;
		case 'G':return 3;
	}
}
//建树 
void insert(char str[])
{
	node *p = root;
	for(int i=0;str[i];i++)
	{
		int x = isid(str[i]);
		if(p->nex[x] == NULL)
			p->nex[x] = creat();
		p = p->nex[x];
	}
	p->flag = 1;
}

//获取fail指针 
void getfail()
{
	int i;
	node *p;
	queue<node*> que;
	que.push(root);
	while(!que.empty())
	{
		p = que.front();
		que.pop();
		for(i=0;i<4;i++)
		{
			if(p->nex[i] != NULL)
			{
				node *q = p->fail;
				while(q != NULL)
				{
					if(q->nex[i] != NULL)
					{
						p->nex[i]->fail = q->nex[i];
						break;
					}
					q = q->fail;
				}
				if(q == NULL)
					p->nex[i]->fail = root;
				//如果q的下一个节点是危险节点，则这个节点也是 
				if(q != NULL && q->nex[i]->flag)
					p->nex[i]->flag = 1;
				que.push(p->nex[i]);
			}
			else
				p->nex[i] = p == root ? root:p->fail->nex[i];
		}
	}
}

matrix sermat()
{
	int i, j, u, v, vis[150];
	matrix q;
	node *p = root;
	queue<node *> que;
	memset(q.m, 0, sizeof(q.m));
	memset(vis, 0, sizeof(vis));
	que.push(root);
	vis[p->id] = 1;
	while(!que.empty())
	{
		p = que.front();
		que.pop();
		for(i=0;i<4;i++)
		{
			//如果它不是危险节点，并且它下一个也不是危险节点
			//则这条路径加1 
			if(!p->flag && !p->nex[i]->flag)
				q.m[p->id][p->nex[i]->id]++;
			if(vis[p->nex[i]->id] == 0)
			{
				vis[p->nex[i]->id] = 1;
				que.push(p->nex[i]);
			}
		}
	}
	return q;
}

void bianli(node *p)
{
	for(int i=0;i<4;i++)
	{
		if(p->nex[i] == NULL)continue;
		if(p->nex[i]->flag == 1)
			printf("%d %d\n", p->nex[i]->id, i);
		bianli(p->nex[i]);
	}
}
//矩阵快速幂，单位矩阵乘以同阶矩阵A等于其A 
matrix Pow(matrix a, int b)
{
	matrix c;
	memset(c.m, 0, sizeof(c.m));
	for(int i=0;i<num;i++)
		c.m[i][i] = 1;
	while(b > 0)
	{
		if(b%2)c = mul(c, a);
		a = mul(a, a);
		b /= 2;
	}
	return c;
}

matrix mul(matrix a, matrix b)
{
	matrix c;
	for(int i=0;i<num;i++)
		for(int j=0;j<num;j++)
		{
			c.m[i][j] = 0;
			for(int k=0;k<num;k++)
				c.m[i][j] = (c.m[i][j] + a.m[i][k] * b.m[k][j]) % mod;
		}
	return c;
}
