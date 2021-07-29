/********************************************************************
博弈论

题目：二维平面上共有n个点，初始在1号点，第一次移动可以任意移动，后续移动每次移动
的距离需要大于上次移动的距离，点不能重复经过。A和B进行博弈，A先移动，是否有必胜策略。

思路：对于所有的边，最长的边所在的点，若是走到其中一点，则对方走一条最长边就赢了。
将最长边相关的点"删去"。则变为了规模更小的子问题。
将同一批次删除的点作为一组，若1号点所在的那组有超过一个点(最后只剩初始点)，
则A必胜，否则必败。
(A先向本组其它点移动，则B必然向其他组移动，A下一步向组内其余点移动即可)

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=6850
*********************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#include<ctime>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-8
   
using namespace std;
typedef long long LL;  
typedef pair<int, int> P;
const int maxn = 2020;
const int mod = 998244353;
struct node{
    int x, y;
    LL dis;
}p[maxn*maxn];
int x[maxn], y[maxn], vis[maxn], a[maxn*maxn];
bool cmp(node a, node b);

int main()
{
    int t, n, m, i, j, k, cnt, sum, sig, num;
    scanf("%d", &t);
    while(t--)
    {
        cnt = sig = 0;
        scanf("%d", &n);
        for(i=1;i<=n;i++){
            scanf("%d %d", &x[i], &y[i]);
            vis[i] = 0;
        }
        for(i=1;i<=n;i++)
            for(j=i+1;j<=n;j++){
                p[cnt].x = i, p[cnt].y = j;
                p[cnt].dis = 1LL*(x[i]-x[j])*(x[i]-x[j])+1LL*(y[i]-y[j])*(y[i]-y[j]);
                a[cnt] = 0;
                cnt++;
            }
        sort(p, p+cnt, cmp);
        i = 0, sum = n;
        while(i<cnt)
        {
            num = 0;
            for(j=i;j<cnt && p[j].dis == p[i].dis;j++){
                if(vis[p[j].x] == 1 || vis[p[j].y] == 1)continue;
                a[j] = 1;
            }
            for(j=i;j<cnt && p[j].dis == p[i].dis;j++){
                if(!a[j])continue;
                num += 2 - vis[p[j].x] - vis[p[j].y];
                vis[p[j].x] = vis[p[j].y] = 1;
            }
            i = j;
            if(vis[1] && sum>1)sig = 1;
            sum -= num;
        }
        if(!sig)printf("NO\n");
        else printf("YES\n");
    }    
    return 0;
}

bool cmp(node a, node b)
{
    return a.dis > b.dis;
}