//线段树
//对于第i个数，可以将它前面的(不包括自己)任意数变为0，
//求对于第i个数，最少将其前面几个数变为0，使a1+a2+..ai<=m
//思路:很容易想到对于每个数，去掉其前面最大的几个数
//然后优先队列等算一下，不过会超时
//问题可以转化为前i-1个数和小于m-a[i]即可，这个用
//线段树很容易就能求
//题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=6609
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
#define dbg printf("...............\n");
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 200100;
const int mod = 1e9;
struct node{
    int num;
    LL sum;
}p[4*maxn];
int a[maxn], id[maxn];
P q[maxn];
bool cmp(P a, P b);
void bulit(int l, int r, int k);
int query(int l, int r, LL x, int k);
void upd(int l, int r, int x, int k);

int main()
{
    int t, n, i, j, l1, l2;
    LL m, ans;
    scanf("%d", &t);
    while(t--){
        scanf("%d %lld", &n, &m);
        bulit(1, n, 1);
        for(i=1;i<=n;i++){
            scanf("%d", &a[i]);
            q[i].first = a[i];
            q[i].second = i;
        }
        sort(q+1, q+n+1, cmp);
        for(i=1;i<=n;i++)
            id[q[i].second] = i;
        for(i=1;i<=n;i++){
            int ans = query(1, n, m-a[i], 1);
            upd(1, n, id[i], 1);
            printf("%d ", i-1-ans);
        }
        printf("\n");
    }
    return 0;
}

bool cmp(P a, P b)
{
    return a.first < b.first;
}

void bulit(int l, int r, int k)
{
    p[k].sum = p[k].num = 0;
    if(l == r)return ;
    int mid = (l+r)/2;
    bulit(l, mid, 2*k);
    bulit(mid+1, r, 2*k+1);
}

int query(int l, int r, LL x, int k)
{
    if(x == 0 || l == r)return 0;
    int mid = (l+r) / 2;
    if(x < p[2*k].sum)
        return query(l, mid, x, 2*k);
    else
        return p[2*k].num + query(mid+1, r, x-p[2*k].sum, 2*k+1);
}

void upd(int l, int r, int x, int k)
{
    p[k].num++, p[k].sum += q[x].first;
    if(l == r)return;
    int mid = (l+r)/2;
    if(x <= mid)
        upd(l, mid, x, 2*k);
    else
        upd(mid+1, r, x, 2*k+1);
}
