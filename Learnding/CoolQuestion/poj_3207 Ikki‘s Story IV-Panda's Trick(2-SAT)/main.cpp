//2-SAT
//有一个环，在i和j点连一条链(链只能在环内或环外，不能
//穿过环的边界)，链为从i，j中较小的连向较大的
//思路：典型的2-SAT问题，在构图时，注意边i->j的含义
//是如果i成立，则j一定成立，对于每条链，如果一条链
//的起点在另一条链中间，两条链必然一个在内，一个在外
//然后trajan缩点即可，如果i和!i在一个强连通分量内，则
//不成立
//题目链接: http://poj.org/problem?id=3207
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
const int maxn = 100100;
int top, sum, tot, dfn[maxn], low[maxn], vis[maxn], stack[maxn], color[maxn];
int cnt, hd[maxn], nex[3*maxn], to[3*maxn];
P p[520];
void init(int n);
void add(int f, int t);
void trajan(int u);
bool isok(int a, int b, int c);

int main()
{
    int n, m, i, j, a1, a2, b1, b2;
    while(~scanf("%d %d", &n, &m))
    {
        init(n);
        for(i=0;i<m;i++){
        	scanf("%d %d", &p[i].first, &p[i].second);
        	if(p[i].first>p[i].second)swap(p[i].first, p[i].second);
		}
        for(i=0;i<m;i++)
        	for(j=i+1;j<m;j++)
			{
				int a=p[i].first, b=p[i].second, c=p[j].first, d=p[j].second;
				if(isok(a, c, d) && b>d || isok(b, c, d)&& a< c){
					add(2*i, 2*j+1);
					add(2*j+1, 2*i);
					add(2*j, 2*i+1);
					add(2*i+1, 2*j);
				}
			}	
        for(i=0;i<m;i++){
        	if(!dfn[2*i])trajan(2*i);
        	if(!dfn[2*i+1])trajan(2*i+1);
		}
		for(i=0;i<m;i++)
		//如果i和非i在同一scc内，则不成立 
		if(color[2*i] == color[2*i+1])
			break;
		/*可以输出一组可行解 
		for(i=0;i<m;i++)
		if(a[2*i] > a[2*i-1])printf("%d\n", 2*i);
		else printf("%d\n", 2*i-1);*/
		if(i == m)
			printf("panda is telling the truth...\n");
		else
			printf("the evil panda is lying again\n");
    }
    return 0;
}

void add(int f, int t)
{
	to[++cnt] = t;
	nex[cnt] = hd[f];
	hd[f] = cnt;
}

void init(int n)
{
	cnt = top = sum = tot = 0;
    memset(hd, 0, sizeof(hd));
    memset(dfn, 0, sizeof(dfn));
    memset(vis, 0, sizeof(vis));
}

void trajan(int u)
{
	dfn[u] = low[u] = ++tot;
	stack[++top] = u;
	vis[u] = 1;
	for(int i=hd[u];i;i=nex[i])
	{
		if(!dfn[to[i]]){
			trajan(to[i]);
			low[u] = min(low[u], low[to[i]]);
		}
		else if(dfn[to[i]] && vis[to[i]]){
			low[u] = min(low[u], dfn[to[i]]);
		}
	}
	if(dfn[u] == low[u]){
		sum++;
		while(stack[top] != u){
			color[stack[top]] = sum;
			vis[stack[top--]] = 0;
		}
		color[stack[top--]] = sum;
	} 
}

bool isok(int a, int b, int c)
{
	return a>b && a<c; 
}
