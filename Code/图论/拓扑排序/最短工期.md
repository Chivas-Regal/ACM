# 🔗
https://pintia.cn/problem-sets/1380134731032481792/problems/1380134925589520393

# 💡


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  
  
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdio>
#include <stack>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#define G 10.0
#define LNF 1e18
#define eps 1e-6
#define mod 1e9 + 7
#define ll long long
#define INF 0x7FFFFFFF
#define PI acos(-1.0)
#define pb(x) push_back(x)
#define SP system("pause")
#define mm(a, b) memset(a, b, sizeof(a))
#define fir(i, a, n) for (ll i = a; i <= n; i++)
#define rif(i, a, n) for (ll i = a; i >= n; i--)
#define each_cass(cass) for (scanf("%d", &cass); cass; cass--)

using namespace std;

const int maxn=500;
int head[maxn];
struct Edge{int next;int to;int val;}edge[maxn];
int dis[maxn];
int indgr[maxn];
int cnt=0;
int n,m;

void init(){
    for(int i=0;i<maxn;i++) head[i]=-1,indgr[i]=0,dis[i]=0;
    cnt=0;
}

void add_edge(int from,int to,int dis){
    edge[++cnt]={head[from],to,dis};
    head[from]=cnt;
}

void drawMap(){
    for(int i=0,x,y,z;i<m;i++){
        cin>>x>>y>>z;
        add_edge(x,y,z);
        indgr[y]++;
    }
}

void topSort(){
    queue<int>q;
    int num_inq=0;
    
    for(int i=0;i<n;i++) if(!indgr[i]) q.push(i);
    while(!q.empty()){
        int cur_start=q.front();
        num_inq++;
        q.pop();
        for(int i=head[cur_start];~i;i=edge[i].next){
            indgr[edge[i].to]--;
            if(!indgr[edge[i].to]) q.push(edge[i].to);
            dis[edge[i].to]=max(dis[edge[i].to],dis[cur_start]+edge[i].val);
        }
    }
    
    int Max=0;
    for(int i=0;i<n;i++) Max=max(Max,dis[i]);
    
    if(num_inq==n){
        cout<<Max<<endl;
    }else{
        cout<<"Impossible"<<endl;
    }
}
int main(){
    cin>>n>>m;
    init();
    drawMap();
    topSort();
}

```
