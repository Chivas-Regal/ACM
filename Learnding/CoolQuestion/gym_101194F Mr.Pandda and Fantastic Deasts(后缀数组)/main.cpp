/*****************************************
后缀数组
有n个字符串，求只在第一个字符串内出现的长度最小子串，如果有
多个长度相同，则求字典序最小的
题解：要求只求存在于第一个字符串中的最短子串，可以枚举子串的起点
确定其终点，去最短且字典序最小即可。将所有字符串拼接成一个字符串，
利用后缀数组，求出sa数组和height数组。对于第一个字符串的每个后缀，
求出其与其他字符串的每个后缀的最长公共前缀，将其长度+1，即为一个
只存在于第一个字符串的子串(对于sa[i]<=len1，求出其与左边和右边的
两个属于其他字符串的最长公共前缀，取两个中的最大值即可)。求出所有结果，
去除不合理的，取满足题意的即可，上述操作可以在O(n)内求出来，
n为所有字符长度和。
题目链接：https://codeforces.com/gym/101194
****************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<deque>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 300100;
const int mod = 1000000007;
struct node{
    int be, len;
    node(){}
    node(int a, int b):be(a),len(b){}
    bool operator <(node b)const
    {
        return be < b.be;
    }
}p[maxn];
char str[maxn], ans[maxn], str1[maxn];
int N, M, tmp[2*maxn], sa[maxn], tp[maxn], rk[maxn], hei[maxn];
int b[maxn], c[maxn], d[maxn];
void solve(int n);
void SA(int n);
void gethei();
void QSORT();
void debug();

int main()
{
    int t, n, i, j, k, len, up, alen;
    scanf("%d", &t);
    for(int z=1;z<=t;z++)
    {
        up = 1;
        ans[0] = 0;
        alen = INF;
        scanf("%d", &n);
        for(i=1;i<=n;i++)
        {
            scanf(" %s", str+up);
            p[i].be = up, p[i].len = strlen(str+up);
            up += p[i].len+1;
            p[i].len += p[i].be;
            str[up-1] = '#';
        }
        for(i=0;i<=2*up+19;i++)tmp[i] = 0, c[i] = d[i] = 0;
        len = up;
        //求sa和height数组
        SA(up);
        gethei();
        solve(n);
        //对于每个后缀，求左右两边与其他字符串后缀的最长的那个
        for(int i=1;i<=N;i++)
        {
            if(b[i] == 1)
            {
                int mx = max(c[i], d[i]);
                if(sa[i]+mx < p[1].len)
                {
                    //printf("%d %d\n", sa[i], mx);
                    if(mx < alen)
                    {
                        strncpy(ans, str+sa[i], mx+1);
                        alen = mx;
                        ans[mx+1] = 0;
                    }
                }
            }
        }
        if(i == N+1 || !ans[0])
            printf("Case #%d: Impossible\n", z);
        else
            printf("Case #%d: %s\n", z, ans);
    }
    return 0;
}
//桶排序，确定当前的SA
void QSORT()
{
    for(int i=0;i<=M;i++)tmp[i] = 0;
    for(int i=1;i<=N;i++)tmp[rk[i]]++;
    for(int i=1;i<=M;i++)tmp[i] += tmp[i-1];
    for(int i=N;i>=1;i--)sa[tmp[rk[tp[i]]]--] = tp[i];
}

void SA(int n)
{
    N = n-1, M = 200;
    for(int i=1;i<=N;i++)
        rk[i]=str[i], tp[i] = i;
    QSORT();
    for(int w=1, p=0;p<N;w<<=1,M=p)
    {
        p = 0;
        for(int i=1;i<=w;i++)tp[++p] = N-w+i;
        for(int i=1;i<=N;i++)if(sa[i]>w)tp[++p] = sa[i]-w;
        QSORT();
        swap(rk, tp);
        rk[sa[1]] = p = 1;
        for(int i=2;i<=N;i++)
            rk[sa[i]]=(tp[sa[i]] == tp[sa[i-1]] && tp[sa[i]+w] == tp[sa[i-1]+w])?p:++p;
    }
}

void gethei()
{
    int j, k = 0;
    for(int i = 1; i <= N; i++) {
        if(k) k--;
        int j = sa[rk[i] - 1];
        while(str[i + k] == str[j + k]) k++;
        hei[rk[i]] = k;
    }
}
//求第一个字符串的每个后缀，与其他其他字符串的最长公共前缀
void solve(int n)
{
    int i, j, k;
    //求出每个sa[i]属于第几个字符串
    for(i=1;i<=N;i++)
        b[i] = upper_bound(p+1, p+1+n, node(sa[i], 0))-p-1;
    //求出属于第一个字符串的后缀与其左边的属于其他字符串的后缀最长的公共前缀
    for(i=1;i<=N;i++)
    {
        if(b[i]!=1 && i+1<=N && b[i+1] == 1)
        {
            int mi = p[b[i]].len-sa[i];
            for(j=i+1;j<=N&&b[j]==1;j++)
            {
                mi = min(mi, hei[j]);
                c[j] = mi;
            }
            i = j-1;
        }
    }
    //求出属于第一个字符串的后缀与其右边的属于其他字符串的后缀最长的公共前缀
    for(i=N;i>=1;i--)
    {
        if(b[i]!=1 && i-1>=0 && b[i-1] == 1)
        {
            int mi = min(hei[i],p[b[i]].len-sa[i]);
            for(j=i-1;j>=1&&b[j]==1;j--)
            {
                d[j] = mi;
                mi = min(mi, hei[j]);
            }
            i = j+1;
        }
    }
}