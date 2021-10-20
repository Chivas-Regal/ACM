# 🔗
<a href="https://acm.dingbacode.com/showproblem.php?pid=7079"><img src="https://i.loli.net/2021/10/20/EP2QloZ7uydMcAi.png"></a>

# 💡
  
对于x根棍子  
每个棍数量首先为0，然后是他们的摆放情况（初始默认分成两部分，两部分互相垂直    
(1, x-1)：这样的话是可以从1根棍子的摆放情况通过每个数量+1*(x-1)转移出来  
(2, x-2)：这样的话是可以从2根棍子的摆放情况通过每个数量+2*(x-2)转移出来  
(3, x-3)：这样的话是可以从3根棍子的摆放情况通过每个数量+3*(x-3)转移出来  
...  
(x-1, 1)：这样的话是可以从x-1根棍子的摆放情况通过每个数量+(x-1)*1转移出来  
那么就有了转移的方式，x根棍子可以`for ( int i = 1; i < x; i ++ ) for ( auto j : vis[i] ) vis[j.first + i * (x - i)] = 1`  
  
这类不管每个位置的数量，直管每个位置存不存在的递推关系，应该很快想到用bitset优化去解  
即 `for ( int i = 1; i < x; i ++ ) bst[x] |= bst[i] << (i * (x - i) );`  
但是这样还是太慢，我们打好一小部分去观察一下大致的表  
```
1: 0
2: 0 1
3: 0 2 3
4: 0 3 4 5 6
5: 0 4 6 7 8 9 10
6: 0 5 8 9 11 12 13 14 15
7: 0 6 10 11 12 14 15 16 17 18 19 20 21
```  
可以发现后面连续的数越来越长了，并且i后面连续的数的开始要比i-1后面连续的数的开始要大  
那么对于x是从y开始连续的话，对于x-1从y开始也必然连续  
那么暴力打一下700的表看看从哪个开始连续（等待ing  
```cpp
const int N = 710, M = 244660;
bitset<M> bst[N];
inline void Pre () {
        for ( int i = 1; i <= 700; i ++ ) {
                bst[i][0] = 1;
                for ( int j = 1; j < i; j ++ ) {
                        bst[i] |= bst[j] << (j * (i - j));
                }
        }
}
int main () {
        ios::sync_with_stdio(false); Pre();
        int res = 0, cur = 244650;
        while ( bst[700][244650] == 1 ) res = cur, bst[700] <<= 1, cur --;
        cout << res << endl;
}
```
发现从31152就能连续  
那直接把bitset的尺寸缩到31152+5即可  
然后就能飞速预处理了  
输出的时候输出1的位置，然后从M开始一直输出到(n-1)*n/2

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 710, M = 31152;
bitset<M> bst[N];

inline void Pre () {
        for ( int i = 1; i <= 700; i ++ ) {
                bst[i][0] = 1;
                for ( int j = 1; j < i; j ++ ) {
                        bst[i] |= bst[j] << (j * (i - j));
                }
        }
}
int main () {
        ios::sync_with_stdio(false); Pre();
        int cass; cin >> cass; while ( cass -- ) {
                int n; cin >> n;
                cout << 0; 
                for ( int i = 1; i < M; i ++ ) if ( bst[n][i] ) cout << " " << i;
                for ( int i = M; i <= (n - 1) * n / 2; i ++ )  cout << " " << i;
                cout << endl;
        }
}
```
