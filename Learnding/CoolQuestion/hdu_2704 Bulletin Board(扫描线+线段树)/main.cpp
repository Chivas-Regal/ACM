/************************************************
扫描线+线段树
有一个w*h大的公告板，有n张长方形海报贴在上面，求公告板未被覆盖的面积，海报的最大厚度，厚度等于最大厚度的面积。

思路：对于求公告板未被覆盖的面积，可以通过扫描线+线段树来求出被覆盖的面积S，然后那总面积-S即可。第二个问题，可以在线段树维护的时候同时维护每个点(区间)被覆盖的次数，求最大的次数即可。第三个问题，可以再维护一个区间中等于最大厚度的长度。扫描线扫描结束，即可求出三个问题的答案。
下面的解法是设扫描线平行于y轴，从0坐标向右扫描。因为本题的所有点都是非负整数，并且数据范围不大，所以x轴并未离散化。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=2704
**************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 220;
const int mod = 9901;
struct node{
    int l, r, x;
    node(){}
    node(int a, int b, int c):l(a),r(b),x(c){}
};
//p：该段区间被被加的次数，pn：该段区间有线覆盖的长度
int mmx, lz[maxn*4], p[maxn*4], pn[maxn*4];
//mx：该段区间当前最大厚度，mxn：当前区间最大厚度的长度
int len, b[maxn], mx[maxn*4], mxn[4*maxn];
vector<node> g[50100];
int lisan(int num, int a[]);
void creat(int l, int r, int k);
void pushdown(int l, int r, int k);
void pushup(int l, int r, int k);
void Update(int l, int r, int al, int ar, int x, int k);

int main()
{
    int n, w, h, i, j, k, num;
    while(scanf("%d", &n), n)
    {
		//初始化
		memset(pn, 0, sizeof(pn));
		memset(mxn, 0, sizeof(mxn));
		memset(p, 0, sizeof(p));
		memset(lz, 0, sizeof(lz));
        scanf("%d %d", &w, &h);
        num = 0;
        for(i=0;i<n;i++)
        {
            int a1, b1, a2, b2;
            scanf("%d %d %d %d", &a1, &b1, &a2, &b2);
            b[++num] = b1; b[++num] = b2;
            g[a1].push_back(node(b1, b2, 1));
            g[a2].push_back(node(b1, b2, -1));
        }
		//离散化y坐标
        len = lisan(num+1, b);
        b[0] = 0;
        creat(1, len, 1);
        int mxx = 0, sum1 = 0, sum2 = 0;
		//x从0坐标开始，每次扫描1单位长度
        for(i=0;i<=w;i++)
        {
            if(mxx == mx[1])sum2 += mxn[1];
            else if(mxx < mx[1]) mxx = mx[1], sum2 = mxn[1];
            sum1 += pn[1];
            for(j=0;j<g[i].size();j++)
            {
                int l = lower_bound(b+1, b+1+len, g[i][j].l)-b;
                int r = lower_bound(b+1, b+1+len, g[i][j].r)-b;
                Update(1, len, l+1, r, g[i][j].x, 1);
            }
            g[i].clear();
        }
        printf("%d %d %d\n", (LL)w*h-sum1, mxx, sum2);
    }
    return 0;
}

int lisan(int num, int a[])
{
    sort(a+1, a+1+num);
    int len = 0;
    a[0] = a[1] - 1;
    for(int i=1;i<=num;i++)
        if(a[i] != a[len])a[++len] = a[i];
    return len;
}
//区间[l,r]代表长度为b[r]-b[l-1]
void creat(int l, int r, int k)
{
    p[k] = pn[k] = mx[k] = 0;
    mxn[k] = b[r]-b[l-1];
    if(l == r) return;
    int mid = (l+r)/2;
    creat(l, mid, 2*k);
    creat(mid+1, r, 2*k+1);
}

void Update(int l, int r, int al, int ar, int x, int k)
{
    if(l == al && r == ar)
    {
        mx[k] += x, lz[k] += x, p[k] += x;
        if(l != r)pushdown(l, r, k);
        pushup(l, r, k);
        return ;
    }
    pushdown(l, r, k);
    int mid = (l+r)/2;
    if(ar <= mid)Update(l, mid, al, ar, x, 2*k);
    else if(al > mid)Update(mid+1, r, al, ar, x, 2*k+1);
    else Update(l, mid, al, mid, x, 2*k),
            Update(mid+1, r, mid+1, ar, x, 2*k+1);
    pushup(l, r, k);
}

void pushdown(int l, int r, int k)
{
    if(lz[k])
    {
        int mid = (l+r)/2;
        lz[2*k] += lz[k];
        lz[2*k+1] += lz[k];
        mx[2*k] += lz[k];
        mx[2*k+1] += lz[k];
        lz[k] = 0;
    }
}

void pushup(int l, int r, int k)
{
    if(p[k])pn[k] = b[r] - b[l-1];
    else if(l == r)pn[k] = 0;
    else pn[k] = pn[2*k]+pn[2*k+1];
	//如果是叶子节点，则长度为b[r]-b[l-1]
    if(l == r){
        mxn[k] = b[r]-b[l-1];
        return;
    }
	//最大值为其左右儿子中较大的一个
    if(mx[2*k] == mx[2*k+1])
        mx[k] = mx[2*k], mxn[k] = mxn[2*k]+mxn[2*k+1];
    else if(mx[2*k] < mx[2*k+1])
        mx[k] = mx[2*k+1], mxn[k] = mxn[2*k+1];
    else
        mx[k] = mx[2*k], mxn[k] = mxn[2*k];
}