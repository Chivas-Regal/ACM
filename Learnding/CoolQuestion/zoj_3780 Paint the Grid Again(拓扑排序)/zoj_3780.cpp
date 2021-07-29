/*************************************************************************
拓扑排序

有一个n*n大小的网格，每次可以将一行所有格涂成黑色或者将一列所有格涂成白色。初始网格
无色，求最少的操作次数的方案。

思路：为了保证最少操作次数，先处理出那些行列是必须要操作的。如果第i行有黑色方块，则说明他
一定需要一次操作，第j列有白色方块，也一定需要一次操作。
确定操作次序，若第i行第j列为'X'，则说明涂白操作在涂黑操作之前，连边j->i，若为'O',则说明
涂白操作在涂黑操作之后，连边i->j，最后对图进行拓扑排序。如果图无环，则能正常处理出
所有元素，若有环，无解，只能排出部分操作。
字典序最小，将行编号由i变为i+n，拓扑时，利用优先队列，取出元素即可。

题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827369765
*****************************************************************************/
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
const int maxn = 1020;
const int mod = 998244353;
char str[maxn][maxn];
int vis[2*maxn], in[maxn];
vector<int> g[2*maxn], ans;

int main()
{
    int t, n, m, i, j, k, num;
    scanf("%d", &t);
    while(t--)
    {
        num = 0;
        priority_queue<int,vector<int>,greater<int> > que;
        scanf("%d", &n);
        ans.clear();
        for(i=0;i<=2*n;i++){
            vis[i] = in[i] = 0;
            g[i].clear();
        }
        for(i=1;i<=n;i++){
            scanf(" %s", str[i]+1);
            for(j=1;j<=n;j++)
                if(str[i][j] == 'X')
                    vis[i+n] = 1;
                else vis[j] = 1;
        }
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                if(vis[i+n] && vis[j]){
                    if(str[i][j] == 'X'){
                        g[j].push_back(i+n);
                        in[i+n]++;
                    }else{
                        g[i+n].push_back(j);
                        in[j]++;
                    }
                }
        for(i=1;i<=2*n;i++)
            if(vis[i]){
                num++;
                if(in[i] == 0)que.push(i);
            }
        while(!que.empty())
        {
           
            int v = que.top();que.pop();
            ans.push_back(v);
            for(int i=0;i<g[v].size();i++)
            {
                in[g[v][i]]--;
                if(in[g[v][i]] == 0)
                    que.push(g[v][i]);
            }
        }
        if(ans.size() == num){
            for(i=0;i<ans.size();i++){
                if(i)printf(" ");
                if(ans[i]<=n)printf("C%d", ans[i]);
                else printf("R%d", ans[i]-n);
            }
            printf("\n");
        }else printf("No solution\n");
    }
    return 0;
}