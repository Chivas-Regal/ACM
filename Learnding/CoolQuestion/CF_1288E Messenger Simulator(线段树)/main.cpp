/************************************************
线段树+思路

有1~n共n个数，按序依次在位置1~n，共有m次操作，每次操作可以将数字i移动至第一个位置前，i之前
的数依次后移，求每个数最大在过的位置和最小在过的位置。

思路：显然初始的最大位置最小位置都是原本的位置，一个数如果移动过，则最小的位置变为1.
对于最大位置，对于每次移动数字i，其所在位置为a[i],他的位置会变为1，原本位置为1~a[i]的
位置都会依次后移，a[i]之后的数位置不变。同时可以发现，一个数的最大位置，要不在移动时的位置
要不在最后状态。因为每次移动，所以可以考虑将数倒着放，每次将移动的数放至最后一个新的位置，
原位置为空。然后每次更新查询即可，线段树区间更新，点查询即可。

题目链接：http://codeforces.com/problemset/problem/1288/E
**************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<map>
#include<queue>
#include<stack>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 600100;
const int mod = 1000000007;
int a[maxn], b[maxn], mx[maxn], mi[maxn], p[maxn*4];
void Update(int l, int r, int al, int ar, int k);
int query(int l, int r, int x, int ans, int k);

int main()
{
    int n, m, s, ed, i, j, k;
    scanf("%d %d", &n, &m);
    s = n+m, ed = n;
    for(i=1;i<=n;i++){
        mi[i] = mx[i] = i;
        Update(1, s, 1, i, 1);
        a[n+1-i] = i;
    }
    while(m--)
    {
        scanf("%d", &i);
        mi[i] = 1;
        mx[i] = max(mx[i], query(1, s, a[i], 0, 1));
        ed++;
        Update(1, s, a[i], ed, 1);
        a[i] = ed;
    }
    for(i=1;i<=n;i++)
        mx[i] = max(mx[i], query(1, s, a[i], 0, 1));
    for(i=1;i<=n;i++)
        printf("%d %d\n", mi[i], mx[i]);
    return 0;
}

void Update(int l, int r, int al, int ar, int k)
{
    if(l == al && r == ar){
        p[k]++;
        return;
    }
    int mid = (l+r)/2;
    if(ar<=mid)Update(l, mid, al, ar, 2*k);
    else if(al > mid)Update(mid+1, r, al, ar, 2*k+1);
    else Update(l, mid, al, mid, 2*k), Update(mid+1, r, mid+1, ar, 2*k+1);
}

int query(int l, int r, int x, int ans, int k)
{
    ans += p[k];
    if(l == r)return ans;
    int mid = (l+r)/2;
    if(x <= mid)return query(l, mid, x, ans, 2*k);
    else return query(mid+1, r, x, ans, 2*k+1);
}