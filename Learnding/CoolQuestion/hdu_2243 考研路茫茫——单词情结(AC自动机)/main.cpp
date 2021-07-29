//AC自动机+矩阵快速幂
//和POJ2778那道题差不多，区别不过是一个求A的l次幂,
//一个是求26^1+26^2+...+26^l-(A^1+A^2+...+A^l)而已，POJ3233正好就是让求A^1+A^2+..A^l
//可以现在POJ上把2778和3233做了，
//参考博客：https://blog.csdn.net/xingyeyongheng/article/details/10005923
//————————————————————————————————————————————————————————————————————————————
//在经历了十几遍的错误以后终于对了，再求A^1+A^2+...A^l的过程中，二分计算写的有错误
//在l是奇数时，应该为(A^1+A^2+...+A^l-1)+A^l，结果写成了A*(A^1+A^2..+A^l-1)；
//真是致命，理所当然的在求26^1+26^2+26^3...+26^l犯了一模一样的错误。
//还有一点就是在输出unsigned __int64时，格式控制符应该是%I64u，一直用%I64d.
//http://acm.hdu.edu.cn/showproblem.php?pid=2243
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <set>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long int ll;
typedef pair<int,int> P;
struct node
{
    node *nex[27];
    node *fail;
    int id, flag;
};
struct matrix
{
    unsigned __int64 a[50][50];
};
node *root;
int num;
node *creat();
void insert(char str[]);
void getfail();
matrix getmat();
matrix erfen(matrix a, unsigned __int64 k);
matrix mul(matrix a, matrix b);
matrix add(matrix a, matrix b);
matrix Pow(matrix a, unsigned __int64 b);
unsigned __int64 erfen1(unsigned __int64 l);
unsigned __int64 Pow1(unsigned __int64 l, unsigned __int64 a);

int main()
{
    int n, i, j;
    unsigned __int64 l;
    char str[20];
    while(scanf("%d%I64d", &n, &l)!=EOF)
    {
        num = 0;
        root = creat();
        unsigned __int64 ts = 0;
        ts = erfen1(l);
        //printf("%I64d\n", ts);
        for(i=0;i<n;i++)
        {
            scanf(" %s", str);
            insert(str);
        }
        //printf("num:%d\n", num);
        getfail();
        matrix mat = getmat();
        mat = erfen(mat, l);
        /*for(i=0;i<num;i++)
        {
            for(j=0;j<num;j++)
                printf("%lld ", mat.a[i][j]);
            printf("\n");
        }*/
        for(i=0;i<num;i++)
            ts -= mat.a[0][i];
        if(ts < 0)
            ts += Pow1(64, 2);
        printf("%I64u\n", ts);
    }
    return 0;
}

node *creat()
{
    node *p = new node;
    for(int i=0;i<26;i++)
        p->nex[i] = NULL;
    p->fail = NULL;
    p->id = num;
    num++;
    p->flag = 0;
    return p;
}

void insert(char str[])
{
    //printf("%s\n", str);
    node *p = root;
    for(int i=0;str[i];i++)
    {
        int x = str[i] - 'a';
        if(p->nex[x] == NULL)
            p->nex[x] = creat();
        p = p->nex[x];
    }
    p->flag = 1;
}

void getfail()
{
    queue<node *> que;
    que.push(root);
    root->fail = NULL;
    while(!que.empty())
    {
        node *p = que.front();
        que.pop();
        for(int i=0;i<26;i++)
            if(p->nex[i] != NULL)
            {
                node *q = p->fail;
                while(q != NULL)
                {
                    if(q->nex[i] != NULL)
                    {
                        p->nex[i]->fail = q->nex[i];
                        break;
                    }
                    q = q->fail;
                }
                if(q == NULL)
                    p->nex[i]->fail = root;
                if(q!=NULL && q->nex[i]->flag)
                    p->nex[i]->flag = 1;
                que.push(p->nex[i]);
             }
            else
                p->nex[i] = p==root?root:p->fail->nex[i];
    }
}

matrix getmat()
{
    matrix mat;
    int i, vis[60];
    memset(mat.a, 0, sizeof(mat.a));
    memset(vis, 0, sizeof(vis));
    queue<node*> que;
    que.push(root);
    vis[root->id] = 1;
    while(!que.empty())
    {
        node *p = que.front();
        que.pop();
        for(i=0;i<26;i++)
        {
            if(!p->flag && !p->nex[i]->flag)
                mat.a[p->id][p->nex[i]->id]++;
            if(vis[p->nex[i]->id] == 0)
            {
                vis[p->nex[i]->id] = 1;
                que.push(p->nex[i]);
            }
        }
    }
    return mat;
}

unsigned __int64 erfen1(unsigned __int64 l)
{
    if(l == 1)
        return 26;
    else if(l == 0)
        return 1;
    if(l % 2)
        return erfen1(l-1)+Pow1(l, 26);
    else
    {
        unsigned __int64 t = erfen1(l/2);
        unsigned __int64 s = Pow1(l/2, 26);
        return t+t*s;
    }
}

unsigned __int64 Pow1(unsigned __int64 l, unsigned __int64 a)
{
    unsigned __int64 n = 1;
    while(l>0)
    {
        if(l%2)n*=a;
        a = a*a;
        l/=2;
    }
    return n;
 }

matrix erfen(matrix a, unsigned __int64 k)
{
    if(k == 1)return a;
    if(k % 2)
        return add(erfen(a, k-1), Pow(a, k));
    else
    {
        matrix c = erfen(a, k/2);
        matrix d = Pow(a, k/2);
        return add(c, mul(d, c));
    }
}

matrix Pow(matrix a, unsigned __int64 b)
{
    matrix n;
    memset(n.a, 0, sizeof(n.a));
    for(int i=0;i<num;i++)
        n.a[i][i] = 1;
    while(b>0)
    {
        if(b%2)n = mul(n, a);
        a = mul(a, a);
        b /= 2;
    }
    return n;
}

matrix mul(matrix a, matrix b)
{
    matrix d;
    memset(d.a, 0, sizeof(d.a));
    for(int i=0;i<num;i++)
        for(int j=0;j<num;j++)
        {
            for(int k=0;k<num;k++)
                d.a[i][j] += a.a[i][k] * b.a[k][j];
        }
    return d;
}

matrix add(matrix a, matrix b)
{
    matrix c;
    for(int i=0;i<num;i++)
        for(int j=0;j<num;j++)
            c.a[i][j] = a.a[i][j] + b.a[i][j];
    return c;
}
