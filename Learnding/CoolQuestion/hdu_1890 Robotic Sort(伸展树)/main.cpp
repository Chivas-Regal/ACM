//伸展树
//有一个无序的序列，需要进行n次翻转，对于第i次翻转需要将第
//i小的树翻转至i，求每次翻转的右区间
//可以使用SPLAY+LAZY标记，先按原始序列建树，并记录每个值在
//树上的编号，然后对所有原本的数据进行排序，从小到大对每个值
//进行翻转，对于第i大的数，找出其在SPLAY上的编号，然后将其旋转
//至根结点，其左子树的大小+i就是答案，然后将此结点删除
//题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=1890 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
struct node{
    int fa, sz, lazy, childs[2];
}sp[maxn];
int tot, n, a[maxn], rk[maxn], st[maxn];
P p[maxn];
void clear();
bool findd(int x);
void update(int x);
void pushdown(int x);
void splay(int x, int to);
void rotate(int x);
int newpoint(int id, int val, int fa);
void connect(int x, int fa, int son);
int bulid(int l, int r, int fa, int son);
bool cmp(P a, P b);
void deleted(int x);
int solve(int x);
void debug();
void deleted(int x);

int main()
{
    int i, j, l, r, m, ans;
    while(scanf("%d", &n), n)
    {
        clear();
        for(i=1;i<=n;i++){
            scanf("%d", &a[i]);
            p[i].first = a[i], p[i].second = i;
        }
        sp[0].childs[1] = bulid(1, n, 0, 1);
        sort(p+1, p+1+n, cmp);
        for(i=1;i<=n;i++){
            if(i!=1)printf(" ");
            ans = solve(p[i].second)+i; 
            printf("%d", ans);
        }
        printf("\n");
    }
    return 0;
}
//建立原始伸展树 
int bulid(int l, int r, int fa, int son)
{
    if(l > r)return 0;
    int mid = (l+r)>>1;
    int pos = ++tot;
    rk[mid] = pos;
    connect(pos, fa, son);
    sp[pos].lazy = 0;
    sp[pos].childs[0] = bulid(l, mid-1, pos, 0);
    sp[pos].childs[1] = bulid(mid+1, r, pos, 1);
    update(pos);
    return pos;
}

void clear()
{
    tot = 0;
    sp[0].childs[0] = sp[0].childs[1] = sp[0].lazy = 0;
}

int newpoint(int id, int val, int fa)
{
    sp[++tot].fa = fa;
    sp[tot].lazy = sp[tot].childs[0] = sp[tot].childs[1] = 0;
    sp[tot].sz = 1;
    return tot;
}

bool cmp(P a, P b)
{
    if(a.first != b.first)
        return a.first < b.first;
    return a.second < b.second;
}
//返回x是其父亲的那个儿子 
bool findd(int x)
{
    return sp[sp[x].fa].childs[0]==x?0:1; 
}
//连接边，将x作为fa的son儿子 
void connect(int x, int fa, int son)
{
    sp[x].fa = fa;
    sp[fa].childs[son] = x;
}
//向下更新lazy标记 
void pushdown(int x)
{
    if(sp[x].lazy){
        sp[sp[x].childs[0]].lazy ^= 1;
        sp[sp[x].childs[1]].lazy ^= 1;
        swap(sp[x].childs[0], sp[x].childs[1]);
        sp[x].lazy = 0;
    }
    
}
//更新子树大小 
void update(int x)
{
    sp[x].sz = sp[sp[x].childs[0]].sz + sp[sp[x].childs[1]].sz + 1;
}
//旋转x到其父结点 
void rotate(int x)
{
    int Y = sp[x].fa;
    int R = sp[Y].fa;
    pushdown(Y), pushdown(x);
    int Yson = findd(x), Rson = findd(Y);
    int B = sp[x].childs[Yson^1];
    connect(B, Y, Yson);
    connect(Y, x, Yson^1);
    connect(x, R, Rson);
    update(Y), update(x);
}
//旋转x到to的位置 
void splay(int x, int to)
{
    to = sp[to].fa;
    while(sp[x].fa != to)
    {
        int y =sp[x].fa;
        //如果x父亲就是目标结点则旋转依次x 
        if(sp[y].fa == to)
            rotate(x);
        //如果x与其父亲，祖父三点一线，先旋转其父亲，在旋转x 
        else if(findd(x) == findd(y))
            rotate(y), rotate(x);
        //x与其父亲、祖父不在一条线上，旋转两次x即可 
        else
            rotate(x), rotate(x);
    }
}

int solve(int x)
{
    int now = rk[x], top = 0;
    while(now!=0){
        st[++top] = now;
        now = sp[now].fa;
    }
    while(top)
        pushdown(st[top--]);
    now = rk[x];
    splay(now, sp[0].childs[1]);
    pushdown(now);
    int res = sp[sp[now].childs[0]].sz;
    if(sp[now].childs[0])
        sp[sp[now].childs[0]].lazy ^= 1, pushdown(sp[now].childs[0]);
    deleted(now);
    return res;
}
//删除x结点 
void deleted(int x)
{
    int pos = x;
    if(!sp[pos].childs[0] && !sp[pos].childs[1])
        sp[0].childs[1] = 0;
    else if(!sp[pos].childs[0])
        connect(sp[pos].childs[1], 0, 1);
    else{
        int now = sp[pos].childs[0];
        pushdown(now);
        while(sp[now].childs[1]){
            now = sp[now].childs[1];
            pushdown(now);
        }  
        splay(now, sp[0].childs[1]);
        connect(sp[pos].childs[1], now, 1);
        connect(now, 0, 1);
        update(now);
    }    
}

void debug()
{
    printf("id   val  cnt   sz   child-left child-right\n");
    queue<int> que;
    que.push(sp[0].childs[1]);
    while(!que.empty())
    {
        int u = que.front();que.pop();
        if(!u)continue;
        printf("%-3d  %-3d  %-3d   %-3d  %-10d %-10d\n", u, sp[u].lazy, sp[u].lazy, sp[u].sz, sp[u].childs[0], sp[u].childs[1]);
        que.push(sp[u].childs[0]), que.push(sp[u].childs[1]);
    }
    printf("\n\n");
}
