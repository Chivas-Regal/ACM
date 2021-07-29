/*****************************************************************************
随机化

有三个n*n的矩阵A、B、C，求A*B == C?

思路：直接求A*B，复杂度为n^3，会超时。随机一个1*n的矩阵X，若A*B == C,则X*A*B==X*C。
随机几组X进行检验。

题目链接：http://poj.org/problem?id=3318
*******************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-7
 
using namespace std;
typedef long long LL;   
typedef pair<LL, int> P;
const int maxn = 520;
const int mod = 998244353;
LL x[maxn], a1[maxn], a2[maxn], a3[maxn]; 
int a[maxn][maxn], b[maxn][maxn], c[maxn][maxn];
void mul(int n, LL x[], LL y[], int a[][520]);

int main()
{
    int n, i, j, k, sig = 1;
    scanf("%d", &n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d", &a[i][j]);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d", &b[i][j]);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d", &c[i][j]);
    for(int z=1;z<=10;z++)
    {
        for(i=0;i<n;i++)
            x[i] = rand()%130;
        mul(n, x, a1, a);
        mul(n, a1, a2, b);
        mul(n, x, a3, c);
        for(i=0;i<n;i++)
            if(a2[i] != a3[i])sig = 0;
    }
    if(sig)printf("YES\n");
    else printf("NO\n");
    return 0;
}

void mul(int n, LL x[], LL y[], int a[][520])
{
    int i, j, k;
    for(i=0;i<n;i++){
        y[i] = 0;
        for(j=0;j<n;j++)
            y[i] += x[j]*a[j][i];
    }
}