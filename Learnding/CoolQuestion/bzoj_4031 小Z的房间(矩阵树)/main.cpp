//Matrix_tree定理
//Kirchhoff矩阵任意n-1阶子矩阵的行列式的绝对值就是无向图的生成树的数量。
//Kirchhoff矩阵的定义是度数矩阵-邻接矩阵。
//1、G的度数矩阵D[G]：n*n的矩阵，Dii等于Vi的度数，其余为0。
//2、G的邻接矩阵A[G]：n*n的矩阵， Vi、Vj之间有边直接相连，则 Aij=ij之间的边数，否则为0。
//题目链接：https://www.lydsy.com/JudgeOnline/problem.php?id=4031
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
const int maxn = 100;
const int mod = 1e9;
int id[maxn][maxn];
LL a[maxn][maxn];
int dx[4]={0,-1,0,1}, dy[4]={-1,0,1,0};
LL det(int n);
void getgrape(int n, int m, char str[][12]);

int main()
{
	int n, m, i, j, num = 0;
	char str[12][12];
	scanf("%d %d", &n, &m);
	for(i=0;i<n;i++){
		scanf("%s", str[i]);
		for(j=0;j<m;j++)
		if(str[i][j]=='.')
			id[i][j] = num++;
	}	
	getgrape(n, m, str);
	LL ans = det(num-1);
	printf("%d", ans);
	return 0;
}

void getgrape(int n, int m, char str[][12])
{
	int i, j, k, nx, ny;
	memset(a, 0, sizeof(a));
	for(i=0;i<n;i++)
		for(j=0;j<m;j++){
			if(str[i][j] != '*'){
				for(k=0;k<4;k++){
					nx = i + dx[k];
					ny = j + dy[k];
					if(nx>=0 && nx<n && ny>=0 && ny<m && str[nx][ny]=='.'){
						a[id[i][j]][id[i][j]]++,a[id[i][j]][id[nx][ny]]--;
					}
				}
			}	
		}
}
//高斯消元辗转消元法
//可避免精度问题，但时间复杂度为n*n*n*log n 
LL det(int n){
	LL i, j, k, t, ret=1;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			a[i][j] %= mod;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++)
			while(a[j][i]){
				t = a[i][i] / a[j][i];
				for(k=i;k<n;k++)
					a[i][k] = (a[i][k]-a[j][k]*t)%mod;
				swap(a[i], a[j]);
				ret = -ret;
			}
		if(a[i][i] == 0)
			return 0LL;
		ret = (ret*a[i][i]) % mod;
	}
	return (ret+mod)%mod;
}
