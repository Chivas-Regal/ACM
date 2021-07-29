//搜索
//一棵树,已知1结点已被感染，每一单位时间可以将
//其下一代感染，一单位时间也可以切断一条边，求
//最少感染多少人
//搜索，此题与一般的搜索不同的是：此题不能在单纯的
//传递某个结点作为参数，而应该将树的深度，传递层
//为参数。首先预处理出每层的结点，然后dfs，切断该层
//中的某个可能被感染的结点，被向下继续求解 
//题目链接：https://www.luogu.org/problemnew/show/P1041 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 320;
vector<int> G[maxn], g[maxn], s[maxn];
int minn, vis[maxn], ti[maxn], ts[maxn];
void solve(int ans, int step);
void bfs(int n);
void work(int u, int stu, int step);

int main()
{
    int n, m, i, j;
    minn = INF; 
    scanf("%d %d", &n, &m);
    while(m--){
        scanf("%d %d", &i, &j);
        G[i].push_back(j);
        G[j].push_back(i);
    }
    bfs(n);
    for(i=1;i<=n;i++)
    if(s[i].size()==0)break;
    else ts[i] = s[i].size();
    solve(1, 2);
    if(n == 1)minn = 1;
    printf("%d", minn);
    return 0;
}
//求各点的深度，并重新构图 
void bfs(int n){
    queue<int> que;
    que.push(1);
    ti[1] = 1;
    while(!que.empty()){
        int u = que.front();que.pop();
        s[ti[u]].push_back(u);
        for(int i=0;i<G[u].size();i++)
        if(!ti[G[u][i]]){
            ti[G[u][i]] = ti[u]+1;
            que.push(G[u][i]);
            g[u].push_back(G[u][i]);
        }
    }
}
//递归求解 
void solve(int ans, int step){
    int i, u;
    /*printf("step:%d t:%d %d\n", step, ts[step], ans);
    for(i=1;i<=7;i++)printf("%d ", vis[i]);
    printf("\n");*/
    if(ts[step] == 0){
        minn = min(minn, ans);
    }
    else
    {
        for(i=0;i<s[step].size();++i){
            u = s[step][i];
            if(!vis[u]){
            	//如果当前的仍有机会被感染，则切断他
				//并将他的子节点全部标记为安全状态 
                vis[s[step][i]] = 1;
                work(s[step][i], 1, step); 
                solve(ans+ts[step], step+1);
                work(s[step][i], 0, step);
                vis[s[step][i]] = 0;
            }
        }
    }
}

void work(int u, int stu, int step)
{
	if(stu)ts[step]--;
	else ts[step]++; 
    vis[u] = stu;
    for(int i=0;i<g[u].size();++i)
        work(g[u][i], stu, step+1);
} 
