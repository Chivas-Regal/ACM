/**********************************************************************
数论

选定区间[a,b](0<a,b<=50000000)，等概率从中选取一个数x，设x二进制长度为len，会从len个二进制
位中随机选一位。求最后选中的是'1'的概率。

思路：设len(x)为x的二进制长度，one(x)为x二进制下'1'的个数，那计算'1'的个数和除以长度和
不就行了？结果为
1/(b-a+1)*(one(a)/len(a)+one(a+1)/len(a+1)+...+one(b)/len(b+1))。
因为作为分母的len(x)是可能不相同的，所以不能简单求和。可以将len(x)相同的数放在一起处理，
然后求分子的和即可，len(x)最多有logn个不同的值，所以最多求logn次。
接下来就是快速求区间内的数，二进制位为‘1’的数量。设求小于等于x的所有数二进制位上‘1’的数量
和。分别考虑每一个为1，考虑第i(从0开始计数)位时，规律为2^i个数第i位为0,2^i个数第i位为1，
2^i个数第i位为0,2^i个数第i位为1....求出有多少个2^(i+1)，就有多少个2^i个数第i位为1，
即 ans += x/(2^(i+1)) * 2^i,然后在处理下边界。依次考虑每一位即可。

题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827367678
**************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 2000100;
const int mod = 1000000007;
double solve(int a, int b);
LL getone(LL x);

int main()
{
    int t, a, b;
    LL up, dn;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &a, &b);
        printf("%.6f\n", solve(a, b));
    }
    return 0;
}

double solve(int a, int b)
{
    int i, j, k, l, r, num = b-a+1;
    double p = 0;
    for(i=0;i<28;i++)
    {
        j = 1<<i;
        l = max(a, j);
        r = min(j*2-1, b);
        if(l<=r)
        {
            LL len = i+1;
            LL num = getone(r)-getone(l-1);
            p += (num*1.0)/len;
        }
    }
    return p/num;
}
//求<=x的所有数二进制位为‘1’的数量
LL getone(LL x)
{
    LL sum = 0, i, j;
    for(i=0;i<30;i++)
    {
        j = 1LL<<(i+1);
        sum += (x/j) * (j/2);
        if(x%j >= j/2)
            sum += x%j - j/2+1;
    }
    return sum;
}
