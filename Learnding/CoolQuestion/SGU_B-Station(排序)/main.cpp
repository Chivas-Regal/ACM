/***********************************************************
排序

有n个容器分布在n层，每一层的容器有三个值wi,li,pi分别是容器内水的体积，容器的容积和手动摧毁
容器的代价。如果容器内的水的体积超过容器的容积，容器将会被摧毁，容器里的水会全部流到下一层容器，
容器也可以被手动摧毁，但需要取出pi的代价。求摧毁最低层(第n个)容器最小的代价。

思路：摧毁第n个容器，则一定是将某一层的之后的容器全部摧毁。分别求从第i层开始摧毁的代价，取
最小值即可。但这样是O(n^2)的，显然不行。已知第i层之后全部摧毁的结果，那第i+1层的结果呢？
摧毁第i层的花费，同时所有层被摧毁时的水量相比上一次结果都少了wi。部分的可能需要由自动
摧毁变为手动摧毁。
优先处理出全部摧毁的结果，每一层按 被摧毁时的水的体积-容器 为键值排序。然后分别考虑2,3,..
n-1。每次统计出由自动摧毁变为手动摧毁的代价和即可。

题目链接：http://codeforces.com/problemsets/acmsguru/problem/99999/148
***************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<set>
#include<queue>
#include<stack>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 15100;
const int mod = 10007;
struct node{
    int id, ch;
}a[maxn];
int w[maxn], l[maxn], p[maxn];
bool cmp(node a, node b);

int main()
{
    int n, i, j, k, sum, psum, num;
    int mi, pos;
    sum = psum = num = 0;
    scanf("%d", &n);
    for(i=1;i<=n;i++)
        scanf("%d %d %d", &w[i], &l[i], &p[i]);
    for(i=1;i<=n;i++){
        sum += w[i];
        a[i].id = i, a[i].ch = sum - l[i];
    }
    sort(a+1, a+1+n, cmp);
    sum = 0;
    j = 1;
    while(j<=n && a[j].ch-sum <= 0)
        psum += p[a[j].id], j++;
    mi = psum, pos = 0;
    for(i=1;i<n;i++)
    {
        sum += w[i], psum -= p[i];
        while(j<=n && a[j].ch-sum <= 0)
            psum += p[a[j].id], j++;
        if(psum < mi){
            mi = psum, pos = i;
        }
    }
    sum = 0;
    for(i=pos+1;i<=n;i++)
    {
        sum += w[i];
        if(sum <= l[i])printf("%d\n", i);
    }
    return 0;
}

bool cmp(node a, node b)
{
    return a.ch < b.ch;
}