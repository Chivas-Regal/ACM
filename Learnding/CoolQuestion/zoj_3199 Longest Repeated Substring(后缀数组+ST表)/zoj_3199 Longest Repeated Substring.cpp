/***********************************************************************
后缀数组+ST表

题意：定义连续重复子串为原串的一个子串，在该子串的后面，再次出现这个子串
(两个子串相邻，无重叠)，求最长的连续重复子串。

思路：首先利用后缀数组求出字典序相邻的两个后缀的最大公共前缀。即Height数组。

考虑从大到小枚举最大连续重复子串的长度。设最终结果为len，则s[1],s[len+1],s[1+2*len]...
必然有一个元素属于目标子串。因为其在后面重复，所以可以求后缀s[1+k*len]与s[1+(k+1)*len]
的最长公共前缀，长度为slen。因为s[1+(k+1)*len]也属于目标子串的重复串，所以len是两串已经
求出的公共部分的长度，则只需要在位置1+k*len之前在匹配len-slen个字符即可。
再求后缀s[1+k*len-(len-slen)]与s[1+(k+1)*len-(len-slen)]的最长公共前缀即可。若LCP等于
len，则说明存在目标子串长度为len，输出即可。

求任意两后缀的LCP，可以通过Height数组和ST表求出。


题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827367823
**************************************************************/
#include<cstdio>
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
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100010;
const int mod = 998244353;
int N, M, rk[maxn], tmp[maxn], tp[maxn], sa[maxn], heg[20][maxn];
char s1[maxn];
void init();
int solve();
void QSORT();
void GetHeight();
void binary_sa();
int getmi(int l, int r);

int main()
{
    int T, n, m, i, j, k;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s", s1+1);
        binary_sa();
        GetHeight();
        init();
        printf("%d\n", solve());
    }
    return 0;
}

int solve()
{
    for(int i=N/2;i>=1;i--){
        for(int j=1;j+i<=N;j+=i){
            int len = getmi(rk[j], rk[j+i]);
            int k = i-len;
            if(j-k>=0){
                len = getmi(rk[j-k],rk[j+i-k]);
                if(len == i)return i;
            }
        }
    }
    return 0;
}

int getmi(int l, int r)
{
    if(l>r)swap(l, r);
    l++;
    int k = log(r-l+1)/log(2.0);
    return min(heg[k][l], heg[k][r-(1<<k)+1]);
}

void init()
{
    for(int j=1;j<17;j++)
        for(int i=0;i+(1<<j)-1<=N;++i)
            heg[j][i] = min(heg[j-1][i], heg[j-1][i+(1<<j)]);
}

void binary_sa()
{
    N = strlen(s1+1);
    M = 200;
    for(int i=1;i<=N;i++)rk[i] = s1[i], tp[i] = i;
    QSORT();
    for(int w=1,q=0;q<N;w<<=1,M=q){
        q = 0;
        for(int i=1;i<=w;i++)tp[++q] = N-w+i;
        for(int i=1;i<=N;i++)if(sa[i]>w)tp[++q] = sa[i]-w;
        QSORT();
        memcpy(tp, rk, sizeof(tp));
        rk[sa[1]] = q = 1;
        for(int i=2;i<=N;i++)
            rk[sa[i]] = (tp[sa[i]] == tp[sa[i-1]]&&tp[sa[i]+w]==tp[sa[i-1]+w])?q:++q;
    }
}

void QSORT()
{
    for(int i=0;i<=M;i++)tmp[i] = 0;
    for(int i=1;i<=N;i++)tmp[rk[i]]++;
    for(int i=1;i<=M;i++)tmp[i] += tmp[i-1];
    for(int i=N;i>=1;i--)sa[tmp[rk[tp[i]]]--] = tp[i];
}

void GetHeight()
{
    int j, k = 0;
    heg[0][0] = 0;
    for(int i=1;i<=N;i++){
        if(k)k--;
        int j = sa[rk[i]-1];
        while(s1[i+k] == s1[j+k])k++;
        heg[0][rk[i]] = k;
    }
}