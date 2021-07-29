/********************************************************************
后缀自动机

由n个小写英文字符组成的字符串S，求S有多少个不同的子串不重叠的出现过两次及以上。

思路：要求出现次数大于等于两次，且不重叠的子串数量。可以考虑求出每个
首次出现的位置lpos，最后一次出现的位置rpos。设子串长度为len，
若lpos+len<=rpos,则该子串满足条件。

对于字符串，构造出后缀自动机，同时维护每个状态的lpos和rpos。其初始值为点
创建时的位置。构造完成后，利用parent树更新lpos和rpos。

后缀自动机中，一个节点u所代表的字符串长度为[st[st[u].link].len, st[u].len],
同时多次出现不重叠，则要求其长度为[1,rpos-lpos]，求两段区间的公共部分长度
即为结果。累加即可。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=3518
********************************************************************/
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
const int maxn = 100100;
const int mod = 998474321;
struct node{
    int len, mx, mi, link, nex[28];
}st[maxn*2];
int last, cnt, tmp[maxn*2], rk[maxn*2];
char str[maxn];
void sam(int ch, int pos);
void init();
void QSORT(int tot);

int main()
{
    int n, c, i, j, k;
    while(scanf(" %s", str))
    {
        if(str[0] == '#')break;
        init();
        for(i=0;str[i];i++)
            sam(str[i]-'a', i+1);
        QSORT(cnt);
        for(i=0;i<cnt;i++){
            j = rk[i];
            if(st[j].link != -1){
                st[st[j].link].mx = max(st[st[j].link].mx, st[j].mx);
                st[st[j].link].mi = min(st[st[j].link].mi, st[j].mi);
            }
                
        }
        int ans = 0;
        for(i=0;i<cnt;i++)
        if(st[i].mx-st[i].mi > st[st[i].link].len)
            ans += min(st[i].len, st[i].mx-st[i].mi)-st[st[i].link].len;
        printf("%d\n", ans);
    }    
    return 0;
}

void init()
{
    st[0].link = -1;
    st[0].len = 0;
    memset(st[0].nex, -1, sizeof(st[0].nex));
    last = 0;
    cnt = 1;
}

void sam(int ch, int pos)
{
    int cur = cnt++, p, q;
    st[cur].len =  st[last].len+1;
    st[cur].mx = st[cur].mi = pos;
    memset(st[cur].nex, -1, sizeof(st[cur].nex));
    for(p=last;p!=-1 && st[p].nex[ch]==-1;p=st[p].link)
        st[p].nex[ch] = cur;
    if(p == -1)
        st[cur].link = 0;
    else{
        q = st[p].nex[ch];
        if(st[p].len+1 == st[q].len)
            st[cur].link = q;
        else{
            int clo = cnt++;
            st[clo] = st[q];
            st[clo].len =   st[p].len+1;
            st[clo].mx = st[clo].mi = pos;
            for(;p!=-1 && st[p].nex[ch] == q;p=st[p].link)
                st[p].nex[ch] = clo;
            st[cur].link = st[q].link = clo;
        }
    }
    last = cur;
}

void QSORT(int tot)
{
    for(int i=0;i<=tot;i++)tmp[i] = 0;
    for(int i=0;i<tot;i++)tmp[st[i].len]++;
    for(int i=1;i<=tot;i++)tmp[i] += tmp[i-1];
    for(int i=0;i<tot;i++)
        rk[tot-(tmp[st[i].len]--)] = i; 
}