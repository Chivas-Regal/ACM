# 🔗
<a href="https://www.luogu.com.cn/problem/P6078"><img src="https://i.loli.net/2021/11/25/WNiCvjUeZGQRs69.png"></a>

# 💡
先根据题目构建生成函数  
 <img src="https://latex.codecogs.com/svg.image?\inline&space;i:1+x+x^2+...+x^{m_i}" title="\inline i:1+x+x^2+...+x^{m_i}" />   
将生成函数乘起来  <img src="https://latex.codecogs.com/svg.image?\inline&space;\prod\limits_{i=1}^n\frac{1-x^{m_i+1}}{1-x}=\frac{\prod\limits_{i=1}^n(1-x(m_i+1))}{(1-x)^n}" title="\inline \prod\limits_{i=1}^n\frac{1-x^{m_i+1}}{1-x}=\frac{\prod\limits_{i=1}^n(1-x(m_i+1))}{(1-x)^n}" />   
上面的可以变成一个多项式  <img src="https://latex.codecogs.com/svg.image?\inline&space;g(x)" title="\inline g(x)" />   
看下面的   
 <img src="https://latex.codecogs.com/svg.image?\inline&space;\begin{aligned}&=(1-x)^{-n}\\&=\sum\limits_{i\ge0}\binom{-n}i(-x)^i\\&=\sum\limits_{i\ge0}\frac{(-n)\times...\times(-n-i+1)}{i!}(-x)^i\\&=\sum\limits_{i\ge0}\frac{n\times...\times(n+i-1)}{i!}x^i\\&=\sum\limits_{i\ge0}\binom{n+i-1}ix^i\end{aligned}" title="\inline \begin{aligned}=(1-x)^{-n}\\=\sum\limits_{i\ge0}\binom{-n}i(-x)^i\\=\sum\limits_{i\ge0}\frac{(-n)\times...\times(-n-i+1)}{i!}(-x)^i\\=\sum\limits_{i\ge0}\frac{n\times...\times(n+i-1)}{i!}x^i\\=\sum\limits_{i\ge0}\binom{n+i-1}ix^i\end{aligned}" />   
合并起来得到  <img src="https://latex.codecogs.com/svg.image?\inline&space;g(x)\sum\limits_{i\ge0}\binom{n+i-1}ix^i" title="\inline g(x)\sum\limits_{i\ge0}\binom{n+i-1}ix^i" />   
  
对于  <img src="https://latex.codecogs.com/svg.image?\inline&space;x^k" title="\inline x^k" />  这一项：（系数设置为  <img src="https://latex.codecogs.com/svg.image?\inline&space;\alpha" title="\inline \alpha" />  )  <img src="https://latex.codecogs.com/svg.image?\inline&space;\alpha&space;x^k\sum\limits_{l\le&space;i+1\le&space;r}\binom{n+i-1}{i}x^i" title="\inline \alpha x^k\sum\limits_{l\le i+1\le r}\binom{n+i-1}{i}x^i" />   
那么这一项贡献为  <img src="https://latex.codecogs.com/svg.image?\inline&space;\alpha\sum\limits_{i=l-k}^{r-k}\binom{n+i-1}{i}" title="\inline \alpha\sum\limits_{i=l-k}^{r-k}\binom{n+i-1}{i}" />   
由  <img src="https://latex.codecogs.com/svg.image?\inline&space;\binom{n}{m}=\binom{n}{m-1}+\binom{n-1}{m-1}" title="\inline \binom{n}{m}=\binom{n}{m-1}+\binom{n-1}{m-1}" />  可将  <img src="https://latex.codecogs.com/svg.image?\inline&space;\sum\limits_{i=l-k}^{r-k}\binom{n+i-1}{i}" title="\inline \sum\limits_{i=l-k}^{r-k}\binom{n+i-1}{i}" />  化成  <img src="https://latex.codecogs.com/svg.image?\inline&space;\binom{r-k+n}{r-k}-\binom{l-k+n-1}{l-k-1}" title="\inline \binom{r-k+n}{r-k}-\binom{l-k+n-1}{l-k-1}" />   
即  <img src="https://latex.codecogs.com/svg.image?\inline&space;\alpha(\binom{r+k-n}{r-k}-\binom{l-k+n-1}{l-k-1})" title="\inline \alpha(\binom{r+k-n}{r-k}-\binom{l-k+n-1}{l-k-1})" />   

那么答案为  <img src="https://latex.codecogs.com/svg.image?\inline&space;\sum\limits_{i=1}^{SZ_g}\alpha_i(\binom{r+k_i-n}{r-k_i}-\binom{l-k_i+n-1}{l-k_i-1})" title="\inline \sum\limits_{i=1}^{SZ_g}\alpha_i(\binom{r+k_i-n}{r-k_i}-\binom{l-k_i+n-1}{l-k_i-1})" />   

对于取模，观察  <img src="https://latex.codecogs.com/svg.image?\inline&space;\binom{x+n}{x}=\frac{(n+1)\times...\times(n+x)}{n!}" title="\inline \binom{x+n}{x}=\frac{(n+1)\times...\times(n+x)}{n!}" />   
将  <img src="https://latex.codecogs.com/svg.image?\inline&space;mod+n!" title="\inline mod+n!" />  ，取完模是比  <img src="https://latex.codecogs.com/svg.image?\inline&space;n!" title="\inline n!" />  要大的，那么这时就可以直接除  <img src="https://latex.codecogs.com/svg.image?\inline&space;n!" title="\inline n!" />  了  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
int n, a, b;
int m[15];
map<int, int> g_mps;
vector<pair<int, int> > g; // first: 指数，second: 系数

const int mod = 2004;
ll MOD = mod;
ll fac = 1;
inline int C ( int n, int m ) {
        if ( n < m ) return 0;
        ll res = 1;
        for ( int i = n - m + 1; i <= n; i ++ ) res = res * i % MOD;
        return res / fac % mod;
}

int main () {
        cin >> n >> a >> b;
        for ( ll i = 1; i <= n; i ++ ) fac *= i;
        MOD *= fac;

        g_mps[0] = 1;
        for ( int i = 0; i < n; i ++ ) {
                cin >> m[i];
                vector<pair<int, int> > tmps; 
                for ( auto g_mp : g_mps ) {
                        tmps.push_back({g_mp.first, g_mp.second});
                        tmps.push_back({g_mp.first + m[i] + 1, -g_mp.second});
                }
                g_mps.clear();
                for ( auto tmp : tmps ) {
                        g_mps[tmp.first] += tmp.second;
                }
        }
        for ( auto g_mp : g_mps ) g.push_back({g_mp.first, g_mp.second});

        ll res = 0;
        for ( auto i : g ) {
                int k = i.first;
                res = ((res + (ll)i.second * (C(n + b - k, n) - C(n + a - k - 1, n) + mod) % mod) % mod + mod) % mod;
        }
        cout << res << endl;
}
```
