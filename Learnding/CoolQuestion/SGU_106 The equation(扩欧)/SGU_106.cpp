/******************************************************************************
扩展欧几里得

已知ax+by+c=0，给出范围[x1,x2],[y1,y2]。求有多少点对(x,y)，x,y为整数，x1<=x<=x2,y1<=y<=y2，
且点(x,y)在直线ax+by+c=0上。

思路：将式子变为ax+by=-c,利用扩欧求出ax+by=gcd(a,b)的一组解(x0,y0), d = gcd(a,b)，若-c%d!=0，
则不存在满足要求的(x,y)；若满足，则求出通解，一个解为(x1,y1)，x1=x0*(-c/d), y1=y0*(-c/d).
则通解为x = x1+b/d*k, y = y1-a/d*k。k未知，结合范围限制求出k的取值范围，两轴
方向的公共部分即为k的可行值。解  x1<= x <= x2 , y1<= y <= y2即可。

题目链接：http://codeforces.com/problemsets/acmsguru/problem/99999/106
***********************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-7
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 120;
const int mod = 998244353;
int exgcd(int a, int b, LL &x, LL &y);

int main()
{
    int a, b, c;
    LL ans=0, x, y, xa, xb, ya, yb, i;
    scanf("%d %d %d", &a, &b, &c);
    c = -c;
    scanf("%I64d %I64d %I64d %I64d", &xa, &xb, &ya, &yb);
    if(a == 0 && b == 0){
        if(c == 0)ans = (yb-ya+1)*(xb-xa+1);
    }
    else if(a == 0){
        if(c%b == 0 && c/b>=ya && c/b<=yb)ans = xb-xa+1;
    }
    else if(b == 0){
        if(c%a == 0 && c/a>=xa && c/a<=xb)ans = yb-ya+1;
    }else{
        int d = exgcd(a, b, x, y);
        if(c%d == 0){
            x *= c/d, y *= c/d;
            LL tx = b/d, ty = -a/d;
            if(tx<0){
                tx*=-1, x*=-1;
                swap(xa, xb);
                xa *= -1, xb*=-1;
            }
            if(ty<0){
                ty*=-1, y*=-1;
                swap(ya, yb);
                ya*=-1, yb*=-1;
            }
            LL mi, mx;
            if((xa-x)%tx == 0 || xa-x < 0)mi = (xa-x)/tx;
            else mi = (xa-x)/tx+1;
            if((ya-y)%ty == 0 || ya-y < 0)mi = max(mi, (ya-y)/ty);
            else mi = max(mi, (ya-y)/ty+1);
            if((xb-x)%tx == 0 || xb-x >= 0)mx = (xb-x)/tx;
            else mx = (xb-x)/tx-1;
            if((yb-y)%ty == 0 || yb-y >= 0)mx = min(mx, (yb-y)/ty);
            else mx = min(mx, (yb-y)/ty-1);
            ans = max(0LL, mx-mi+1);
        }   
    }
    printf("%I64d\n", ans);
    return 0;
}

int exgcd(int a, int b, LL &x, LL &y)
{
    if(b == 0){
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a%b, y, x);
    y -= x*(a/b);
    return d;
}