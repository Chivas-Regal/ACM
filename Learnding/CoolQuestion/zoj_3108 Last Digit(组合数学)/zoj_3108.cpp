/*********************************************************************************
组合数学

一个字符串，求所有排列，本质不同的串的数量，输出最后一位非0的数即可。

思路：设字符串长度为len，'a'~'z'出现的次数分别为a[0]~a[25]，显然本质不同的字符串的数量
为len!/(a[0]!*a[1]!*....*a[25]!)。显然len太大，不能直接求，将其分解，求出每个质因数的数量。
打表出质因数，然后求出每个质因数的数量即可。最后一位非0，需要将2出现的次数减去5出现的次数。

题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827367483
**************************************************************************/
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
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 1000100;
const int mod = 1000000000;
int top, a[32], c[maxn], p[100000];
char str[maxn];
void init();
int getnum(int n, int s);

int main()
{
    init();
    int i, j, k, len;
    while(~scanf("%s", str))
    {
        len = strlen(str);
        memset(a, 0, sizeof(a));
        memset(c, 0, (len+10) * sizeof(c[0]));
        for(i=0;i<len;i++)
            a[str[i]-'a']++;
        for(i=0;i<top && p[i]<=len;i++)
            c[p[i]] += getnum(len, p[i]);
        for(i=0;i<26;i++)
            for(j=0;j<top && p[j]<=a[i];j++)
                c[p[j]] -= getnum(a[i], p[j]);
        int x = 1;
        c[2] -= c[5];c[5] = 0;
        for(i=2;i<=len;i++)
            if(c[i]){
                j = c[i]%4+4;
                while(j--)
                    x = x*i%10;
            }
        printf("%d\n",x);
        
    }
    return 0;
}

void init()
{
    top = 0;
    int n= maxn-90, i, j;
    for(i=2;i<=n;i++)
        if(!c[i]){
            p[top++] = i;
            for(j=i;j<=n;j+=i)
                c[j] = 1;
        }
}

int getnum(int n, int s)
{
    int num = 0;
    while(n){
        num += n / s;
        n /= s;
    }
    return num;
}