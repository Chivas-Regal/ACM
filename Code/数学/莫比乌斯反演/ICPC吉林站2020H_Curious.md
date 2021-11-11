# 🔗
<a href="https://codeforces.com/gym/102800/attachments"><img src="https://i.loli.net/2021/11/11/Vj3r1pPbgXq4nN5.png"></a>

# 💡
题目大意是给定一个序列  <img src="https://latex.codecogs.com/svg.image?\inline&space;\{a\}" title="\inline \{a\}" />   
每一次询问给定一个  <img src="https://latex.codecogs.com/svg.image?\inline&space;x" title="\inline x" />  
问  <img src="https://latex.codecogs.com/svg.image?\inline&space;\sum\limits_{i=1}^n\sum\limits_{j=1}^n[(a_i,a_j)=x]" title="\inline \sum\limits_{i=1}^n\sum\limits_{j=1}^n[(a_i,a_j)=x]" />   
我们可以感性地想到这一题  <img src="https://latex.codecogs.com/svg.image?\inline&space;\sum\limits_{i=1}^n\sum\limits_{j=1}^n[(i,j)=k]" title="\inline \sum\limits_{i=1}^n\sum\limits_{j=1}^n[(i,j)=k]" />  
想到我们后面在处理  <img src="https://latex.codecogs.com/svg.image?\inline&space;F(k)=\sum\limits_{i=1}^n\sum\limits_{j=1}^n[k\mid(i,j)]" title="\inline F(k)=\sum\limits_{i=1}^n\sum\limits_{j=1}^n[k\mid(i,j)]" /> 时使用的是让  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" /> 和  <img src="https://latex.codecogs.com/svg.image?\inline&space;j" title="\inline j" /> 都是枚举的是  <img src="https://latex.codecogs.com/svg.image?\inline&space;k" title="\inline k" /> 的倍数  
从而得到  <img src="https://latex.codecogs.com/svg.image?\inline&space;F(k)=\left\lfloor\frac&space;nk\right\rfloor^2" title="\inline F(k)=\left\lfloor\frac&space;nk\right\rfloor^2" />  
其实也就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;n" title="\inline n" /> 以下  <img src="https://latex.codecogs.com/svg.image?\inline&space;k" title="\inline k" /> 的倍数个数的平方  
而我们此时也可以使用这个  
我们预处理一个数组  <img src="https://latex.codecogs.com/svg.image?\inline&space;\{A\}" title="\inline \{A\}" /> ，其中  <img src="https://latex.codecogs.com/svg.image?\inline&space;A[i]" title="\inline A[i]" /> 表示对于  <img src="https://latex.codecogs.com/svg.image?\inline&space;\{a\}" title="\inline \{a\}" /> 中是  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" /> 倍数的个数  
这个可以通过对  <img src="https://latex.codecogs.com/svg.image?\inline&space;\{a\}" title="\inline \{a\}" />  埃氏筛  <img src="https://latex.codecogs.com/svg.image?\inline&space;O(nlogn)" title="\inline O(nlogn)" /> 地得到  
那么我们的  <img src="https://latex.codecogs.com/svg.image?\inline&space;F(k)=A[k]^2" title="\inline F(k)=A[k]^2" />   
 <img src="https://latex.codecogs.com/svg.image?\inline&space;f(k)=\sum\limits_{d=1}^{\left\lfloor\frac&space;mk\right\rfloor}\mu(d)A[d\times&space;k]^2" title="\inline&space;f(k)=\sum\limits_{d=1}^{\left\lfloor\frac&space;mk\right\rfloor}\mu(d)A[d\times&space;k]^2" />  
 然后什么都不用，暴力跑一遍这个式子就行了  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 1e5 + 10;
int a[N], vis[N];
int n, m, k;
ll A[N];

namespace Number {
        ll mu[N];
        bool not_prime[N];
        vector<int> prime;

        inline void Sieve () {
                mu[1] = 1;
                not_prime[0] = not_prime[1] = 1;
                for ( int i = 2; i < N; i ++ ) {
                        if ( !not_prime[i] ) 
                                mu[i] = -1,
                                prime.push_back(i);
                        for ( int j = 0; j < prime.size() && i * prime[j] < N; j ++ ) {
                                not_prime[i * prime[j]] = 1;
                                if ( i % prime[j] == 0 ) break;
                                mu[i * prime[j]] = -mu[i];
                        } 
                }
        }
        inline int g ( int x, int k ) { return x / (x / k); }
} using namespace Number;

int main () { Sieve();
        int cass; scanf("%d", &cass); while ( cass -- ) {
                scanf("%d%d%d", &n, &m, &k);
                for ( int i = 0; i < n; i ++ ) scanf("%d", &a[i]), vis[a[i]] ++; // 记录a[i]出现次数
                for ( int i = 1; i <= m; i ++ ) {
                        for ( int j = i; j <= m; j += i ) {
                                A[i] += vis[j]; // 预处理{a}中i的倍数的个数
                        }
                }
                while ( k -- ) {
                        int x; scanf("%d", &x);
                        ll res = 0;
                        for ( int i = 1; i <= m / x; i ++ ) res += mu[i] * A[i * x] * A[i * x]; // 跑柿子
                        printf("%lld\n", res);
                }
                for ( int i = 0; i <= m; i ++ ) A[i] = vis[i] = 0; // 清空
        }
}
```
