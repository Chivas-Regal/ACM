/*******************************************************************************
欧拉路径

一个n*m的图，每个点有一个数字a[i][j]，还有一个字母，为'u','d','l','r'中的一个，分别代表
想上、下、左、右移动a[i][j]步的位置，是否存在走过所有点的方案。

思路：
一：欧拉路径，本身是哈密顿路径，但本题图特殊，可以作为有向图欧拉路径的判定：
    满足有向图基图连通，最多只有一对点满足，一点出度比入度大1，另一点入度比出度大1，其余点
    入度等于出度。
二：动态规划。dp[i][j]代表从i,j出发，最能到达的点数，然后DFS，维护栈，将点放入栈中，直到
    再次访问到栈内的点， 或者该点之前已更新、该点越界。再更改栈中点的信息即可。

题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827370522
******************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<map>
#include<vector>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 100010;
const int mod = 1000000000;
int in[maxn], out[maxn], a[maxn];
vector<char> g[maxn];
int Find(int x);

int main()
{
    int t, n, m, i, j, k, num, sig1, sig2;
    char ch;
    scanf("%d", &t);
    while(t--)
    {
        num = sig1 = sig2 = 0;
        scanf("%d %d", &n, &m);
        for(i=0;i<=n*m;i++){
            g[i].clear();
            a[i] = i;
            in[i] = out[i] = 0;
        }
        for(i=0;i<n;i++)
            for(j=0;j<m;j++){
                scanf(" %c", &ch);
                g[i].push_back(ch);
            }
        for(i=0;i<n;i++)
            for(j=0;j<m;j++){
                scanf("%d", &k);
                int nx, ny;
                if(g[i][j] == 'r')nx = i, ny = j+k;
                else if(g[i][j] == 'l')nx = i, ny = j-k;
                else if(g[i][j] == 'u')nx = i-k, ny = j;
                else nx = i+k, ny = j;
                if(nx>=0 && nx<n && ny>=0 && ny<m)
                {
                    int id1 = i*m+j, id2 = nx*m+ny, x=Find(id1), y = Find(id2);
                    in[id2]++, out[id1]++;
                    if(x != y){
                        a[x] = y;
                        num++;
                    }
                }
            }
        for(i=0;i<n*m;i++)
            if(in[i]>out[i])sig1 += in[i]-out[i];
            else sig2 += out[i]-in[i];
        if(num == n*m-1 && sig1<=1 && sig2<=1)printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

int Find(int x)
{
    return a[x]=x==a[x]?x:Find(a[x]);
}
//动态规划
/*
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<map>
#include<vector>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 100010;
const int mod = 1000000000;
int top, n, m;
P st[maxn];
vector<int> a[maxn], vis[maxn], dp[maxn], in[maxn];
vector<char> g[maxn];
void init(int n);
void dfs(int x, int y, int tim);

int main()
{
    int t, i, j, k;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &m);
        init(n);
        char ch;
        for(i=0;i<n;i++)
            for(j=0;j<m;j++){
                scanf(" %c", &ch);
                g[i].push_back(ch);
                dp[i].push_back(-1);
                vis[i].push_back(0);
                in[i].push_back(0);
            }
        for(i=0;i<n;i++)
            for(j=0;j<m;j++){
                scanf("%d", &k);
                a[i].push_back(k);
            }
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                if(vis[i][j] == 0)
                {
                    in[i][j] = 1;
                    top = 0;
                    st[++top] = P(i, j);
                    dfs(i, j, 1);
                }
        int mx = 0;
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                mx = max(mx, dp[i][j]);
        if(mx == n*m)printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

void init(int n)
{
    for(int i=0;i<n;i++)
    {
        g[i].clear();
        a[i].clear();
        dp[i].clear();
        vis[i].clear();
        in[i].clear();
    }
}


void dfs(int x, int y, int tim)
{
    in[x][y] = 1;
    vis[x][y] = tim;
    int nx, ny, sig, up;
    if(g[x][y] == 'r')nx = x, ny = y+a[x][y];
    else if(g[x][y] == 'l')nx = x, ny = y-a[x][y];
    else if(g[x][y] == 'u')nx = x-a[x][y], ny = y;
    else nx = x+a[x][y], ny = y;
    if(nx>=0 && nx<n && ny>=0 && ny<m){
        if(vis[nx][ny] && in[nx][ny])sig = 1, up = tim+1-vis[nx][ny];
        else if(vis[nx][ny])sig = 0, up = dp[nx][ny]+1;
        else{
            st[++top] = P(nx,ny);
            dfs(nx, ny, tim+1);
        }
    }else sig = 0, up = 1;
    if(sig){
        while(top){
            dp[st[top].first][st[top].second] = up;
            in[st[top].first][st[top].second] = 0;
            top--;
           if(st[top+1].first == nx && st[top+1].second == ny)break;
        }
        up++;
        while(top){
            dp[st[top].first][st[top].second] = up;
            in[st[top].first][st[top].second] = 0;
            up++;
            top--;
        }
    }else{
        while(top){
            dp[st[top].first][st[top].second] = up;
            in[st[top].first][st[top].second] = 0;
            up++;
            top--;
        }
    }
}
*/