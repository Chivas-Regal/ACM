/************************************************************************
位运算，数论

有序列S，初始为空，进行以下操作：
1：选择三元组(a,b,c)满足a^b^c==0，且a,b,c未在S中出现过，且a,b,c字典序最小。
2：将a,b,c依次放入序列S的尾部。
3：重复第一步。
求序列S的第n个数。

思路：打表可以发现每个三元组a在一些段是连续的，依次为1~1,4~7,16~31...，
起始位置为2^(2*k)，k为非负整数，且[2^(2*k),2^(2*k+2))的所有数都分布在起始
位置在[2^(2*k),2^(2*k+1))的三元组内。
分析其中连续的几组三元组可以发现，将二进制下两位作为一组，规律如下：
a     b     c
00    00    00
01    10    11
10    11    01    
11    01    10
根据n求出其所在三元组的a，然后根据上面的关系求出b，异或后可知c，n对3取余输出即可。

题目链接：https://codeforces.com/contest/1338/problem/C
**********************************************************************/
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
const int maxn = 110000;
const int mod = 998244353;
LL d[64];
void solve(LL a, LL &b, LL &c);
 
int main()
{
    int t, i, j, k;
    LL n, a, b, c;
    for(i=0;i<29;i++)
        d[i] = 1LL<<(2*i);
    scanf("%d", &t);
    while(t--)
    {
        scanf("%I64d", &n);
        for(i=0;;i++)
            if(d[i]<=n && d[i+1]>n)break;
        a = d[i]+(n-d[i])/3;
        solve(a, b, c);
        if(n%3 == 1)printf("%I64d\n", a);
        else if(n%3 == 2)printf("%I64d\n", b);
        else printf("%I64d\n", c);
    }
    return 0;
}
 
void solve(LL a, LL &b, LL &c)
{
    b = 0;
    char str1[64], str2[64];
    for(int i=60;i>=0;i--){
        if(a&(1LL<<i))str1[i] = 1;
        else str1[i] = 0;
    }
    for(int i=59;i>=1;i-=2){
        if(str1[i] == 0 && str1[i-1] == 0)str2[i]=str2[i-1]=0;
        else if(str1[i]==0 && str1[i-1]==1)str2[i]=1,str2[i-1]=0;
        else if(str1[i]==1 && str1[i-1]==0)str2[i] = str2[i-1] = 1;
        else str2[i]=0,str2[i-1]=1;
    }
    for(int i=0;i<60;i++)
    if(str2[i])
        b |= 1LL<<i;
    c = a^b;
}