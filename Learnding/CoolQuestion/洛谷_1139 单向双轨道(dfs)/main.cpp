//dfs+手写stack
//每一步由6种走法，暴力搜索求最短的路程 
//如果用STL的栈会超时，手写却会快很多很多 
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
const int maxn = 2010;
int n, minn, l1, l2, l3, l4;
char a[maxn], l[maxn], r[maxn];
char an[maxn], al[maxn], ar[maxn];
char str[39], st[6][120];
void dfs(int step, int j);

int main()
{
	minn = INF;
	scanf("%d %s", &n, str);
	l2 = l3 = l4 = 0;
	for(int i=0;i<n;i++)
		st[1][i+1] = i+'a';
	l1 = n;
	dfs(0, n-1);
	if(minn == INF)
		printf("NO\n");
	else
	for(int i=0;i<minn;i++)
		printf("%c %c %c\n", an[i], al[i], ar[i]);
	return 0;
}

void dfs(int step, int j)
{
	//if(step)
	//printf("%d %d %d\n", l[step-1], r[step-1], a[step-1]);
	if(step>minn)return;
	else if(l4 == n){
		if(minn == step)
		{
			for(int i=0;i<minn;i++)
			if(an[i]<a[i])return;
			else if(an[i]>a[i])break;
			else if(al[i]<l[i])return;
			else if(al[i]>l[i])break;
			else if(ar[i]<r[i])return;
			else if(ar[i]>r[i])break;	
		}
		minn = step;
		for(int i=0;i<minn;i++)
			an[i] = a[i], al[i] = l[i], ar[i] = r[i];
		return;
	}
	char lu;
	if(l1){
		lu = st[1][l1];
		l1--;
		l[step] = 'A';
		a[step] = lu;
		if(lu == str[j]){
			st[4][++l4] = lu;
			r[step] = 'D';
			dfs(step+1, j-1);
			l4--;
		}
		else{
			st[2][++l2] = lu;
			r[step] = 'B';
			dfs(step+1, j);
			l2--;
			
			st[3][++l3] = lu;
			r[step] = 'C';
			dfs(step+1, j);
			l3--;
		}
		l1++;
		st[1][l1] = lu;
	}
	if(l2){
		lu = st[2][l2];
		l2--;
		l[step] = 'B';
		a[step] = lu;
		if(lu == str[j]){
			st[4][++l4] = lu;
			r[step] = 'D';
			dfs(step+1, j-1);
			l4--;
		}
		else
		{
			st[3][++l3] = lu;
			r[step] = 'C';
			dfs(step+1, j);
			l3--;
		}
		l2++;
		st[2][l2] = lu;
	}
	if(l3 && st[3][l3] == str[j]){
		lu = st[3][l3];
		l3--;
		a[step] = lu;
		l[step] = 'C';
		r[step] = 'D';
		st[4][++l4] = lu;
		dfs(step+1, j-1);
		l4--;
		l3++;
		st[3][l3] = lu;
	}
}

/*
5
adcbe
*/
