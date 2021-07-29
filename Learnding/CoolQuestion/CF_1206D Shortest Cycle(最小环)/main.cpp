//floyd求最小环
//有n个数，如果ai & aj != 0 ,则i，j之间有边，求最小环 
//n的范围为100000，如果直接建所有边的话显然会超，可以发现
//如果某个二进制位为1的数有大于等于3个，则这三个就可以直接
//形成一个环，所以如果n>64*2,就可以直接输出3，
//对于n<=64*2的，n的范围不大，可以考虑用floyd跑最小环
//保存原图，对于每个路径i->j，如果i与j都与k相连，则这是一个环
//求最小的就好了
//题目链接：https://codeforces.com/problemset/problem/1206/D 
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
typedef pair<int, int> P;
const int maxn = 210;
LL res;
LL b[100100], a[maxn][maxn], c[maxn][maxn];
void floyd(int n);

int main()
{
	int n, i, j, k =1;
	scanf("%d", &n);
	for(i=1;i<=n;i++){
		LL x;
		scanf("%I64d", &x);
		if(x)b[k++] = x;
	}
	n = k-1;
	if(n >= 64*3)
		printf("3\n");
	else{
		res = INF;
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++)
				if(b[i] & b[j])a[i][j] = c[i][j] = 1;
				else a[i][j] = c[i][j] = INF;
			a[i][i] = c[i][i] = 0;
		}
		floyd(n);
		if(res == INF)
			printf("-1\n");
		else
			printf("%d\n", res);
	}
	return 0;
}

void floyd(int n)
{
	int i, j, k;
	for(k=1;k<=n;k++)
	{
		//找最小环
		//dis[i][j]作为最短路，然后i点，j点都有连向k的原始边
		//即为一个环 
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			if(i != j && i!=k && j!=k){
				res = min(res, c[i][k]+c[k][j]+a[i][j]);
			}
				
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			if(a[i][j] > a[i][k]+a[k][j])
				a[i][j] = a[i][k]+a[k][j];
	}
}
