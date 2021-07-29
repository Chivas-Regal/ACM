/***************************************************
DFS+贪心

有一个序列包含n个非负整数，现在需要找一个X，是所有的数对X异或的最大值最小，求最小的结果。

思路：设T=max(ai^X) i属于1~n，题目要求最小的T。因为求的是异或，所以各二进制位对结果的贡献是独立的。所以可以考虑从高到低确定每个二进制位。设当前考虑到第step位二进制位，之前的二进制位都已确定，且对结果贡献为ans。
1.如果当前所有数二进制下的第step位都相同，为了最小化T，应该令X的第step也与所有数一样，此时第step位两者异或为0，对ans贡献为0.
2.如果当前所有数二进制位的第step位不同，一部分为1，一部分为0。无论X的第step位是0还是1，都会与另一部分的数异或为1，所以对ans的贡献为1<<step。可以将第step位为1和为0的分开，分别考虑第step+1位，取最终得到的ans的最小值即可。

题目链接：https://codeforces.com/problemset/problem/1285/D
*******************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
const int mod = 1000000007;
vector<int> g[maxn];
int res, num, a[maxn], b[maxn];
void dfs(int u, int step, int ans);

int main()
{
	int n, i, j, k;
	num = 0;
	res = 1<<30;
	scanf("%d", &n);
	for(i=0;i<n;i++)
	{
		scanf("%d", &j);
		g[0].push_back(j);
	}
	dfs(0, 30, 0);
	printf("%d\n", res);
	return 0;
}

void dfs(int u, int step, int ans)
{
	int i, on, ze, n1, n2, ans2 = ans|(1<<step);
	n1 = n2 = 0;
	for(i=0;i<g[u].size();i++)
	{
		if( g[u][i] & (1<<step) )a[++n1] = g[u][i];
		else b[++n2] = g[u][i];
	}
	//这里是为了节省空间，写的有点乱，可以用其他更合适的数据结构维护
	//这里的主要目的是将第step位为0和为1的数分开，
	if(n1 && n2 == 0)on = u;
	else if(n2 && n1 == 0)ze = u;
	else{
		g[u].clear();
		if(n1 > n2)on = u, ze = ++num;
		else ze = u, on = ++num;
		for(i=1;i<=n1;i++)g[on].push_back(a[i]);
		for(i=1;i<=n2;i++)g[ze].push_back(b[i]);
	}
	if(n1 && n2)
	{
		if(step){
			dfs(on, step-1, ans2);
			dfs(ze, step-1, ans2);
		}
		else res = min(res, ans2);
	}
	else if(n2){
		if(step)dfs(ze, step-1, ans);
		else res = min(res, ans);
	}
	else if(n1){
		if(step)dfs(on, step-1, ans);
		else res = min(res, ans);
	}
}