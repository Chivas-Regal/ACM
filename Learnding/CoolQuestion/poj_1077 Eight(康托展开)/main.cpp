//bfs+hash
//一个拼图游戏，问能否还原成原来的状态
//因为总共有九块拼图，所以给每块编号(按初始位置)
//看其能否变为初始的序列，即1 2 3 4 5 6 7 8 9
//可以考虑bfs，对于状态的记录，可以考虑康托展开
//对于每个排列，将其hash为数，记录状态
//康托展开： 
//一个排列是全排列的第num个
//num =  an*(n-1)! + an-1*(n-2)! +.....+ a1* 0!
//ai为排列中，下标为i后面的，比下标i对应的数小的数的数量
//逆康托展开：
//共有n个数的全排列的第num个排列为
//对于第i位，设a = num / (n-i)!, b = num % (n-i)!
//第a+1个未使用过的数即为当前位的数，b为下一位的num 
//题目链接：http://poj.org/problem?id=1077
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
const int maxn = 1001000;
const int mod = 998244353;
struct node{
	int id, x, y;
	node(){}
	node(int a, int b, int c){
		id = a, x = b , y = c;
	}
};
int a[16], b[16], c[16], fac[16], vis[maxn];
int dx[4] = {0,-1,0,1}, dy[4] = {-1,0,1,0};
char str[520];
int contor(int n, int a[]);
void pretrean(int n, int a[]);
void revcontor(int n, int a[], int num);
void priset(int n, int a[], int bx, int by);

int main()
{
	int i, n, j, bx, by;
	fac[0] = fac[1] = 1;
	//预处理出阶乘，加速运算 
	for(i=2;i<=12;i++)
		fac[i] = i*fac[i-1];
	n = 9;
	pretrean(n, a);
	while(gets(str))
	{
		n = 0;
		for(i=0;str[i];i++)
		{
			char ch = str[i];
			if(ch == 'x'){
				a[++n] = 9;
				bx = (n-1) / 3 + 1;
				if(n%3 == 0)by = 3;
				else by = n%3;
			}
			else if(isdigit(ch)) a[++n] = ch-'0';
		}
		int id = contor(n, a);
		if(!vis[id])printf("unsolvable\n");
		else priset(n, a, bx, by);
	}
	
	return 0;
}
//提取路径，将找出当前状态到初始状态的路径 
void priset(int n, int a[], int bx, int by)
{
	int i, id, id1;
	id = contor(n, a);
	queue<char> st;
	queue<node> que;
	que.push(node(id, bx, by));
	while(!que.empty())
	{
		node p = que.front();que.pop();
		if(p.id == 1)break;
		revcontor(n, a, p.id);
		for(i=0;i<4;i++)
		{
			int nx = p.x + dx[i];
			int ny = p.y + dy[i];
			if(nx>=1 && nx<=3 && ny>=1 && ny<=3)
			{
				swap(a[nx*3+ny-3], a[p.x*3+p.y-3]);
				id1 = contor(n, a);
				if(vis[id1] == vis[p.id]-1)
				{
					if(i == 0)st.push('l');
					else if(i==1)st.push('u');
					else if(i==2)st.push('r');
					else if(i==3)st.push('d');
					que.push(node(id1, nx, ny));break;
				}
				swap(a[nx*3+ny-3], a[p.x*3+p.y-3]);
			}
		}
	}
	while(!st.empty())
	{
		printf("%c", st.front());st.pop();
	}
	printf("\n");
}
//预处理出所有能够存在的状态 
void pretrean(int n, int a[])
{
	int i, j, id, id1;
	memset(vis, 0, sizeof(vis));
	for(int i=1;i<=n;i++)
		a[i] = i;
	id = contor(n, a);
	queue<node> que;
	que.push(node(id, 3, 3));
	vis[id] = 1;
	while(!que.empty())
	{
		node p = que.front();que.pop();
		revcontor(n, a, p.id);
		for(i=0;i<4;i++)
		{
			int nx = p.x + dx[i];
			int ny = p.y + dy[i];
			if(nx>=1 && nx<=3 && ny>=1 && ny<=3)
			{
				swap(a[nx*3+ny-3], a[p.x*3+p.y-3]);
				id1 = contor(n, a);
				if(!vis[id1])
				{
					vis[id1] = vis[p.id] + 1;
					que.push(node(id1, nx, ny));
				}
				swap(a[nx*3+ny-3], a[p.x*3+p.y-3]);
			}
		}
	}
}
//康托展开，求n个数的排列，是第几个全排列 
int contor(int n, int a[])
{
	int num = 0, n1;
	memset(c, 0, sizeof(c));
	for(int i=1;i<=n;i++)
	{
		n1 = 0;
		for(int j=1;j<a[i];j++)
			if(!c[j])n1++;
		num += fac[n-i]*n1;
		c[a[i]] = 1;
	}
	return num+1;
}
//求n个数的排列的第num个 
void revcontor(int n, int a[], int num)
{
	num--;
	int i, j, n1;
	memset(c, 0, sizeof(c));
	for(i=1;i<=n;i++)
	{
		n1 = num / fac[n-i] + 1;
		for(j=1;;j++)
		{
			if(!c[j])n1--;
			if(!n1)break;
		}
		a[i] = j;
		num %= fac[n-i];
		c[a[i]] = 1;
	}
}
