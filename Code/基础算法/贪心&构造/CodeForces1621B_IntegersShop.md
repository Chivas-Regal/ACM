# 🔗
<a href="https://codeforces.com/contest/1621/problem/B"><img src="https://s2.loli.net/2022/01/04/YCUIs6LRJNdXayb.png"></a>

# 💡
根据题意我们容易知道，其实就是让你选能覆盖已知全局的  <img src="https://latex.codecogs.com/svg.image?\inline&space;l" title="\inline l" /> 和  <img src="https://latex.codecogs.com/svg.image?\inline&space;r" title="\inline r" />   
这个  <img src="https://latex.codecogs.com/svg.image?\inline&space;l" title="\inline l" /> 和  <img src="https://latex.codecogs.com/svg.image?\inline&space;r" title="\inline r" /> **可能会在一个段里也可能会在两个段里**   
<img src="https://s2.loli.net/2022/01/04/XIrcsGPKTCU48k5.png">
    
所以我们维护一个只会扩展的单段，维护这个单段在两端都最边界的情况下价值最小  
>如果枚举到的段两端都比这个单段靠边 或者 等于这个单段的两端（彻底包含它）并且可以让它的价值更小，就替换这个单段  

和一套双段，一个左段一个右段，维护这两个双段分别左侧和右侧都最边界的情况下价值最小  
>对于左段，如果枚举到的段左侧比这个左段靠边 或者 等于这个左段的左侧并且可以让它的价值更小，就替换这个左段  
>右段同理  
   
在求最小价值的时候  
如果这个单段包含这套双段，那么就要比价值了，肯定是选 双段价值和 与 单段价值 的最小值  
如果不包含，那么肯定是双段覆盖的点最多，就必选双段价值和了


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
struct node {
        ll a, b, v;
}nd[100005];

inline void Solve () {
        ll n; scanf("%lld", &n);
        for ( ll i = 0; i < n; i ++ ) scanf("%lld%lld%lld", &nd[i].a, &nd[i].b, &nd[i].v);
        node l = nd[0], r = nd[0]; // 左段，右段
        node allin = nd[0]; // 单段
        for ( ll i = 0; i < n; i ++ ) {
        
                if ( nd[i].b > r.b ) r = nd[i]; 
                else if ( nd[i].b == r.b && nd[i].v < r.v ) r = nd[i]; 

                if ( nd[i].a < l.a ) l = nd[i];
                else if ( nd[i].a == l.a && nd[i].v < l.v ) l = nd[i];

                if ( (nd[i].a <= allin.a && nd[i].b > allin.b) || (nd[i].a < allin.a && nd[i].b >= allin.b) ) allin = nd[i];
                else if ( nd[i].a == allin.a && nd[i].b == allin.b && nd[i].v < allin.v ) allin = nd[i];
                
                if ( allin.a <= l.a && allin.b >= r.b ) {
                        printf("%lld\n", min(allin.v, r.v + l.v));
                } else printf("%lld\n", r.v + l.v);
        }

}

int main () {       
        ll cass; scanf("%lld", &cass); while ( cass -- ) {
                Solve();
        }
}
```
