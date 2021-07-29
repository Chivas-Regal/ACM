/*************************************************************************************
Manachar 

字符串S，设a为S的前缀，b为S的后缀，t =a+b(a,b可为空)，|t|<=|S| && t为回文串。求最长的t。

思路：len=|S|,答案一定是选择字符串原本的一个回文串[nl,nr]。若
将nr作为前缀的最后一个字符，alen=nl, 则需要满足[0,nl)与[len-alen, len-1]连接为回文串(可通过
预处理判断)，同时nr<len-alen(保证字符未被重复使用)。满足条件则字符串为[0,nr]+[len-alen,len-1];
将al作为后缀的第一个字符，blen=len-1-nr，则需要满足[0,blen)与[len-blen, len-1]连接为回文串，
同时blen<=n1。满足条件字符串为[0,blen)+[nl, len-1]。
遍历manachar后的数组，求最大即可。

题目链接：http://codeforces.com/problemset/problem/1326/D2
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
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 1000100;
const int mod = 998244353;
char s[maxn], str[maxn*2];
int len, len2, p[maxn*2], a[maxn*2], b[maxn];
void init(char s[]);

int main()
{
    int t, n, i, j, mx, id, alen, l, r, al, ar;
    scanf("%d", &t);
    while(t--)
    {
        scanf(" %s", s);
        init(s);
        for(i=0;i<=len;i++)
            b[i] = 0;
        alen = 1, l = 0, r = len;
        mx = 0;
        al = 0, ar = len-1;
        while(al<ar && s[al] == s[ar]){
            b[al] = b[ar] = 1;
            al++, ar--;
        }
        for(i=1;i<len2;i++)
        {
            p[i] = mx>i?min(mx-i, p[2*id-i]):1;
            while(str[i-p[i]] == str[i+p[i]])
                p[i]++;
            if(i+p[i]>mx){
                id = i;
                mx = i+p[i];
            }
            int nl, nr, x;
            nl = a[i-p[i]]+1;
            nr = a[i+p[i]]-1;
            if(nr<nl)continue;
            if(nl == 0 && nr == len-1){
                alen = len;
                l = len-1, r = len;break;
            }
            if((nl == 0 || b[nl-1] == 1) && nr+nl<len && nr-nl+1+2*nl>alen){
                alen = nr-nl+1+2*nl;
                l = nr, r = len-nl;
            }
            if((nr == len-1 || b[nr+1] == 1) && len-1-nr<=nl && nr-nl+1+2*(len-1-nr) > alen){
                alen = nr-nl+1+2*(len-1-nr);
                r = nl, l = len-1-nr-1;
            }
                
        }
        for(i=0;i<=l;i++)
            printf("%c", s[i]);
        for(i=r;i<len;i++)
            printf("%c", s[i]);
        printf("\n");
    }
    return 0;
}

void init(char s[])
{
    str[0]=')';
    str[1]='*';
    a[0] = -1;
    int i, j=2;
    for(i=0;s[i];i++){
        str[j] = s[i];
        a[j] = i;
        str[j+1] = '*';
        j += 2; 
    }
    len = i;
    len2 = j;
    str[j] = 0;
    a[j] = len;
}