# 🔗
<a href="https://codeforces.com/contest/1611/problem/D"><img src="https://i.loli.net/2021/11/26/2CicwtKbpVXgsy1.png"></a>

# 💡
~~想半天以为这道题难点在找根...，然后发现我真是个憨憨~~  
  
### 找根
如果一个点的父节点是自己，那它就是根...（不会就我一个人这地方看半天吧  

### 检查  
由于  <img src="https://latex.codecogs.com/svg.image?\inline&space;p[]" title="\inline p[]" />  表示先后顺序，我们设  <img src="https://latex.codecogs.com/svg.image?\inline&space;p'[i]" title="\inline p'[i]" />  表示  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" />  是  <img src="https://latex.codecogs.com/svg.image?\inline&space;p[]" title="\inline p[]" />  中第几个  

```cpp
int pr[N];
int rp[N];
for ( int i = 1; i <= n; i ++ ) 
	scanf("%d", &pr[i]),
	rp[pr[i]] = i;
```

一条链上的  <img src="https://latex.codecogs.com/svg.image?\inline&space;dis[]" title="\inline dis[]" />  必定越来越大，  <img src="https://latex.codecogs.com/svg.image?\inline&space;p'[]" title="\inline p'[]" />  同样    
那么可以知道的是，如果一堆父子关系中， <img src="https://latex.codecogs.com/svg.image?\inline&space;p'[fath]>p'[son]" title="\inline p'[fath]\gt&space;p'[son]" />  那么一定不行   
这个跑一遍点就可以实现了，也要在输入  <img src="https://latex.codecogs.com/svg.image?\inline&space;b[]" title="\inline b[]" />  的时候记录一下父子关系 

**记录**
```cpp
for ( int i = 1, x; i <= n; i ++ ) {
	scanf("%d", &x); b[i] = { x, i };
}
```

**检查**
```cpp
inline bool check() {
        for ( int i = 1; i <= n; i ++ ) {
                if ( rp[b[i].first] > rp[b[i].second] ) return false;
        }
        return true;
}

if ( !check() ) { printf("-1\n"); return;};
```

### 边权  
我们不想影响他们的先后顺序  
那么可以让 $dis[i]=p'[i]$  
这样的话一条边 $(fath\rightarrow son)$ 的边权就是 $p'[fath]-p'[son]$   

```cpp
for ( int i = 1; i <= n; i ++ ) {
	printf("%d ", rp[b[i].second] - rp[b[i].first]);
} printf("\n");
```


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <queue>

#define ll long long

using namespace std;

const int N = 2e5 + 10;

int n;
pair<int, int> b[N]; // first: fath, second: son
int pr[N]; // 正p数组
int rp[N]; // 反p数组

inline bool check() {
        for ( int i = 1; i <= n; i ++ ) {
                if ( rp[b[i].first] > rp[b[i].second] ) return false;
        }
        return true;
}

inline void Solve () {

        scanf("%d", &n);
        for ( int i = 1, x; i <= n; i ++ ) {
                scanf("%d", &x); b[i] = { x, i };
        }
        for ( int i = 1; i <= n; i ++ ) 
                scanf("%d", &pr[i]),
                rp[pr[i]] = i;

        if ( !check() ) { printf("-1\n"); return;};

        for ( int i = 1; i <= n; i ++ ) {
                printf("%d ", rp[b[i].second] - rp[b[i].first]);
        } printf("\n");
        
}


int main () {
        int cass; scanf("%d", &cass); while ( cass -- ) {
                Solve ();
        }
}
```
