/************************************************************************
二分图匹配、最小点覆盖

有一个n*m的区域，每一个格子是草地或者泥坑，现在有宽度为1，长度任意的木板。木板可以覆盖
泥坑，但不能覆盖草地，求最少需要多少块木板能覆盖所有泥坑。

思路：因为泥坑可以被多次覆盖，当木板横放或者竖放时，木板的长应尽量的长，这样才能覆盖更多的
泥坑。对于泥坑而言，每个泥坑至少需要被横放或竖放的木板覆盖一次。所以可以将横放的木板和竖放
的木板看着二分图的两部分(一块木板代表一个点)，将每个泥坑作为一条边，然后求二分图的最小点覆盖。
1.建图：只考虑横放，求每个泥坑属于哪块木板，记id1,只考虑竖放，求每个泥坑属于哪块木板，记id2
对于泥坑，连id1->id2。
2.求二分图最小点覆盖，二分图最小点匹配=二分图最大匹配。匈牙利或者网络流求最大匹配即可。

题目链接：http://poj.org/problem?id=2226
********************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<set>
#include<queue>
#include<stack>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 2100;
const int mod = 1000000007;
char str[56][56];
int n, m, xnum, ynum, id1[56][56], id2[56][56];
int vis[maxn], py[maxn];
vector<int> g[maxn];
void getmap(int n, int m);
int xiongya();
bool match(int u);

int main()
{
    int n, m, i, j;
    scanf("%d %d", &n, &m);
    for(i=0;i<n;i++)
        scanf(" %s", str[i]);
    getmap(n, m);
    int ans = xiongya();
    printf("%d\n", ans);
    return 0;
}
//匈牙利算法，求二分图最大匹配
int xiongya()
{
    int ans = 0, i, j;
    memset(py, -1, sizeof(py));
    for(i=1;i<=xnum;i++)
    {
        memset(vis, 0, sizeof(vis));
        if(match(i))ans++;
    }
    return ans;
}

bool match(int u)
{
    for(int i=0;i<g[u].size();i++)
        if(!vis[g[u][i]])
        {
            vis[g[u][i]] = 1;
            if(py[g[u][i]] == -1 || match(py[g[u][i]]))
            {
                py[g[u][i]] = u;
                return true;
            }
        }
    return false;
}
//建图
void getmap(int n, int m)
{
    int i, j, k;
    xnum = ynum = 0;
    memset(id1, -1, sizeof(id1));
    memset(id2, -1, sizeof(id2));
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            if(str[i][j] == '*' && id1[i][j] == -1)
            {
                id1[i][j] = ++xnum;
                k = j+1;
                while(k<m && str[i][k] == '*')
                {
                    id1[i][k] = id1[i][j];
                    k++;
                }
            }
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            if(str[i][j] == '*' && id2[i][j] == -1)
            {
                id2[i][j] = ++ynum;
                k = i+1;
                while(k<n && str[k][j] == '*')
                {
                    id2[k][j] = id2[i][j];
                    k++;
                }
            }
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            if(str[i][j] == '*')
                g[id1[i][j]].push_back(id2[i][j]);
    
}