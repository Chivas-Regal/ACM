# 🔗
<a href="https://codeforces.com/contest/1605/problem/D"><img src="https://i.loli.net/2021/11/13/LgVPJUDRoGFruC9.png"></a>

# 💡
由于Eikooc只决定这个点放哪，但是先走的是Sushi  
我们可以想一种方法让断开的点尽量多，这样Eikooc放到很多个位置Sushi都走不动  
  
思考一下断边的条件： <img src="https://latex.codecogs.com/svg.image?\inline&space;a\oplus&space;b>min(a,b)" title="\inline&space;a^b>min(a,b)" />  
这样的话只要邻边的二进制位数不同就一定可以  
由于二进制位数相同的是一个集合  
我们确保邻点不在同一集合即可  

由于二进制可以合并成任意我们想要的数且二进制位数相同的数本身就是一个二的幂次      
对点二分染色一下  <img src="https://latex.codecogs.com/svg.image?\inline&space;0/1" title="\inline 0/1" />   
让染色相同的点必须包含完整的二进制集合，不能有染色不同的点二进制位数相同的情况  
  
那么我们就对  <img src="https://latex.codecogs.com/svg.image?\inline&space;n" title="\inline n" />  分二进制块之后每次一个完整的二进制块分给当前颜色数量最多的点集，给他们赋一下编号然后从该集合中删去  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 4e5 + 10;
int res[N];
struct Edge {
        int nxt, to;
} edge[N];
int head[N], cnt;
int n; 
vector<int> vec[2];

inline void add_Edge ( int from, int to ) {
        edge[ ++ cnt ] = { head[from], to };
        head[from] = cnt;
}
inline void DFS ( int x, int fath, int dep ) {
        vec[dep].push_back(x);
        for ( int i = head[x]; ~i; i = edge[i].nxt ) {
                int to = edge[i].to;
                if ( to == fath ) continue;
                DFS ( to, x, dep^1 );
        }
}

inline void Solve () {
        scanf("%d", &n);

        int stt = 0; while ( (1 << stt) <= n ) stt ++; stt --; // 有多少个二进制块
        for ( int i = 0; i <= n * 2 + 5; i ++ ) head[i] = res[i] = -1, cnt = 0;
        vec[0].clear(); vec[1].clear();

        for ( int i = 0; i < n - 1; i ++ ) {
                int a, b; scanf("%d%d", &a, &b);
                add_Edge ( a, b );
                add_Edge ( b, a );
        }
        DFS ( 1, 1, 0 ); // 染色
        for ( ; stt >= 0; stt -- ) {
                int to; // 选择点数量最多的色块
                if ( max(vec[0].size(), vec[1].size()) == vec[0].size() ) to = 0; 
                else                                                      to = 1;
                for ( int i = min(n, (1 << (stt + 1)) - 1); i >= (1 << stt); i -- ) { // 一个完整的二进制块
                        res[vec[to].back()] = i;
                        vec[to].pop_back();
                }
        }
        for ( int i = 1; i <= n; i ++ ) printf("%d ", res[i]);
        printf("\n");
}

int main () {
        int cass; scanf("%d", &cass); while ( cass -- ) {
                Solve ();
        }
}
```
