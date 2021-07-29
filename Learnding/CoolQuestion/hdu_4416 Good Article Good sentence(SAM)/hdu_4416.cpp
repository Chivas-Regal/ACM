/***************************************************************
后缀自动机

一个串S和n个串Ti，求S有多少个不同子串只在S中出现未在n个Ti中出现。

思路：首先对n个串Ti构造自动机，每个不同的串构造是将last=0即可。n个
串构造完成后，求不同子串的数量。然后将串S也加入自动机中，再求一遍不同
子串的数量，两者的差即为结果。
PS：这题有点卡空间。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=4416
*****************************************************************/
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
const int mod = 3000001;
struct node{
    int len, link, nex[26];
}st[maxn*3];
int tot, last;
char str1[maxn*2], str2[maxn*2];
void sam(int ch);
void init();
LL dfs();

int main()
{
    int t, n, i, j;
    scanf("%d", &t);
    for(int id=1;id<=t;id++)
    {
        scanf("%d %s", &n, str1);
        init();
        while(n--){
            scanf(" %s", str2);
            last = 0;
            for(i=0;str2[i];i++)
                sam(str2[i]-'a');
        }
        LL ans = dfs();
        last = 0;
        for(i=0;str1[i];i++)
            sam(str1[i]-'a');
        ans = dfs() - ans;
        printf("Case %d: %lld\n", id, ans);
    }
    return 0;
}

void init()
{
    st[0].len = 0;
    st[0].link = -1;
    memset(st[0].nex, -1, sizeof(st[0].nex));
    tot = 1;
}

void sam(int ch)
{
    int p, q, cur = tot++;
    st[cur].len = st[last].len+1;
    memset(st[cur].nex, -1, sizeof(st[cur].nex));
    for(p=last;p!=-1 && st[p].nex[ch] == -1;p=st[p].link)
        st[p].nex[ch] = cur;
    if(p == -1)
        st[cur].link = 0;
    else{
        q = st[p].nex[ch];
        if(st[p].len+1 == st[q].len)
            st[cur].link = q;
        else{
            int clo = tot++;
            st[clo] = st[q];
            st[clo].len = st[p].len+1;
            for(;p!=-1 && st[p].nex[ch] == q;p=st[p].link)
                st[p].nex[ch] = clo;
            st[cur].link = st[q].link = clo;
        }
    }
    last = cur;
}

LL dfs()
{
    LL ans = 0;
    for(int i=1;i<tot;i++)ans += st[i].len - st[st[i].link].len;
    return ans;
}