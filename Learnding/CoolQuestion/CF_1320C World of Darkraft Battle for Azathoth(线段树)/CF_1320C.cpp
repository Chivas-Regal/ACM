/**************************************************************************
线段树

有n把武器，m件防具，p只怪物，每把武器有攻击值ai、价格cai；每件防具有防御值bi、价格cbi；
怪物有防御值xi、攻击值yi、奖励zi。勇者可以(必须)选择购买一把武器和一件防具，当勇者的攻击值大于
怪物的防御值且勇者防御值大于怪物攻击值，则勇者可以击杀这只怪物并获得其对应的奖励。勇者可以
击杀多只怪物，每只怪物只能被击杀一次。求勇者能获得的最大收益(打怪奖励-武器价格-防具价格)。

思路：线段树。可以考虑对一种属性值排序，线段树维护另一种属性值的最大收益。这里对攻击排序，
然后线段树维护防御为某个值时的最大收益。初始的收益为防御值为其的防具的花费(负值)。
接下来考虑防御的变化对收益的影响，对于一个怪物，其攻击值为y,收益为z，那么所有防御值大于y的
收益都可以加上z。所以可以将防御值y+1到ymaxn(最大可达的防御)的部分收益都加上z。
所以，可以暴力枚举购买的武器，然后将所有防御低于该武器的攻击值的怪物收益加入线段树中。因为
武器攻击值有序，所以只需要加入防御大于等于上把武器，小于当前武器的怪物收益。然后统计线段树
中收益的最大值即可。
这边其实可以离散化一下，不过单属性最大1e6，不离散化应该也可以。
有点类似于二维偏序问题。

题目链接：http://codeforces.com/problemset/problem/1320/C
************************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<stack>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<LL, int> P;
const int maxn = 200100;
const int mod = 1000000007;
struct node{
    int a, b, p;
}atk[maxn], def[maxn], mon[maxn];
LL b[maxn], c[maxn], p[maxn*4], lz[maxn*4];
int lisan(int n, LL a[]);
void creat(int l, int r, int k);
void pushdown(int k);
bool cmp1(node a, node b);
bool cmp2(node a, node b);
void Update(int l, int r, int al, int ar, int x, int k);

int main()
{
    int n, m, q, i, j, k, len;
    LL ans = -1e16;
    scanf("%d %d %d", &n, &m, &q);
    for(i=1;i<=n;i++)
        scanf("%d %d", &atk[i].a, &atk[i].p);
    for(i=1;i<=m;i++){
        scanf("%d %d", &def[i].b, &def[i].p);
        b[i] = def[i].b;
    }
    for(i=1;i<=q;i++)
        scanf("%d %d %d", &mon[i].b, &mon[i].a, &mon[i].p);
    sort(atk+1, atk+1+n, cmp1);
    sort(mon+1, mon+1+q, cmp2);
    //离散化，初始化收益
    len = lisan(m, b);
    for(i=1;i<=len;i++)
        c[i] = -INF;
    for(i=1;i<=m;i++){
        int pos = lower_bound(b+1, b+1+len, def[i].b)-b;
        c[pos] = max(c[pos], -1LL*def[i].p);
    }
    for(i=len-1;i>=1;i--)
        c[i] = max(c[i], c[i+1]);
    creat(1, len, 1);
    //暴力考虑购买的武器
    j = 1;
    for(i=1;i<=n;i++)
    {
        //将攻击值变大所能击杀的怪物信息加入线段树中
        while(j<=q && mon[j].b < atk[i].a)
        {
            int pos = upper_bound(b+1, b+1+len, mon[j].a)-b;
            if(pos<=len)Update(1, len, pos, len, mon[j].p, 1);
            j++;
        }
        ans = max(ans, -atk[i].p+p[1]);
    }
    printf("%I64d\n", ans);
    return 0;
}

int lisan(int n, LL a[])
{
    sort(a+1, a+1+n);
    int top = 0, i;
    a[0] = a[1]-1;
    for(i=1;i<=n;i++)
        if(a[i] != a[top])a[++top] = a[i];
    return top;
}

void creat(int l, int r, int k)
{
    lz[k] = 0;
    if(l == r){
        p[k] = c[l];
        return;
    }
    int mid = (l+r)/2;
    creat(l, mid, 2*k);
    creat(mid+1, r, 2*k+1);
    p[k] = max(p[2*k], p[2*k+1]);
}

void Update(int l, int r, int al, int ar, int x, int k)
{
    if(l == al && r == ar){
        p[k] += x;
        lz[k] += x;
        return ;
    }
    pushdown(k);
    int mid = (l+r)/2;
    if(ar <= mid)Update(l, mid, al, ar, x, 2*k);
    else if(al>mid) Update(mid+1, r, al, ar, x, 2*k+1);
    else Update(l, mid, al, mid, x, 2*k), Update(mid+1, r, mid+1, ar, x, 2*k+1);
    p[k] = max(p[2*k], p[2*k+1]);
}

void pushdown(int k)
{
    if(lz[k])
    {
        p[2*k] += lz[k];
        p[2*k+1] += lz[k];
        lz[2*k] += lz[k];
        lz[2*k+1] += lz[k];
        lz[k] = 0;
    }
}

bool cmp1(node a, node b)
{
    return a.a < b.a;
}

bool cmp2(node a, node b)
{
    return a.b < b.b;
}