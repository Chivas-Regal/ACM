//��չ��
//��һ����������У���Ҫ����n�η�ת�����ڵ�i�η�ת��Ҫ����
//iС������ת��i����ÿ�η�ת��������
//����ʹ��SPLAY+LAZY��ǣ��Ȱ�ԭʼ���н���������¼ÿ��ֵ��
//���ϵı�ţ�Ȼ�������ԭ�������ݽ������򣬴�С�����ÿ��ֵ
//���з�ת�����ڵ�i��������ҳ�����SPLAY�ϵı�ţ�Ȼ������ת
//������㣬���������Ĵ�С+i���Ǵ𰸣�Ȼ�󽫴˽��ɾ��
//��Ŀ���ӣ�http://acm.hdu.edu.cn/showproblem.php?pid=1890 
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
//����ԭʼ��չ�� 
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
//����x���丸�׵��Ǹ����� 
bool findd(int x)
{
    return sp[sp[x].fa].childs[0]==x?0:1; 
}
//���ӱߣ���x��Ϊfa��son���� 
void connect(int x, int fa, int son)
{
    sp[x].fa = fa;
    sp[fa].childs[son] = x;
}
//���¸���lazy��� 
void pushdown(int x)
{
    if(sp[x].lazy){
        sp[sp[x].childs[0]].lazy ^= 1;
        sp[sp[x].childs[1]].lazy ^= 1;
        swap(sp[x].childs[0], sp[x].childs[1]);
        sp[x].lazy = 0;
    }
    
}
//����������С 
void update(int x)
{
    sp[x].sz = sp[sp[x].childs[0]].sz + sp[sp[x].childs[1]].sz + 1;
}
//��תx���丸��� 
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
//��תx��to��λ�� 
void splay(int x, int to)
{
    to = sp[to].fa;
    while(sp[x].fa != to)
    {
        int y =sp[x].fa;
        //���x���׾���Ŀ��������ת����x 
        if(sp[y].fa == to)
            rotate(x);
        //���x���丸�ף��游����һ�ߣ�����ת�丸�ף�����תx 
        else if(findd(x) == findd(y))
            rotate(y), rotate(x);
        //x���丸�ס��游����һ�����ϣ���ת����x���� 
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
//ɾ��x��� 
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
