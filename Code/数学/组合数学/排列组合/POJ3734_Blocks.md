# 🔗
<a href="https://ac.nowcoder.com/acm/contest/24710/D"><img src="https://i.loli.net/2021/11/25/t2savw1RVIrTjGd.png"></a>

# 💡
首先生成函数想一波，把这四个砖的生成函数乘起来得到  <img src="https://latex.codecogs.com/svg.image?\inline&space;\frac{1}{(1-x)^4(1+x)^2}" title="\inline \frac{1}{(1-x)^4(1+x)^2}" />  发现啥也不啥，告辞  
组合数想一波  
其实就是分成两部分，一部分一定是偶数，一部分无所谓，偶数那一部分分成两份偶数，无所谓那一部分分成两份无所谓  
 <img src="https://latex.codecogs.com/svg.image?\inline&space;n" title="\inline n" />  块砖选偶数个有  <img src="https://latex.codecogs.com/svg.image?\inline&space;2^{n-1}" title="\inline 2^{n-1}" />  种，选任意个有  <img src="https://latex.codecogs.com/svg.image?\inline&space;2^n" title="\inline 2^n" />  种  
那么从这偶数个中选偶数个，再从另外任意个中选任意个，得到柿子  
 <img src="https://latex.codecogs.com/svg.image?\inline&space;\sum\limits_{i=0}^{\frac&space;n2\times2}(\binom{n}{i}\times2^{i-1}\times2^{n-i})" title="\inline \sum\limits_{i=0}^{\frac n2\times2}(\binom{n}{i}\times2^{i-1}\times2^{n-i})" />   
注意在  <img src="https://latex.codecogs.com/svg.image?\inline&space;i=0" title="\inline i=0" />  时  <img src="https://latex.codecogs.com/svg.image?\inline&space;2^{i-1}" title="\inline 2^{i-1}" />  可能会出错，所以拿出来  
 <img src="https://latex.codecogs.com/svg.image?\inline&space;\begin{aligned}&\sum\limits_{i=0}^{\frac&space;n2\times2}(\binom{n}{i}\times2^{i-1}\times2^{n-i})\\=&\sum\limits_{i=2}^{\frac&space;n2\times2}(\binom{n}{i}\times2^{i-1}\times2^{n-i})+2^n\\=&2^{n-1}\sum\limits_{i=2}^{\frac&space;n2\times2}\binom{n}{i}+2^n\\=&2^{n-1}\times(2^{n-1}-1)+2^n\end{aligned}" title="\inline \begin{aligned}&\sum\limits_{i=0}^{\frac n2\times2}(\binom{n}{i}\times2^{i-1}\times2^{n-i})\\=&\sum\limits_{i=2}^{\frac n2\times2}(\binom{n}{i}\times2^{i-1}\times2^{n-i})+2^n\\=&2^{n-1}\sum\limits_{i=2}^{\frac n2\times2}\binom{n}{i}+2^n\\=&2^{n-1}\times(2^{n-1}-1)+2^n\end{aligned}" />   
  
我们解这个柿子就行了  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int mod = 10007;

inline ll ksm ( ll a, ll b ) {
        ll res = 1;
        while ( b ) {
                if ( b & 1 ) res = res * a % mod;
                a = a * a % mod;
                b >>= 1;
        }
        return res;
}

int main () {
        int cass; cin >> cass; while ( cass -- ) {
               ll n; cin >> n;
               ll two_mi = ksm(2, n - 1);
               cout << (two_mi * (two_mi - 1) % mod + two_mi * 2 % mod) % mod << endl;
        }
}
```
