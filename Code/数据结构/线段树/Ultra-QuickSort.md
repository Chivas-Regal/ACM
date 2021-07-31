
# 🔗
http://poj.org/problem?id=2299

# 💡


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  

```cpp
#include                                            <algorithm>
#include                                             <iostream>
#include                                              <cstring>
#include                                               <string>
#include                                               <vector>
#include                                               <cstdio>
#include                                                <stack>
#include                                                <queue>
#include                                                <cmath>
#include                                                  <map>
#include                                                  <set>
#define G                                                  10.0
#define LNF                                                1e18
#define eps                                                1e-6
#define mod                                             1e9 + 7
#define ll                                            long long
#define INF                                          0x7FFFFFFF
#define PI                                           acos(-1.0)
#define pb(x)                                      push_back(x)
#define SP                                      system("pause")
#define mm(a, b)                        memset(a, b, sizeof(a))
#define fir(i, a, n)               for (int i = a; i <= n; i++)
#define rif(i, a, n)               for (int i = a; i >= n; i--)
#define each_cass(cass)  for (scanf("%d", &cass); cass; cass--)

using namespace std;

const int maxn = 5e5 + 15;
struct SegTree{
    int lazy;
    int val;
} SegTree[maxn << 2];
struct Num{
    int id;
    int val;
    friend bool operator<(Num a,Num b){
        return a.val < b.val;
    }   
} Num[maxn];
int A[maxn];
int n;

void Disc();
void PushUp(int rt);
void PushDown(int l, int r, int rt);
void BuildTree(int l, int r, int rt);
void UpDate(int a, int b, int c, int l, int r, int rt);
ll Query(int a, int b, int l, int r, int rt);


int main(){
    while(scanf("%lld",&n)==1,n){
        for (int i = 1; i <= n; i++)
            scanf("%lld", &Num[i].val), Num[i].id = i;
        Disc();
        ll cnt = 0;
        BuildTree(1, n, 1);
        for (int i = 1; i <= n; i++){
            UpDate(A[i], A[i], 1, 1, n, 1);
            cnt += Query(A[i]+1, n, 1, n, 1);
        }
        printf("%lld\n", cnt);
    }
    return 0;
}

void Disc(){
    int cnt = 0;
    sort(Num + 1, Num + n + 1);
    A[Num[1].id] = 1;
    cnt=1;
    for (int i = 2; i <= n; i++){
        if(Num[i].val==Num[i-1].val)
            A[Num[i].id] = cnt;
        else
            A[Num[i].id] = ++cnt;
    }
}
void PushUp(int rt)
{
    SegTree[rt].val = SegTree[rt << 1].val + SegTree[rt << 1 | 1].val;
}
void PushDown(int l, int r, int rt)
{
    if (!SegTree[rt].lazy)
        return;
    int mid = (l + r) >> 1;
    SegTree[rt << 1].val += SegTree[rt].lazy * (mid - l + 1);
    SegTree[rt << 1 | 1].val += SegTree[rt].lazy * (r - mid);
    SegTree[rt << 1].lazy += SegTree[rt].lazy;
    SegTree[rt << 1 | 1].lazy += SegTree[rt].lazy;
    SegTree[rt].lazy = 0;
}
void BuildTree(int l, int r, int rt)
{
    SegTree[rt].lazy = 0;
    if (l == r)
    {
        SegTree[rt].val = 0;
        return;
    }
    int mid = (l + r) >> 1;
    BuildTree(l, mid, rt << 1);
    BuildTree(mid + 1, r, rt << 1 | 1);
    PushUp(rt);
}
void UpDate(int a, int b, int c, int l, int r, int rt)
{
    if (a > r || b < l)
        return;
    if (a <= l && b >= r)
    {
        SegTree[rt].val += c * (r - l + 1);
        SegTree[rt].lazy += c;
        return;
    }
    PushDown(l, r, rt);
    int mid = (l + r) >> 1;
    UpDate(a, b, c, l, mid, rt << 1);
    UpDate(a, b, c, mid + 1, r, rt << 1 | 1);
    PushUp(rt);
}
ll Query(int a, int b, int l, int r, int rt)
{
    if (a > r || b < l)
        return 0;
    if (a <= l && b >= r)
        return SegTree[rt].val;
    int mid = (l + r) >> 1;
    return Query(a, b, l, mid, rt << 1) + Query(a, b, mid + 1, r, rt << 1 | 1);
}     
```
