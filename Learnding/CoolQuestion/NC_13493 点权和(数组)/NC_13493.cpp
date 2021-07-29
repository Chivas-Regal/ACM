/***********************************************************************
数组

一棵树，初始每个点权为0，每次操作可选择一个点x，将距离x小于等于1的点的点权都加上1，
求每次操作后，到x小于等于1的点权和。

每次询问只需要关心x，x的儿子节点，x的父节点的点权即可。
设数组b代表点被选中的次数，数组c代表点的儿子节点被选中的次数，数组d代表点的孙子节点被
选中的次数。
则点权和为3*b[x]+2*(c[x]+b[a[x]])+b[a[a[x]]]+d[x];
注意可能x点无父节点，则需要减去一部分的权值。

题目链接：https://ac.nowcoder.com/acm/problem/14393
**********************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#include<ctime>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-8
   
using namespace std;
typedef long long LL;  
typedef pair<int, int> P;
const int maxn = 100100;
const int mod = 19260817;
int a[maxn], sz[maxn], b[maxn], c[maxn], d[maxn];

int main()
{
    int n, m, i, j, k, x;
    LL ans = 0;
    scanf("%d %d", &n, &m);
    for(i=2;i<=n;i++){
        scanf("%d", &a[i]);
        sz[a[i]]++;
    }
    for(i=1;i<=m;i++){
        scanf("%d", &x);
        b[x]++;
        LL num = 0;
        if(a[x]){
            c[a[x]]++;
            num += 2*b[a[x]]+b[x]+(c[a[x]]-b[x]);
            if(a[a[x]])
                d[a[a[x]]]++, num += b[a[a[x]]];
        }
        num += b[x]*(sz[x]+1LL)+2*c[x]+d[x];
        num%=mod;
        ans = (ans+i%mod*num%mod)%mod;
    }
    printf("%lld\n", ans);
    return 0;
}