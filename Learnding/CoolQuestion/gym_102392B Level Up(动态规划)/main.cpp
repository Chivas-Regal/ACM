/**********************************************************************
动态规划

有n个任务，每个任务可以在一级时完成，需要ti的时间，能获得xi的经验，也可以在二级的时候
完成，需要ri的时间，能获得yi的经验。每个任务只能完成一次，一级经验槽为s1，二级经验槽为
s2，升级后溢出经验将继承。求过2级满经验最少需要的时间。

思路：问题的难点在于经验一级升二级时经验溢出的问题。为了考虑所有的经验溢出量，在一级
时选择的任务，需要按照x的升序进行dp，若最大的提前dp，则可能存在未考虑最后一种，就已
升级，其中的部分任务就只能留到二级时进行了。
排序后，01背包，设dp[i][j]代表一级获得i经验，二级获得j经验，对于第k个任务，分别考虑
将其在一级、二级时完成的转移。在一级时，如果溢出，则将溢出的经验加到j上即可。


题目链接：https://codeforces.com/gym/102392/problem/B
**********************************************************************************/
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
const int maxn = 520;
const int mod = 998244353;
const LL llinf = 0x3f3f3f3f3f3f3f3f;
struct node{
    int x, y, r, t;
}p[maxn];
LL dp1[maxn][maxn], dp2[maxn][maxn];
int rd();
bool cmp(node a, node b);

int main()
{
    int n, s1, s2, s3, i, j, k, p1, p2;
    LL ans = llinf, mi;
    scanf("%d %d %d", &n, &s1, &s2);
    for(i=1;i<=n;i++)
        scanf("%d %d %d %d", &p[i].x, &p[i].t, &p[i].y, &p[i].r);
    sort(p+1, p+1+n, cmp);
    memset(dp1, 0x3f, sizeof(dp1));
    memset(dp2, 0x3f, sizeof(dp2));
    dp1[0][0] = dp2[0][0] = 0;
    for(i=1;i<=n;i++){
        for(j=0;j<=s1;++j)
            for(k=0;k<=s2;++k)
                dp1[j][k] = dp2[j][k];
        for(j=0;j<=s1;j++)
            for(k=0;k<=s2;k++)
                if(dp1[j][k] != llinf){
                    int dj = j+p[i].x, dk = k;
                    if(j != s1){
                        if(dj >= s1){
                            dk = min(s2, dk+dj-s1);
                            dj = s1;
                        } 
                        dp2[dj][dk] = min(dp2[dj][dk], dp1[j][k]+p[i].t);
                    }
                    dk = min(s2, k+p[i].y);
                    dp2[j][dk] = min(dp2[j][dk], dp1[j][k]+p[i].r);
                }
    }
    if(dp2[s1][s2] >= llinf)printf("-1\n");
    else printf("%I64d\n", dp2[s1][s2]);
    return 0;
}

bool cmp(node a, node b)
{
    return a.x < b.x;
}